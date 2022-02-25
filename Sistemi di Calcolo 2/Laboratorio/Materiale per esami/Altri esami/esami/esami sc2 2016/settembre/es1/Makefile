CC = gcc -Wall -g

all: server-mp

server: server-mp.c common.h
	$(CC) -o server-mp server-mp.c

.PHONY: clean

clean:
	rm -f server-mp
