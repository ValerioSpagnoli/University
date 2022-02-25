#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"
#include "graph.h"

void print_help() {
    printf("Richiesto argomento: {graph, input, conta_comp, get_comp, list}\n");
}

int main(int argc, char** argv) {
	if (argc != 2) {
		print_help();
		return EXIT_FAILURE;
	}
	if (strcmp(argv[1], "graph") == 0) {
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

		graph_add_edge(graph, a, b);
		graph_add_edge(graph, a, f);
		graph_add_edge(graph, b, c);
		graph_add_edge(graph, b, f);
		graph_add_edge(graph, c, d);
		graph_add_edge(graph, d, b);
		graph_add_edge(graph, e, f);
		graph_add_edge(graph, f, c);
		graph_add_edge(graph, g, h);

		printf("Grafo iniziale\n\n");
		graph_print_adj(graph);
		printf("\n");
		printf("Rimozione: %s,%s\n", (char*)graph_get_node_value(f), (char*)graph_get_node_value(c));
		graph_remove_edge(graph, f, c);
		graph_print_adj(graph);

		printf("Rimozione: %s,%s\n", (char*)graph_get_node_value(c), (char*)graph_get_node_value(b));
		graph_remove_edge(graph, c, b);
		graph_print_adj(graph);

		printf("Rimozione: %s,%s\n", (char*)graph_get_node_value(d), (char*)graph_get_node_value(c));
		graph_remove_edge(graph, d, c);
		graph_print_adj(graph);

		printf("Aggiunta: %s,%s\n", (char*)graph_get_node_value(c), (char*)graph_get_node_value(f));
		graph_add_edge(graph, c, f);
		graph_print_adj(graph);

		printf("Aggiunta: %s,%s\n", (char*)graph_get_node_value(d), (char*)graph_get_node_value(c));
		graph_add_edge(graph, d, c);
		graph_print_adj(graph);
		printf("\n");

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(d));
		graph_remove_node(graph, d);
		graph_print_adj(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(a));
		graph_remove_node(graph, a);
		graph_print_adj(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(h));
		graph_remove_node(graph, h);
		graph_print_adj(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(i));
		graph_remove_node(graph, i);
		graph_print_adj(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(b));
		graph_remove_node(graph, b);
		graph_print_adj(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(c));
		graph_remove_node(graph, c);
		graph_print_adj(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(e));
		graph_remove_node(graph, e);
		graph_print_adj(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(f));
		graph_remove_node(graph, f);
		graph_print_adj(graph);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(g));
		graph_remove_node(graph, g);
		printf("EMPTY GRAPH:\n");
		graph_print_adj(graph);

		printf("DONE\n");
		graph_delete(graph);
	}
	else if (strcmp(argv[1], "input") == 0) {
		FILE* fp = fopen("graph.in", "r");
		if (fp == NULL) {
			fprintf(stderr, "Errore nella lettura del file\n");
			return 1;
		}
		graph* g = graph_read_ff(fp);
		fclose(fp);
		printf("Rappresentazione ad archi: \n");
		graph_print(g);
		printf("\n");
		printf("Rappresentazione delle adiacenze: \n");
		graph_print_adj(g);
		printf("\n");
		graph_delete(g);
	}
	else if (strcmp(argv[1], "list") == 0) {
		linked_list* lista = linked_list_new();
		linked_list_add(lista, "1");
		linked_list_add(lista, "2");
		linked_list_add(lista, "3");
		linked_list_add(lista, "4");
		linked_list_add(lista, "5");
		linked_list_iterator * it = linked_list_iterator_new(lista);
		for (; it;) {
			linked_list_iterator *itera = linked_list_iterator_next(it);
			printf("%s\n", (char*)linked_list_iterator_getvalue(it));
			it = itera;
		}
		printf("DONE\n");
		linked_list_delete(lista);
	}
	else if (strcmp(argv[1], "conta_comp") == 0){
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

		graph_add_edge(graph, a, b);
		graph_add_edge(graph, a, f);
		graph_add_edge(graph, b, c);
		graph_add_edge(graph, b, f);
		graph_add_edge(graph, c, d);
		graph_add_edge(graph, d, b);
		graph_add_edge(graph, e, f);
		graph_add_edge(graph, f, c);
		graph_add_edge(graph, g, h);

		graph_print_adj(graph);
		int cc = graph_n_con_comp(graph);
		printf("Il grafo ha %d componenti connesse\n", cc);
	}
	else if (strcmp(argv[1], "get_comp") == 0) {
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

		graph_add_edge(graph, a, b);
		graph_add_edge(graph, a, f);
		graph_add_edge(graph, b, c);
		graph_add_edge(graph, b, f);
		graph_add_edge(graph, c, d);
		graph_add_edge(graph, d, b);
		graph_add_edge(graph, e, f);
		graph_add_edge(graph, f, c);
		graph_add_edge(graph, g, h);

		graph_print_adj(graph);
		linked_list* cc = graph_get_con_comp(graph);
		linked_list_iterator * it = linked_list_iterator_new(cc);
		for (int i = 1; it; i++) {
			linked_list_iterator *itera = linked_list_iterator_next(it);
			printf("Sottografo %d:\n", i);
			graph_print_adj(linked_list_iterator_getvalue(it));
			it = itera;
		}
	}
	else{
        print_help();
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}