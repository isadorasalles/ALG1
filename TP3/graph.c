#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

node *create_node(int dest){  //cria um vertice
	node *vertice = (node *) malloc(sizeof(node));
	vertice->dest= dest;
	vertice->next = NULL;

	return vertice;
}

graph *create_graph(int num_vertices){ 
	graph *grafo = (graph *) malloc(sizeof(graph));
	grafo->vc = 0;
	grafo->num_vertices = num_vertices;
	grafo->adjlist = (node **) malloc(num_vertices * sizeof(node *));  //cria uma lista de adjacencia para o grafo
	grafo->visited = (int *) malloc(num_vertices * sizeof(int));
	grafo->num_arestas = 0;

	int i;
	for (i = 0; i < num_vertices; i++){
		grafo->adjlist[i] = NULL;
		grafo->visited[i] = 0;
	}

	return grafo;
} 

void add_edge(graph *grafo, int dest, int src, int i){   
	if (dest != src){  //if usado para garantir que nao haja insercao de arestas de um vertice para ele mesmo
		//grafo nao direcionado temos colocar a aresta dos dois lados
		node *newnode = create_node(dest);
		newnode->next = grafo->adjlist[src];
		grafo->adjlist[src] = newnode;

		newnode = create_node(src);
		newnode->next = grafo->adjlist[dest];
		grafo->adjlist[dest] = newnode;
		
		grafo->arestas[i].dest = dest;
		grafo->arestas[i].src = src;
		grafo->num_arestas++; //com a adicao de uma aresta o numero de arestas do grafo incrementa
	}

}

void clear_graph(graph *graph){
    for(int i = 0; i < graph->num_vertices; i++){
        node *toVisit = graph->adjlist[i];

        while(toVisit != NULL){
            node *toFree = toVisit;
            toVisit = toVisit->next;
            free(toFree);
        }    
    }
    free(graph->adjlist);
    free(graph->visited);
	free(graph->arestas);
    free(graph);
}

