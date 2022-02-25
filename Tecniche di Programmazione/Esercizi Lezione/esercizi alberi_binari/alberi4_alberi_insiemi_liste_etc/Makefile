#default rules
.phony:	clean all

#make rule
all:	main

#each .o depends on the corresponding .c
%.o: %.c albbin.h
	g++ -c -Wall -Werror=return-type $< -o $@

#main depends on all object files
main: esercizi4.o albbin.o ins_scl.o lista_scl.o pila_scl.o coda_scl.o albbin_ascii.o
	g++ -Wall -o $@ $^

#polishes
clean:	
	rm -rf *.o main *~

