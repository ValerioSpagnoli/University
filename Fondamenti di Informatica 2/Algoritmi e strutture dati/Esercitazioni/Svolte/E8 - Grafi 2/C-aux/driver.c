#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "graph.h"
#include "graph_services.h"

void print_help() {
    printf("Richiesto argomento: {graph, sweep, top_sort, strong_cc, list}\n");
}

int main(int argc, char** argv) {
	if (argc != 2) {
		print_help();
		return EXIT_FAILURE;
	}
	else if (strcmp(argv[1], "list") == 0) {
		linked_list* lista = linked_list_new();
		linked_list_print(lista);
		printf("\n");

		linked_list_add(lista,0, "1");
		linked_list_print(lista);
		printf("\n");

		linked_list_add(lista,0, "2");
		linked_list_print(lista);
		printf("\n");

		linked_list_add(lista,1, "3");
		linked_list_print(lista);
		printf("\n");

		linked_list_add(lista,2, "4");
		linked_list_print(lista);
		printf("\n");

		linked_list_add(lista,4, "5");
		linked_list_print(lista);
		printf("\n");
		
		for (int i = -1; i <= linked_list_size(lista); i++) {
			printf("element in pos: %d -> %s\n", i, (char*)linked_list_get(lista, i));
		}
		printf("\n");

		linked_list_remove(lista, 0);
		linked_list_print(lista);
		printf("\n");

		linked_list_remove(lista, 0);
		linked_list_print(lista);
		printf("\n");

		linked_list_remove(lista, 1);
		linked_list_print(lista);
		printf("\n");

		linked_list_remove(lista, 1);
		linked_list_print(lista);
		printf("\n");

		linked_list_remove(lista, 0);
		linked_list_print(lista);
		printf("\n");

		linked_list_add(lista, 0, "1");
		linked_list_add(lista, 0, "2");
		linked_list_add(lista, 0, "3");
		linked_list_add(lista, 0, "5");
		linked_list_add(lista, 0, "4");
		linked_list_enqueue(lista, "4");
		linked_list_enqueue(lista, "5");
		linked_list_enqueue(lista, "1");
		linked_list_enqueue(lista, "1");
		linked_list_enqueue(lista, "4");
		linked_list_enqueue(lista, "5");

		linked_list_print(lista);
		linked_list_iterator *it = linked_list_iterator_new(lista);
		void * cur = linked_list_iterator_getvalue(it);
		for(; linked_list_iterator_hasnext(it); cur = linked_list_iterator_next(it)) {
			if (cur) {
				if (((char*)cur)[0] == '1') {
					linked_list_iterator_remove(it);
				}
				if (((char*)cur)[0] == '4') {
					linked_list_iterator_remove(it);
				}
				if (((char*)cur)[0] == '5') {
					linked_list_iterator_remove(it);
				}
			}
			//linked_list_iterator_remove(it);
			linked_list_print(lista);
		}
		linked_list_iterator_delete(it);
		
		printf("DONE\n");
		linked_list_delete(lista);
	}
	else if (strcmp(argv[1], "graph") == 0) {
		graph * graph = graph_new();
		
		graph_node * a = graph_add_node(graph, "a");
		graph_node * b = graph_add_node(graph, "b");
		graph_node * c = graph_add_node(graph, "c");
		graph_node * d = graph_add_node(graph, "d");
		graph_node * e = graph_add_node(graph, "e");
		graph_node * f = graph_add_node(graph, "f");
		graph_node * g = graph_add_node(graph, "g");
		graph_node * h = graph_add_node(graph, "h");
		graph_node * i = graph_add_node(graph, "i");

		graph_add_edge(graph, b, c);
		graph_add_edge(graph, b, f);
		graph_add_edge(graph, c, d);
		graph_add_edge(graph, d, b);
		graph_add_edge(graph, e, f);
		graph_add_edge(graph, f, c);
		graph_add_edge(graph, g, h);
		graph_add_edge(graph, a, c);
		graph_add_edge(graph, c, a);
		graph_add_edge(graph, i, a);

		printf("Grafo iniziale\n\n");
		graph_print(graph);
		printf("\n");

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(a));
		graph_remove_node(graph, a);
		graph_print(graph);

		printf("Rimozione: %s,%s\n", (char*)graph_get_node_value(f), (char*)graph_get_node_value(c));
		graph_remove_edge(graph, f, c);
		graph_print(graph);

		printf("Rimozione: %s,%s\n", (char*)graph_get_node_value(g), (char*)graph_get_node_value(h));
		graph_remove_edge(graph, g, h);
		graph_print(graph);

		printf("Rimozione: %s,%s\n", (char*)graph_get_node_value(c), (char*)graph_get_node_value(d));
		graph_remove_edge(graph, c, d);
		graph_print(graph);

		printf("Aggiunta: %s,%s\n", (char*)graph_get_node_value(c), (char*)graph_get_node_value(f));
		graph_add_edge(graph, c, f);
		graph_print(graph);

		printf("Aggiunta: %s,%s\n", (char*)graph_get_node_value(d), (char*)graph_get_node_value(c));
		graph_add_edge(graph, d, c);
		graph_print(graph);
		printf("\n");

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(d));
		graph_remove_node(graph, d);
		graph_print(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(h));
		graph_remove_node(graph, h);
		graph_print(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(i));
		graph_remove_node(graph, i);
		graph_print(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(b));
		graph_remove_node(graph, b);
		graph_print(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(c));
		graph_remove_node(graph, c);
		graph_print(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(e));
		graph_remove_node(graph, e);
		graph_print(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(f));
		graph_remove_node(graph, f);
		graph_print(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(g));
		graph_remove_node(graph, g);
		printf("EMPTY GRAPH:\n");
		graph_print(graph);
		graph_delete(graph);
		printf("DONE\n");
	}
	else if (strcmp(argv[1], "sweep") == 0) {
		graph * graph = graph_new();

		graph_node * a = graph_add_node(graph, "a");
		graph_node * b = graph_add_node(graph, "b");
		graph_node * c = graph_add_node(graph, "c");
		graph_node * d = graph_add_node(graph, "d");
		graph_node * e = graph_add_node(graph, "e");
		graph_node * f = graph_add_node(graph, "f");
		graph_node * g = graph_add_node(graph, "g");
		graph_node * h = graph_add_node(graph, "h");

		graph_add_edge(graph, a, b);
		graph_add_edge(graph, a, f);
		graph_add_edge(graph, b, c);
		graph_add_edge(graph, b, f);
		graph_add_edge(graph, c, d);
		graph_add_edge(graph, d, b);
		graph_add_edge(graph, e, f);
		graph_add_edge(graph, f, c);
		graph_add_edge(graph, g, h);

		printf("Grafo\n\n");
		graph_print(graph);
		printf("\n");

		sweep(graph, "%s");

		graph_delete(graph);
	}
	else if (strcmp(argv[1], "top_sort") == 0) {
		graph * graph = graph_new();

		graph_node * a = graph_add_node(graph, "a");
		graph_node * b = graph_add_node(graph, "b");
		graph_node * c = graph_add_node(graph, "c");
		graph_node * d = graph_add_node(graph, "d");
		graph_node * e = graph_add_node(graph, "e");
		graph_node * f = graph_add_node(graph, "f");
		graph_node * g = graph_add_node(graph, "g");
		graph_node * h = graph_add_node(graph, "h");

		graph_add_edge(graph, a, b);
		graph_add_edge(graph, a, f);
		graph_add_edge(graph, b, c);
		graph_add_edge(graph, b, f);
		graph_add_edge(graph, c, d);
		graph_add_edge(graph, d, b);
		graph_add_edge(graph, e, f);
		graph_add_edge(graph, f, c);
		graph_add_edge(graph, g, h);

		printf("Grafo\n\n");
		graph_print(graph);
		printf("\n");

		printf("Primo tentativo: (dovrebbe fallire)\n");
		topological_sort(graph);

		printf("Rimozione arco (d,b)\n");
		graph_remove_edge(graph, d, b);

		printf("secondo tentativo: (dovrebbe riuscire)\n");
		topological_sort(graph);

		graph_delete(graph);
	}
	else if (strcmp(argv[1], "strong_cc") == 0) {
		graph * graph = graph_new();

		graph_node * a = graph_add_node(graph, "a");
		graph_node * b = graph_add_node(graph, "b");
		graph_node * c = graph_add_node(graph, "c");
		graph_node * d = graph_add_node(graph, "d");
		graph_node * e = graph_add_node(graph, "e");

		graph_add_edge(graph, a, c);
		graph_add_edge(graph, a, d);
		graph_add_edge(graph, b, a);
		graph_add_edge(graph, d, b);
		graph_add_edge(graph, e, c);
		
		printf("Grafo 1\n\n");
		graph_print(graph);
		printf("\n");

		strong_connected_components(graph);

		graph_delete(graph);
		
		graph = graph_new();

		a = graph_add_node(graph, "a");
		b = graph_add_node(graph, "b");
		c = graph_add_node(graph, "c");
		d = graph_add_node(graph, "d");
		e = graph_add_node(graph, "e");
		graph_node * f = graph_add_node(graph, "f");
		graph_node * g = graph_add_node(graph, "g");
		graph_node * h = graph_add_node(graph, "h");

		graph_add_edge(graph, a, b);
		graph_add_edge(graph, a, f);
		graph_add_edge(graph, b, c);
		graph_add_edge(graph, b, f);
		graph_add_edge(graph, c, d);
		graph_add_edge(graph, d, b);
		graph_add_edge(graph, e, f);
		graph_add_edge(graph, f, c);
		graph_add_edge(graph, g, h);
		
		printf("Grafo 2\n\n");
		graph_print(graph);
		printf("\n");

		strong_connected_components(graph);

		graph_delete(graph);

		graph = graph_new();

		a = graph_add_node(graph, "0");
		b = graph_add_node(graph, "1");
		c = graph_add_node(graph, "2");
		d = graph_add_node(graph, "3");
		e = graph_add_node(graph, "4");
		f = graph_add_node(graph, "5");
		g = graph_add_node(graph, "6");
		h = graph_add_node(graph, "7");
		graph_node * i = graph_add_node(graph, "8");

		// 0-1-2-3
		graph_add_edge(graph, a, b);
		graph_add_edge(graph, b, c);
		graph_add_edge(graph, c, d);
		graph_add_edge(graph, d, a);

		graph_add_edge(graph, c, e);

		// 4-5-6
		graph_add_edge(graph, e, f);
		graph_add_edge(graph, f, g);
		graph_add_edge(graph, g, e);

		graph_add_edge(graph, h, g);
		graph_add_edge(graph, h, i);


		
		printf("Grafo 3\n\n");
		graph_print(graph);
		printf("\n");

		strong_connected_components(graph);

		graph_delete(graph);
		
	}
	else{
        print_help();
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}