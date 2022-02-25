CC=g++
CFLAGS= -I.
DEPS=esercizio_1.h correttore_esercizio_1.h libs/mat.h
OBJS=test_esercizio_1.o esercizio_1.o libs/mat.o
OBJ_SOL=correttore_esercizio_1.o
TGT=test_esercizio_1

all: $(TGT)

%.o:	%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TGT):	$(OBJS) $(OBJ_SOL)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:	clean

clean:
	rm -rf $(OBJS) *~ $(TGT)
