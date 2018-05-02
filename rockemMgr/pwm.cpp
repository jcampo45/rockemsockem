#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <unistd.h>
#include <dirent.h>
#include "pwm.h"

static const char* SLOTS_FILE = "/sys/devices/platform/bone_capemgr/slots";

static const char* OCP_DIR = "/sys/devices/platform/ocp/";
static const char* PWM_DIR = "/sys/class/pwm/";

bool PWM::_capeLoaded = false; 

static const std::map<int, const char*> pinHeaderLookup = {{50,  "P9_14"},
							   {51,  "P9_16"},
							   {3,   "P9_21"},
							   {2,   "P9_22"},
							   {123, "P9_28"},
							   {121, "P9_29"},
							   {120, "P9_31"},
							   {23,  "P8_13"},
							   {22,  "P8_19"},
							   {81,  "P8_34"},
							   {80,  "P8_36"},
							   {70,  "P8_45"},
							   {71,  "P8_46"}};



PWM::PWM(int pinNumber)
{
  _pinNumber = pinNumber;
  initPinFS();
  configPinMux();
  exportPWM();
}



// This method heavily based off of code provided by Pierre-Louis Constant at: https://groups.google.com/d/msg/beagleboard/gL-IobsCJ_s/p3BvBZaBBgAJ
int PWM::initPinFS()
{
  loadCape("cape-universaln");


  if (pinHeaderLookup.end() == pinHeaderLookup.find(_pinNumber)) {
    printf("ERROR: Invalid pin number specified\n");
    return -1;
  }
  const char* headerNumber = pinHeaderLookup.at(_pinNumber);

  //Find chip name
  std::string chipAddress;
  std::string pwmNumber;
  //EHRPWM0A
  if ((strcmp(headerNumber, "P9_22") == 0) || (strcmp(headerNumber, "P9_31") == 0)) {
    chipAddress = "48300200.ehrpwm";
    _exportNumber = 0;
    pwmNumber = "pwm0";
  }
  //EHRPWM0B
  if ((strcmp(headerNumber, "P9_21") == 0) || (strcmp(headerNumber, "P9_29") == 0)) {
    chipAddress = "48300200.ehrpwm";
    _exportNumber = 1;
    pwmNumber = "pwm1";
  }
  //EHRPWM1A
  if ((strcmp(headerNumber, "P9_14") == 0) || (strcmp(headerNumber, "P8_36") == 0)) {
    chipAddress = "48302200.ehrpwm";
    _exportNumber = 0;
    pwmNumber = "pwm0";
  }
  //EHRPWM1B
  if ((strcmp(headerNumber, "P9_16") == 0) || (strcmp(headerNumber, "P8_34") == 0)) {
    chipAddress = "48302200.ehrpwm";
    _exportNumber = 1;
    pwmNumber = "pwm1";
  }
  //EHRPWM2A
  if ((strcmp(headerNumber, "P8_19") == 0) || (strcmp(headerNumber, "P8_45") == 0)) {
    chipAddress = "48304200.ehrpwm";
    _exportNumber = 0;
    pwmNumber = "pwm0";
  }
  //EHRPWM2B
  if ((strcmp(headerNumber, "P8_13") == 0) || (strcmp(headerNumber, "P8_46") == 0)) {
    chipAddress = "48304200.ehrpwm";
    _exportNumber = 1;
    pwmNumber = "pwm1";
  }
  //ECAPPWM0
  if (strcmp(headerNumber, "P9_42") == 0) {
    chipAddress = "48300100.ecap";
    _exportNumber = 0;
    pwmNumber = "pwm0";
  }\
  //EHCAPPWM2
  if (strcmp(headerNumber, "P9_28") == 0) {
    chipAddress = "48300200.ecap";
    _exportNumber = 0;
    pwmNumber = "pwm0";
  }
               
  std::string chipPath;
    
  chipPath = std::string(OCP_DIR) + "subsystem/devices/" + chipAddress +"/pwm/";
    
  _pwmChip = getFullNameOfFileInDirectory(chipPath, "pwmchip");
    
  if (_pwmChip == "") {
    return -1;
  }
    
  std::string pinInterfacePath = std::string(PWM_DIR) + _pwmChip + "/" + pwmNumber + "/";
    
  _dutyCyclePath = pinInterfacePath + "duty_cycle";
  _periodPath = pinInterfacePath + "period";
  _polarityPath = pinInterfacePath + "polarity";
  _enablePath = pinInterfacePath + "enable";

  return 0;
}



// This method is taken from https://github.com/SaadAhmad/beaglebone-black-cpp-PWM/blob/master/library/PWM.cpp
// A bunch of helper functions to get us locations in the file system.
// They are used so that we can manipulate the pwm driver through the /sys interface
std::string PWM::getFullNameOfFileInDirectory(const std::string & dirName, const std::string & fileNameToFind)
{
  DIR *pDir;

  dirent *pFile;
  if ((pDir = opendir(dirName.c_str())) == NULL)
    {
      printf("Directory doesn't exist\n");
      //throw std::bad_exception();
      return "";
    }
  while ((pFile = readdir(pDir)) != NULL)
    {
      std::string currentFileName = (pFile->d_name);
      if (currentFileName.find(fileNameToFind) != std::string::npos)
	{
	  return currentFileName;
	}
    }
  return std::string("");
}


int PWM::loadCape(const char* capeName)
{
  if (!_capeLoaded) {
    printf("Loading Cape\n");
    // Use fopen() to open the file for write access.
    FILE *pfile = fopen(SLOTS_FILE, "w");
    if (pfile == NULL) {
      printf("ERROR: Unable to open cape file.\n");
      return -1;
    }
    // Write to data to the file using fprintf():
    int retVal = fprintf(pfile, "%s", capeName);
    if (retVal < 0 || strlen(capeName) != static_cast<size_t>(retVal)) {
      printf("ERROR: Unable to write to cape file.\n");
      return -2;
    }
    // Close the file using fclose():
    fclose(pfile);
    _capeLoaded = true;
  }
  
  sleep(4);
  return 0;
}


int PWM::configPinMux() {
  if (pinHeaderLookup.end() == pinHeaderLookup.find(_pinNumber)) {
    printf("ERROR: Invalid pin number specified\n");
    return -1;
  }
  const char* headerNumber = pinHeaderLookup.at(_pinNumber);
  
  // Use fopen() to open the file for write access.
  char fileName[50];
  
  sprintf(fileName, "%socp:%s_pinmux/state", OCP_DIR, headerNumber); 
  
  FILE *pfile = fopen(fileName, "w");
  if (pfile == NULL) {
    printf("ERROR: Unable to open pinmux file.\n %s\n", fileName);
    return -1;
  }
  // Write to data to the file using fprintf():
  if (strlen("pwm") != fprintf(pfile, "%s", "pwm")) {
    printf("ERROR: Unable to set pinmux.\n");
    return -1;
  }
  // Close the file using fclose():
  fclose(pfile);
  return 0;
}


int PWM::exportPWM()
{
  if (pinHeaderLookup.end() == pinHeaderLookup.find(_pinNumber)) {
    printf("ERROR: Invalid pin number specified\n");
    return -1;
  }
  
  char fileName[50];
  
  sprintf(fileName, "%s%s/export", PWM_DIR, _pwmChip.c_str()); 
  
  
  // Use fopen() to open the file for write access.
  FILE *pfile = fopen(fileName, "w");
  if (pfile == NULL) {
    printf("ERROR: Unable to open export file.\n");
    return -1;
  }
  // Write to data to the file using fprintf():
  if (1 != fprintf(pfile, "%i", _exportNumber)) {
    printf("ERROR: Unable to export pin.\n");
    return -1;
  }
  // Close the file using fclose():
  fclose(pfile);
  return 0;
}


int PWM::setDutyCycle(int nanoseconds)
{
  int returnValue = 0;
  
  printf("%s\n", _dutyCyclePath.c_str());
  
  FILE *file = fopen(_dutyCyclePath.c_str(), "w");

  if (NULL == file) {
    printf("ERROR OPENING %s.", _dutyCyclePath.c_str());
    returnValue = -1;
  }
  else {
    int charWritten = fprintf(file, "%i", nanoseconds);
    if (charWritten <= 0) { 
      printf("ERROR WRITING DATA");
      returnValue = -1;
    }
  }
  fclose(file);
  return returnValue;

}

int PWM::setPeriod(int nanoseconds)
{
  int returnValue = 0;
  
  printf("%s\n", _periodPath.c_str());
  
  FILE *file = fopen(_periodPath.c_str(), "w");

  if (NULL == file) {
    printf("ERROR OPENING %s.", _periodPath.c_str());
    returnValue = -1;
  }
  else {
    int charWritten = fprintf(file, "%i", nanoseconds);
    if (charWritten <= 0) { 
      printf("ERROR WRITING DATA");
      returnValue = -1;
    }
  }
  fclose(file);
  return returnValue;
}

int PWM::enable()
{
  int returnValue = 0;
  
  printf("%s\n", _enablePath.c_str());
  
  FILE *file = fopen(_enablePath.c_str(), "w");

  if (NULL == file) {
    printf("ERROR OPENING %s.", _enablePath.c_str());
    returnValue = -1;
  }
  else {
    int charWritten = fprintf(file, "1");
    if (charWritten <= 0) { 
      printf("ERROR WRITING DATA");
      returnValue = -1;
    }
  }
  fclose(file);
  return returnValue;
}

int PWM::disable()
{
  int returnValue = 0;
  
  printf("%s\n", _enablePath.c_str());
  
  FILE *file = fopen(_enablePath.c_str(), "w");

  if (NULL == file) {
    printf("ERROR OPENING %s.", _enablePath.c_str());
    returnValue = -1;
  }
  else {
    int charWritten = fprintf(file, "0");
    if (charWritten <= 0) { 
      printf("ERROR WRITING DATA");
      returnValue = -1;
    }
  }
  fclose(file);
  return returnValue;
}

int PWM::getDutyCycle()
{
  return getValue(_dutyCyclePath.c_str());
}

int PWM::getPeriod()
{
  return getValue(_periodPath.c_str());
}

int PWM::getValue(const char *fileName)
{
  FILE *file = fopen(fileName, "r");
  if (NULL == file) {
    printf("ERROR: Unable to open file (%s) for read\n", fileName);
    exit(-1);
  }

  // Read string (line)
  const int max_length = 32;
  char buff[max_length];
  fgets(buff, max_length, file);
  
  // Close
  fclose(file);
  
  return atoi(buff);
}


/*int main()
{
PWM pwm50(50);
printf("Enabling PWM on GPIO50\n");
printf("PWM Pin directories:\n");

pwm50.setPeriod(10000000);
pwm50.setDutyCycle(5000000);

printf("Period: %i\n", pwm50.getPeriod());
printf("DutyCycle: %i\n", pwm50.getDutyCycle());
pwm50.enable();
}
*/
