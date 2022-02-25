#ifndef __GRAPH_H__
#define	__GRAPH_H__

#include "linked_list.h"
#include <stdio.h>

typedef struct graph graph;
typedef struct graph_node graph_node;

graph * graph_new();
linked_list * graph_get_nodes(graph * g);
linked_list * graph_get_neighbors(graph * g, graph_node * n);
graph_node * graph_add_node(graph * g, void * value);
void graph_add_edge(graph * g, graph_node * from, graph_node * to);
void * graph_get_node_value(graph_node * n);
void graph_remove_edge(graph* g, graph_node* v1, graph_node* v2);
void graph_remove_node(graph* g, graph_node* v);
void graph_delete(graph * h);
graph* graph_read_ff(FILE* input);
void graph_print(graph* g);
void graph_print_adj(graph* g);
int graph_n_con_comp(graph *);
linked_list* graph_get_con_comp(graph*);

#endif	/* __GRAPH_H__ */

