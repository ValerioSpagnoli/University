CC = gcc -Wall -g

all: multi_thread

multi_thread: common.h multi_thread.c
	$(CC) -o multi_thread multi_thread.c -lpthread

.PHONY: clean
clean:
	rm -f multi_thread
