#ifndef PWM_H
#define PWM_H

#include <string>

class PWM
{

 public:
  
  PWM(int pinNumber);
  
  int setDutyCycle(int value);
  int setPeriod(int value);

  int getDutyCycle();
  int getPeriod();
  
  int enable();
  int disable();
  
 private:

  int initPinFS();
  
  static int loadCape(const char* capeName);
  
  std::string getFullNameOfFileInDirectory(const std::string & dirName, const std::string & fileNameToFind);
  
  int configPinMux();
  
  int exportPWM();
  
  static int getValue(const char* fileName);

  static bool _capeLoaded;

  int _pinNumber;
  int _exportNumber;
  
  std::string _pwmChip;
  
  std::string _dutyCyclePath;
  std::string _periodPath;   
  std::string _polarityPath;
  std::string _enablePath;
};


#endif
