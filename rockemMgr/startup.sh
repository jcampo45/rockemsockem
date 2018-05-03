#!/bin/sh

echo BB-ADC > /sys/devices/platform/bone_capemgr/slots

config-pin P9.21 pwm
config-pin P9.14 pwm
config-pin P8.13 pwm
config-pin P8.19 pwm

./pwmcheck.sh

echo 49 > /sys/class/gpio/export
echo 115 > /sys/class/gpio/export
echo 112 > /sys/class/gpio/export
echo 2 > /sys/class/gpio/export
echo 15 > /sys/class/gpio/export
echo 14 > /sys/class/gpio/export

echo 67 > /sys/class/gpio/export
echo 68 > /sys/class/gpio/export
echo 44 > /sys/class/gpio/export
echo 26 > /sys/class/gpio/export
echo 46 > /sys/class/gpio/export
echo 65 > /sys/class/gpio/export
