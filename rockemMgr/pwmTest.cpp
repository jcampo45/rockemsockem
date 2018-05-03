#include "pwm.h"
#include<unistd.h>

int main()
{
  PWM pwm50("pwmchip0/","pwm1/");
  printf("Enabling PWM on GPIO50\n");
  printf("PWM Pin directories:\n");
  pwm50.enable();
  pwm50.setPeriod(20000);
  pwm50.setDutyCycle(1750);
  pwm50.enable();
  sleep(1);
  pwm50.disable();
  pwm50.setDutyCycle(2000);
  pwm50.enable();
  sleep(1);
  pwm50.disable();
  pwm50.setDutyCycle(1600);
  pwm50.enable();
  sleep(1);
  pwm50.disable();
  pwm50.setDutyCycle(1750);
  pwm50.enable();
  printf("Period: %i\n", pwm50.getPeriod());
  printf("DutyCycle: %i\n", pwm50.getDutyCycle());

}
