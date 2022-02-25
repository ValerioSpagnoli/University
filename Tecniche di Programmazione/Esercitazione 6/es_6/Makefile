CC=g++
CFLAGS= -I.
DEPS=e6_esercizio.h e6_correttore.h 
OBJS=e6_test_esercizio.o e6_esercizio.o 
OBJ_SOL=e6_correttore.o
TGT=e6_test_esercizio

all: $(TGT)

%.o:	%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TGT):	$(OBJS) $(OBJ_SOL)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:	clean

clean:
	rm -rf $(OBJS) *~ $(TGT)
