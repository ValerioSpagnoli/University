CC = gcc -Wall -g
LDFLAGS = -lpthread

all: multi_proc_thread

multi_proc_thread: common.h multi_proc_thread.c
	$(CC) -o multi_proc_thread multi_proc_thread.c $(LDFLAGS)

.PHONY: clean
clean:
	rm -f multi_proc_thread
