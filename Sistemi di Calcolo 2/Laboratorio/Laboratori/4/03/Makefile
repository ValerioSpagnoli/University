CFLAGS=-m32 -g -Wall
all: producer consumer

producer: producer.c common.h
	gcc $(CFLAGS) -o producer producer.c -lrt

consumer: consumer.c common.h
	gcc $(CFLAGS) -o consumer consumer.c -lrt

.PHONY: clean
clean:
	rm -f producer consumer
