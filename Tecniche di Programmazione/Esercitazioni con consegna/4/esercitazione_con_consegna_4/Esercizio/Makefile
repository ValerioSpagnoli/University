CC=g++
CFLAGS= -I.
DEPS=esercizio_1.h libs/scl.h
OBJS=test_esercizio_1.o esercizio_1.o libs/scl.o
TGT=test_esercizio_1

all: $(TGT)

%.o:	%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TGT):	$(OBJS) $(OBJ_SOL)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:	clean

clean:
	rm -rf $(OBJS) *~ $(TGT)
