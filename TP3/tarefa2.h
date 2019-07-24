#ifndef TAREFA2_H
#define TAREFA2_H

#include "graph.h"

void aproximative_vertex_cover(graph *G);
void remove_edges(graph *G, int k);
void remove_element (graph *G, int k, int i);
void print_result_tarefa2(graph *G);

#endif