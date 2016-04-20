#compiler
CC = g++
#flag compiler
FLAG_CC = -I $(HEAD_DIR) -o 
#source directory
SRC_DIR = src/
#header directory
HEAD_DIR = 	header/
#header
HEAD_FILE = $(HEAD_DIR)header.hpp $(HEAD_DIR)player.hpp $(HEAD_DIR)node.hpp $(HEAD_DIR)auxiliary.hpp $(HEAD_DIR)macros.hpp
#source
SOURCE_FILE = $(SRC_DIR)worms.cpp $(SRC_DIR)auxiliary.cpp $(SRC_DIR)node.cpp $(SRC_DIR)player.cpp

all: worms

worms: $(SOURCE_FILE) $(HEAD_FILE)
	$(CC) $(FLAG_CC) worms $(SOURCE_FILE)

clean:
	rm -rf worms