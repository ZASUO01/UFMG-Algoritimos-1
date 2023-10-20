CC = g++
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/tp2.o $(OBJ)/Graph.o
HDRS = $(INC)/Graph.hpp
CFLAGS = -pg -Wall -c -I$(INC)
EXE = $(BIN)/tp2

test: $(EXE)
		$(EXE) < ./tests/input1.txt
		$(EXE) < ./tests/input2.txt
		$(EXE) < ./tests/input3.txt

$(BIN)/tp2: $(OBJS)
	$(CC) -pg -o $(BIN)/tp2 $(OBJS) $(LIBS)

$(OBJ)/tp2.o: $(HDRS) $(SRC)/tp2.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/tp2.o $(SRC)/tp2.cpp

$(OBJ)/Graph.o: $(HDRS) $(SRC)/Graph.cpp
	$(CC) $(CFLAGS) -o $(OBJ)/Graph.o $(SRC)/Graph.cpp

clean:
	rm -f $(EXE) $(OBJS) gmon.out