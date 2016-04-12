#compiler
CC = g++
#header
HEAD_FILE = player.hpp node.hpp

all: worms

worms: $(OBJECTS) 


worms.o: worms.cpp $(HEAD_FILE)
	$(CC) worms.o worms.c