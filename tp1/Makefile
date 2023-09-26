#---------------------------------------------------------------------
# FILE: Makefile
# Content	: instructions to compile the tp1 program
# Author	: ZASUO01
# Creation  : 26-09-23
#---------------------------------------------------------------------
# Options	: make - Generates the exe
#           : make test - Runs all the test files 
#		    : make clean - removes objects and exe
#---------------------------------------------------------------------
CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/tp1.o $(OBJ)/Graph.o
HDRS = $(INC)/Graph.hpp
CFLAGS = -pg -Wall -c -I$(INC)
EXE = $(BIN)/tp1

test: $(EXE)
		$(EXE) < ./tests/input1.txt
		$(EXE) < ./tests/input2.txt
		$(EXE) < ./tests/input3.txt
		$(EXE) < ./tests/input4.txt

$(BIN)/tp1: $(OBJS)
	$(CC) -pg -o $(BIN)/tp1 $(OBJS) $(LIBS)

$(OBJ)/tp1.o: $(HDRS) $(SRC)/tp1.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/tp1.o $(SRC)/tp1.cpp

$(OBJ)/Graph.o: $(HDRS) $(SRC)/Graph.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Graph.o $(SRC)/Graph.cpp

clean:
	rm -f $(EXE) $(OBJS) gmon.out