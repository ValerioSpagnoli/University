driver:	driver.o linked_list.o max_gap.o labirinto.o
	gcc -o driver driver.o linked_list.o max_gap.o labirinto.o

driver.o: driver.c linked_list.h max_gap.h labirinto.h
	gcc -c driver.c

linked_list.o: linked_list.h linked_list.c
	gcc -c linked_list.c

max_gap.o: max_gap.h max_gap.c
	gcc -c max_gap.c

labirinto.o: labirinto.h labirinto.c
	gcc -c labirinto.c

.PHONY:clean
clean:
	-rm ./*.o 
	-rm driver
