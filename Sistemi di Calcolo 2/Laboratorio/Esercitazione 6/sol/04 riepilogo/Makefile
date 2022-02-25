CC = gcc -Wall -g
LDFLAGS = -lpthread -lrt

all: riepilogo

riepilogo: riepilogo.c common.h
	$(CC) -o riepilogo riepilogo.c $(LDFLAGS)


.PHONY: clean
clean:
	rm -f riepilogo

