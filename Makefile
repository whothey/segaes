CC=gcc
BIN=bin
CFLAGS=-Wall

all: cli

cli: cli.c aes.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: cli
	./$(BIN)/$<

clean:
	rm -f $(BIN)/*
