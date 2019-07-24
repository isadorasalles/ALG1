#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
#include "tarefa2.h"
#include "tarefa1.h"
#include <string.h>

int main(int argc, char const *argv[]){

    FILE *trilha = fopen(argv[2], "r");
    int src, dest;
    int num_vertices, num_arestas;
    fscanf(trilha, "%d %d", &num_vertices, &num_arestas);

    graph* graph = create_graph(num_vertices);
    graph->arestas = (edge_t *) malloc(num_arestas *sizeof(edge_t)); //aloca vetor de arestas
    
    for (int i=0; i < num_arestas; i++){
        fscanf(trilha, "%d %d", &src, &dest);  //leitura de cada caminho da trilha
        add_edge(graph, dest, src, i); // adiciona arestas no grafo
    }
    fclose(trilha); 

    if (strcmp(argv[1],"tarefa1") == 0)  // verifica qual tarefa deve ser atendida
        print_result_tarefa1(graph);
    else 
        print_result_tarefa2(graph);

    clear_graph(graph);
    return 0;
}