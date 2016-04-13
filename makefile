#compiler
CC = g++
#flag compiler
FLAG_CC = -o
#header
HEAD_FILE = player.hpp node.hpp

all: worms

worms: worms.cpp $(HEAD_FILE)
	$(CC) $(FLAG_CC) worms worms.cpp