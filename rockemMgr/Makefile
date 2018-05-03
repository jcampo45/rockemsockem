CC = g++
CXX = g++

CFLAGS = -g -Wall -std=c++11 -I./BlackLib/BlackI2C -I./BlackLib/BlackADC -I./BlackLib/BlackGPIO 
CXXFLAGS = $(CFLAGS)
LDFLAGS = -std=c++11

game: game.o robot.o display.o pwm.o ./BlackLib/BlackI2C/BlackI2C.o ./BlackLib/BlackADC/BlackADC.o ./BlackLib/BlackGPIO/BlackGPIO.o ./BlackLib/BlackCore.o

multiReadTest: ./BlackLib/BlackI2C/BlackI2C.o ./BlackLib/BlackCore.o

solenoid: ./BlackLib/BlackGPIO/BlackGPIO.o ./BlackLib/BlackCore.o

punchTest: ./BlackLib/BlackI2C/BlackI2C.o ./BlackLib/BlackGPIO/BlackGPIO.o ./BlackLib/BlackCore.o

onePunch: ./BlackLib/BlackI2C/BlackI2C.o ./BlackLib/BlackGPIO/BlackGPIO.o ./BlackLib/BlackCore.o

imuRead: ./BlackLib/BlackI2C/BlackI2C.o ./BlackLib/BlackCore.o

motionTrace: ./BlackLib/BlackI2C/BlackI2C.o ./BlackLib/BlackCore.o

harnessTest: ./BlackLib/BlackI2C/BlackI2C.o ./BlackLib/BlackCore.o

displayTest: display.o ./BlackLib/BlackI2C/BlackI2C.o ./BlackLib/BlackCore.o

joystickRead:  ./BlackLib/BlackADC/BlackADC.o ./BlackLib/BlackCore.o

buttonTest: ./BlackLib/BlackCore.o ./BlackLib/BlackGPIO/BlackGPIO.o

pwmTest: pwm.o

BlackLib/BlackCore.o: 
	make -C ./BlackLib

robot.o: robot.h

display.o: display.h
.PHONY: clean
clean:
	rm *.o game multiReadTest solenoid punchTest onePunch servoTest imuRead motionTrace displayTest joystickRead buttonTest -rf

.PHONY: default
all: clean game

.PHONY: all 
default: clean game solenoid punchTest imuRead joystickRead
