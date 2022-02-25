#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "graph_services.h"

void print_help() {
	printf("Richiesto argomento: {graph, bfs, sssp, mst}\n");
}

int main(int argc, char** argv) {
	if (argc != 2) {
		print_help();
		return EXIT_FAILURE;
	}
	else if (strcmp(argv[1], "graph") == 0) {
		graph *gra = graph_new();

		graph_node *a = graph_add_node(gra, "a");
		graph_node *b = graph_add_node(gra, "b");
		graph_node *c = graph_add_node(gra, "c");
		graph_node *d = graph_add_node(gra, "d");
		graph_node *e = graph_add_node(gra, "e");
		graph_node *f = graph_add_node(gra, "f");

		graph_add_edge(gra, a, b, 2);
		graph_add_edge(gra, a, c, 1);
		graph_add_edge(gra, a, d, 5);
		graph_add_edge(gra, b, c, 2);
		graph_add_edge(gra, b, d, 3);
		graph_add_edge(gra, c, d, 2);
		graph_add_edge(gra, c, e, 1);
		graph_add_edge(gra, e, d, 1);
		graph_add_edge(gra, d, f, 5);
		graph_add_edge(gra, e, f, 2);

		printf("Grafo iniziale\n\n");
		graph_print(gra);
		printf("\n");

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(a));
		graph_remove_node(gra, a);
		graph_print(gra);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(e));
		graph_remove_node(gra, e);
		graph_print(gra);

		printf("Rimozione: %s,%s\n", (char*)graph_get_node_value(c), (char*)graph_get_node_value(d));
		graph_remove_edge(gra, c, d);
		graph_print(gra);

		printf("Aggiunta: %s,%s\n", (char*)graph_get_node_value(c), (char*)graph_get_node_value(f));
		graph_add_edge(gra, c, f, 3);
		graph_print(gra);

		printf("Aggiunta: %s,%s\n", (char*)graph_get_node_value(d), (char*)graph_get_node_value(c));
		graph_add_edge(gra, d, c, 4);
		graph_print(gra);
		printf("\n");

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(d));
		graph_remove_node(gra, d);
		graph_print(gra);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(b));
		graph_remove_node(gra, b);
		graph_print(gra);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(c));
		graph_remove_node(gra, c);
		graph_print(gra);

		printf("Rimozione nodo: %s\n", (char*)graph_get_node_value(f));
		graph_remove_node(gra, f);
		graph_print(gra);

		printf("EMPTY GRAPH:\n");
		graph_print(gra);
		graph_delete(gra);
		printf("DONE\n");

		return (EXIT_SUCCESS);
	}
	else if (strcmp(argv[1], "bfs") == 0) {
		graph *gra = graph_new();

		graph_node *a = graph_add_node(gra, "a");
		graph_node *b = graph_add_node(gra, "b");
		graph_node *c = graph_add_node(gra, "c");
		graph_node *d = graph_add_node(gra, "d");
		graph_node *e = graph_add_node(gra, "e");
		graph_node *f = graph_add_node(gra, "f");

		graph_add_edge(gra, a, b, 2);
		graph_add_edge(gra, a, c, 1);
		graph_add_edge(gra, a, d, 5);
		graph_add_edge(gra, b, c, 2);
		graph_add_edge(gra, b, d, 3);
		graph_add_edge(gra, c, d, 2);
		graph_add_edge(gra, c, e, 1);
		graph_add_edge(gra, e, d, 1);
		graph_add_edge(gra, d, f, 5);
		graph_add_edge(gra, e, f, 2);

		printf("Grafo:\n\n");
		graph_print(gra);
		printf("\n");

		bfs(gra);

		graph_delete(gra);
	}
	else if (strcmp(argv[1], "sssp") == 0) {
		graph *gra = graph_new();

		graph_node *a = graph_add_node(gra, "a");
		graph_node *b = graph_add_node(gra, "b");
		graph_node *c = graph_add_node(gra, "c");
		graph_node *d = graph_add_node(gra, "d");
		graph_node *e = graph_add_node(gra, "e");
		graph_node *f = graph_add_node(gra, "f");

		graph_add_edge(gra, a, b, 2);
		graph_add_edge(gra, a, c, 1);
		graph_add_edge(gra, a, d, 5);
		graph_add_edge(gra, b, c, 2);
		graph_add_edge(gra, b, d, 3);
		graph_add_edge(gra, c, d, 2);
		graph_add_edge(gra, c, e, 1);
		graph_add_edge(gra, e, d, 1);
		graph_add_edge(gra, d, f, 5);
		graph_add_edge(gra, e, f, 2);

		printf("Grafo:\n");
		graph_print(gra);
		printf("\n");

		printf("SSSP dal nodo 'a':\n");
		single_source_shortest_path(gra, a);

		graph_delete(gra);
	}
	else if (strcmp(argv[1], "mst") == 0) {
		// MST e' generalmente definito per grafi non diretti
		// Modifichiamo il grafo rendendolo indiretto e pesato

		graph *gra = graph_new();

		graph_node *a = graph_add_node(gra, "a");
		graph_node *b = graph_add_node(gra, "b");
		graph_node *c = graph_add_node(gra, "c");
		graph_node *d = graph_add_node(gra, "d");
		graph_node *e = graph_add_node(gra, "e");
		graph_node *f = graph_add_node(gra, "f");

		graph_add_edge(gra, a, b, 2);
		graph_add_edge(gra, b, a, 2);
		graph_add_edge(gra, a, c, 1);
		graph_add_edge(gra, c, a, 1);
		graph_add_edge(gra, a, d, 5);
		graph_add_edge(gra, d, a, 5);
		graph_add_edge(gra, b, c, 2);
		graph_add_edge(gra, c, b, 2);
		graph_add_edge(gra, b, d, 3);
		graph_add_edge(gra, d, b, 3);
		graph_add_edge(gra, c, d, 2);
		graph_add_edge(gra, d, c, 2);
		graph_add_edge(gra, c, e, 1);
		graph_add_edge(gra, e, c, 1);
		graph_add_edge(gra, e, d, 1);
		graph_add_edge(gra, d, e, 1);
		graph_add_edge(gra, d, f, 5);
		graph_add_edge(gra, f, d, 5);
		graph_add_edge(gra, e, f, 2);
		graph_add_edge(gra, f, e, 2);

		printf("Grafo:\n");
		graph_print(gra);
		printf("\n");

		printf("MST:\n");
		mst(gra);

		graph_delete(gra);
	}
}

