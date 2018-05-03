

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <unistd.h>
#include <dirent.h>
#include "pwm.h"

static const char* PWM_DIR = "/sys/class/pwm/";

PWM::PWM(std::string pchip, std::string proot)
{
  std::string pinInterfacePath  = PWM_DIR + pchip + proot;
  _pwmChip          = pchip;
  _exportNumber     = atoi(&proot[3]);
  _dutyCyclePath    = pinInterfacePath + "duty_cycle";
  _periodPath       = pinInterfacePath + "period";
  _polarityPath     = pinInterfacePath + "polarity";
  _enablePath       = pinInterfacePath + "enable";

  exportPWM();

}

PWM::~PWM(){
  disable(); 
}

int PWM::exportPWM()
{

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
  
  //  printf("%s\n", _dutyCyclePath.c_str());
  
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
  
  //printf("%s\n", _periodPath.c_str());
  
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
  
  //printf("%s\n", _enablePath.c_str());
  
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
  
  //printf("%s\n", _enablePath.c_str());
  
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
