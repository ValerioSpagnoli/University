#ifndef __GRAPH_SERVICES__
#define __GRAPH_SERVICES__

#include "graph.h"

void sweep(graph * g, char * format_string);
void topological_sort(graph *g);
void strong_connected_components(graph *g);

#endif // !__GRAPH_SERVICES__

