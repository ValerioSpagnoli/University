CC = gcc -Wall -g

all: multi_process

multi_process: common.h multi_process.c
	$(CC) -o multi_process multi_process.c

.PHONY: clean
clean:
	rm -f multi_process
