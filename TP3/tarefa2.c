#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "tarefa2.h"

void aproximative_vertex_cover(graph *G){
    for (int i=0; i<G->num_arestas; i++){ //caminha pela lista de arestas
        if ((G->visited[G->arestas[i].dest] == 0) && (G->visited[G->arestas[i].src] == 0)){  //verifica se os dois vertices nao estao na cobertura
                // colore os vertices que farao parte do vertex cover e incrementa o vertex cover em 2
                G->visited[G->arestas[i].dest] = 1;  
                G->visited[G->arestas[i].src] = 1;
                G->vc+=2;
            }
    }
}


void print_result_tarefa2(graph *G){
    aproximative_vertex_cover(G);
    
    printf("%d\n", G->vc);
    for (int i=0; i<G->num_vertices; i++){
        if(G->visited[i]== 1){
            printf("%d\n", i);
        }
    }
}

