#default rules
.phony:	clean all

#make rule
all:	main


%.o:	%.c albero.h
	g++ -c -Wall -Werror=return-type $< -o $@

#main depends on all object files
main: esercizi.o albero.c
	g++ -Wall -o $@ $^

#polishes
clean:	
	rm -rf *.o main *~

