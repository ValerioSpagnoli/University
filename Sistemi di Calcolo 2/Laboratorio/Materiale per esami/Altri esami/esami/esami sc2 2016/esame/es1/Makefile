CC = gcc -Wall -g

all: server

server: server.c common.h
	$(CC) -o server server.c -lpthread

.PHONY: clean

clean:
	rm -f server
