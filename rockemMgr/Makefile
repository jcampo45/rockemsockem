CC = g++
CXX = g++

CXXFLAGS = -g -Wall

game: gamemanager.o imureader.o armcontroller.o dodgecontroller.o bbcommands.o

game.o: gamemanager.hh imureader.hh armcontroller.hh dodgecontroller.hh bbcommands.hh

gamemanager.o: imureader.hh armcontroller.hh dodgecontroller.hh bbcommands.hh

imureader.o: imureader.hh bbcommands.hh

armcontroller.o: armcontroller.hh bbcommands.hh

dodgecontroller.o: dodgecontroller.hh bbcommands.hh

bbcommands.o: bbcommands.hh

.PHONY: clean
clean:
	rm *.o game

.PHONY: all
all: clean game
