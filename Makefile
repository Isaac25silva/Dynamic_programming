###############################################################
#
# Purpose: Makefile for "Programação Dinâmica"
# Author.: Isaac Jesus da Silvamake
# Version: 0.1
#
###############################################################

CC = gcc
TARGET = exec
INCLUDE_DIRS = -I./include
LFLAGS += -std=c++0x -lstdc++ -lm
CFLAGS  = -g -Wall #check warning

SRC =  ./src/main.cpp     	\
        ./src/classe.cpp

$(TARGET): $(SRC)
#	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LFLAGS) $(INCLUDE_DIRS)
	$(CC) -o $(TARGET) $(SRC) $(LFLAGS) $(INCLUDE_DIRS) 

all: $(TARGET)

.PHONY: clean

clean:
	rm -f ./exec 
