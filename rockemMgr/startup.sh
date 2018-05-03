#!/bin/sh

echo BB-ADC > /sys/devices/platform/bone_capemgr/slots

config-pin P9.21 pwm
echo 20000000 > /sys/
config-pin P9.14 pwm
config-pin P8.13 pwm
config-pin P8.19 pwm
