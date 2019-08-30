

CC = clang
CFLAGS = -Wall -Wextra -pedantic -Wfloat-equal -std=c90 -O2
LIBS = -lm
SRC = huffman.c linkedlist.c huffmantree.c
INC = linkedlist.h huffmantree.h
TARGET = huffman

all: $(TARGET)

$(TARGET): $(SRC) $(INC)
	$(CC) $(SRC) -o $(TARGET) $(CFLAGS) $(LIBS)
