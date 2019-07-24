#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int distanceEarthKm(double lat1d, double lon1d, double lat2d, double lon2d);

int main(int argc, char const *argv[]){
    int num_vertices;
    FILE *cidades = fopen(argv[1], "r");
    fscanf(cidades, "%d", &num_vertices); //leitura do numero de telescopios, ou seja, vertices

    double coordenadas[num_vertices][2];

    for (int i=0; i < num_vertices; i++){
        fscanf(cidades, "%lf %lf", &coordenadas[i][0], &coordenadas[i][1]);  //leitura das posicoes de cada telescopio
    }
    fclose(cidades);  

    int num_arestas = (num_vertices * (num_vertices - 1))/2; 

	graph* graph = create_graph(num_vertices); //cria grafo original
    graph->arestas = (edge_t *) malloc(num_arestas *sizeof(edge_t)); //aloca vetor de arestas

    int k = 0;
    //como o grafo e completo, cada vertice se conecta com todos os outros, sendo assim abaixo temos a insercao das arestas na adjlist do grafo:
    for (int i=0; i<num_vertices; i++)  
        for(int j=i+1; j<num_vertices; j++){
            graph->arestas[k].edge = distanceEarthKm(coordenadas[i][0], coordenadas[i][1], coordenadas[j][0], coordenadas[j][1]);
            graph->arestas[k].src = i;
            graph->arestas[k].dest = j;
            add_edge(graph, i, j, graph->arestas[k].edge);
            k++;
        }
    
    
    printf("%d\n", Camerine(graph, num_arestas, num_vertices));  //chama a funcao de camerine e printa ta tela o valor da bottleneck
    
    clear_graph(graph);  //deleta o grafo
    
    
    return 0;
}

