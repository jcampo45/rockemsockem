#ifndef PWM_H
#define PWM_H

#include <string>

class PWM
{

 public:
  
  PWM(std::string pchip, std::string proot);
  ~PWM();
  
  int setDutyCycle(int value);
  int setPeriod(int value);

  int getDutyCycle();
  int getPeriod();
  
  int enable();
  int disable();
  
 private:

  int exportPWM();
  
  static int getValue(const char* fileName);

  int _exportNumber;
  
  std::string _pwmChip;
  std::string _dutyCyclePath;
  std::string _periodPath;   
  std::string _polarityPath;
  std::string _enablePath;
};


#endif
