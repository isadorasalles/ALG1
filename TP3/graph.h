#ifndef GRAPH_H
#define GRAPH_H

typedef struct{
	int dest;
	int src;
} edge_t; 

typedef struct no{
	int dest;
	struct no *next;
} node;

typedef struct {
	int vc;
	int num_vertices;
	int num_arestas;
	node **adjlist;
	int *visited;
	edge_t *arestas; //vetor usado para facilitar as operacoes da tarefa2
} graph;

node *create_node(int dest);
graph *create_graph(int num_vertices);
void add_edge(graph *grafo, int dest, int src, int i);
void clear_graph(graph *grafo);
void dfs(graph *grafo, int pai, int k);



#endif
