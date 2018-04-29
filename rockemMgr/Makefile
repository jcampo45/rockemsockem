CC = g++
CXX = g++

CFLAGS = -g -Wall -std=c++11 -I./BlackLib/BlackPWM -I./BlackLib/BlackI2C -I./BlackLib/BlackADC -I./BlackLib/BlackGPIO 
CXXFLAGS = $(CFLAGS)
LDFLAGS = -std=c++11

game: robot.o display.o ./BlackLib/BlackPWM/BlackPWM.o ./BlackLib/BlackI2C/BlackI2C.o ./BlackLib/BlackADC/BlackADC.o ./BlackLib/BlackGPIO/BlackGPIO.o ./BlackLib/BlackCore.o

solenoid: solenoid.o ./BlackLib/BlackGPIO/BlackGPIO.o ./BlackLib/BlackCore.o

punchTest: punchTest.o ./BlackLib/BlackI2C/BlackI2C.o ./BlackLib/BlackGPIO/BlackGPIO.o ./BlackLib/BlackCore.o

onePunch: onePunch.o ./BlackLib/BlackI2C/BlackI2C.o ./BlackLib/BlackGPIO/BlackGPIO.o ./BlackLib/BlackCore.o

imuRead: imuRead.o ./BlackLib/BlackI2C/BlackI2C.o ./BlackLib/BlackCore.o

#muxImuRead: muxImuRead.o ./BlackLib/BlackPWM/BlackPWM.o ./BlackLib/BlackI2C/BlackI2C.o ./BlackLib/BlackADC/BlackADC.o ./BlackLib/BlackGPIO/BlackGPIO.o ./BlackLib/BlackCore.o

joystickRead: joystickRead.o ./BlackLib/BlackADC/BlackADC.o ./BlackLib/BlackCore.o

buttonTest: ./BlackLib/BlackCore.o ./BlackLib/BlackGPIO/BlackGPIO.o

game.o:  

BlackLib/BlackCore.o: 
	make -C ./BlackLib

robot.o: robot.h

display.o: display.h
.PHONY: clean
clean:
	rm *.o game

.PHONY: default
all: clean game

.PHONY: all 
default: clean game solenoid punchTest imuRead joystickRead
