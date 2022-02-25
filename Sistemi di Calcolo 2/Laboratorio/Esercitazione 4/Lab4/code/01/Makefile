CFLAGS=-m32 -g -Wall
all: req_wrk

req_wrk: req_wrk.c common.h
	gcc $(CFLAGS) -o req_wrk req_wrk.c -lrt -pthread

.PHONY: clean
clean:
	rm -f req_wrk
