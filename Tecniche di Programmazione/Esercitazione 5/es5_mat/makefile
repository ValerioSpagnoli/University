CC=g++
CFLAGS= -I.
DEPS=es5_mat.h 
OBJS=es5_mat_test.o es5_mat.o 
TGT=es5_mat_test

all: $(TGT)

%.o:	%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TGT):	$(OBJS) $(OBJ_SOL)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY:	clean

clean:
	rm -rf $(OBJS) *~ $(TGT)
