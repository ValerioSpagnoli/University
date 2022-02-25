CC = gcc -Wall -g

all: master

master: master.c common.h ds.c
	$(CC) -o master master.c ds.c

.PHONY: clean
clean:
	rm -f master /tmp/ds_fifo_1 /tmp/ds_fifo_2 
