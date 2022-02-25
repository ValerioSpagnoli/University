#default rules
.phony:	clean all

#make rule
all:	main

#each .o depends on the corresponding .c
%.o:	%.c grafo.h
	g++ -c -Wall -Werror=return-type $< -o $@

#main depends on all object files
main: esercizi.o grafo.o ins_sclord.o
	g++ -Wall -o $@ $^

#polishes
clean:	
	rm -rf *.o main *~

