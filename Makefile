CC=gcc
BIN=bin
CFLAGS=-Wall

all: aes

aes: aes.c
	$(CC) $(CFLAGS) $< -o $(BIN)/$@

run: aes
	./$(BIN)/$<

clean:
	rm -f $(BIN)/*
