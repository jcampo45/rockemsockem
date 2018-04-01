CC = g++
CXX = g++

CFLAGS = -g -Wall -std=c++11 -I./BlackLib/BlackPWM -I./BlackLib/BlackI2C -I./BlackLib/BlackADC 
CXXFLAGS = $(CFLAGS)
LDFLAGS = -std=c++11

game: robot.o ./BlackLib/BlackPWM/BlackPWM.o ./BlackLib/BlackI2C/BlackI2C.o ./BlackLib/BlackADC/BlackADC.o ./BlackLib/BlackGPIO/BlackGPIO.o ./BlackLib/BlackCore.o

game.o:  

BlackLib/BlackPWM/BlackPWM.o: 
	make -C ./BlackLib

robot.o: robot.h

.PHONY: clean
clean:
	rm *.o game

.PHONY: all
all: clean game
