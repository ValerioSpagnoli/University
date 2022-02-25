#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

typedef enum {UNEXPLORED, EXPLORED, EXPLORING} STATUS;

struct graph_node{
    void * value;
    linked_list * out_edges;

    // keep track status
    STATUS state;
    int timestamp;
};

struct graph{
    linked_list * nodes;
};

graph * graph_new() {
	return NULL;
}

linked_list * graph_get_nodes(graph * g) {
	return NULL;
}

linked_list * graph_get_neighbors(graph * g, graph_node * n) {
	return NULL;
}

graph_node * graph_add_node(graph * g, void * value) {
	return NULL;
}

void graph_add_edge(graph * g, graph_node * v1, graph_node * v2) {
    
}

void * graph_get_node_value(graph_node * n) {
	return NULL;
}

void graph_remove_edge(graph* g, graph_node* v1, graph_node* v2) {

}

void graph_remove_node(graph* g, graph_node* v) {

}

void graph_delete(graph * g) {

}

graph* graph_read_ff(FILE* input) {
	return NULL;
}

void graph_print(graph* g) {

}

void graph_print_adj(graph* g) {

}


int graph_n_con_comp(graph * g) {
	return 0;
}

linked_list* graph_get_con_comp(graph* g) {
	return NULL;
}
