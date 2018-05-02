#include "pwm.h"

int main()
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
