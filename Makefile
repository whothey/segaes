CC=gcc
BIN=bin
CFLAGS=-Wall

.PHONY: cli debug release

all: cli

cli: cli.c aes.o
	$(CC) $(CFLAGS) $^ -o $(BIN)/$@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS+=-DDEBUG -g

release: CFLAGS+=-O2 -DRELEASE

debug release: cli

run: cli
	./$(BIN)/$<

clean:
	rm -f $(BIN)/* *.o
