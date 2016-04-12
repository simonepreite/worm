#compiler
CC = g++
#header
HEAD_FILE = player.hpp node.hpp

all: worms

worms: $(OBJECTS) 


worms.o: worms.cpp $(HEAD_FILE)
	$(CC) $(FLAG_CC) $(SRC_DIR)pcb.o $(SRC_DIR)pcb.c