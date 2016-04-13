#compiler
CC = g++
#flag compiler
FLAG_CC = -o
#header
HEAD_FILE = header.hpp player.hpp node.hpp auxiliary.hpp 
#source
SOURCE_FILE = worms.cpp auxiliary.cpp

all: worms

worms: $(SOURCE_FILE) $(HEAD_FILE)
	$(CC) $(FLAG_CC) worms $(SOURCE_FILE)

clean:
	rm -rf worms