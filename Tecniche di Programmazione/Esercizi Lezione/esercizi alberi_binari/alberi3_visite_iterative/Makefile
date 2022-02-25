#default rules
.phony:	clean all

#make rule
all:	main

#each .o depends on the corresponding .c
%.o: %.c albbin.h
	g++ -c -Wall -Werror=return-type $< -o $@

#main depends on all object files
main: esercizi3.o albbin.o pila_scl.o coda_scl.o
	g++ -Wall -o $@ $^

#polishes
clean:	
	rm -rf *.o main *~

