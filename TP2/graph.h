#ifndef GRAPH_H
#define GRAPH_H

typedef struct{
	int edge;
	int dest;
	int src;
} edge_t; 

typedef struct no{
	int dest;
	int weight;
	struct no *next;
} node;

typedef struct {
	int num_vertices;
	int num_arestas;
	node **adjlist;
	int *visited;
	edge_t *arestas; //vetor usado para facilitar as operacoes no calcula da mediana
} graph;

node *create_node(int dest, int weight);
graph *create_graph(int num_vertices);
void add_edge(graph *grafo, int dest, int src, int weight);
void clear_graph(graph *grafo);
void dfs(graph *grafo, int* vis, int k, int cor);

edge_t *merge (edge_t *left, edge_t *right, int tam_l, int tam_r);
edge_t *mergeSort(edge_t* vector, int start, int end);
int mom_select(edge_t* arestas, int num_arestas);
edge_t* separate_vector(edge_t* arestas, int median, int num_arestas, int* position);
graph *create_subgraph(int num_vertices, int* vis, edge_t* arestas, int median,  int begin, int num_arestas);
int Camerine(graph* grafo, int num_arestas, int num_vertices);
void separe_edges(graph* G, edge_t* vector, int begin, int end, int *vis);

#endif