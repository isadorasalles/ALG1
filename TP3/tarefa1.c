#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "tarefa1.h"

void dfs(graph *grafo, int pai, int k) {

	if (grafo->visited[k] == 1)  //se o vertice ja foi visitado, retorna  
		return;
	
	grafo->visited[k] = 1;  //cor 1 indica que o vertice ja foi visitado

	if (grafo->adjlist[k] == NULL)
		return;
	node *aux = grafo->adjlist[k];
	while(aux != NULL) {
		// para cada aresta, se o vertice nao foi visitado, chama dfs para ele
		if (grafo->visited[aux->dest] == 0){
			dfs(grafo, k, aux->dest);
		}
		aux = aux->next;
	}
	if (grafo->visited[k] == 1){  //se o vertice foi visitado na dfs porem ainda nao esta coberto
		if (grafo->adjlist[pai] != NULL){ // se possui pai
            grafo->visited[pai] = 3; // o pai fara parte do vertex cover
		    grafo->visited[k] = 2; // marca como coberto o filho
        }
        else 
		    grafo->visited[k] = 3; // se nao possui pai e nao esta coberto, ele mesmo fara parte do vertex cover
    }
}


void print_result_tarefa1(graph *G){
    dfs(G, 0, 0);
    for (int i=0; i<G->num_vertices; i++){
        if(G->visited[i] == 3) // conta o numero de vertices que pertence ao vertex cover
          G->vc++;
    }
    printf("%d\n", G->vc); 
}

void print_vis(graph *G){
     for (int i=0; i<G->num_vertices; i++){
        printf("%d ", G->visited[i]);
     }
    printf("\n");
}
