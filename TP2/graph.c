#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

node *create_node(int dest, int weight){  //cria um vertice
	node *vertice = (node *) malloc(sizeof(node));
	vertice->dest= dest;
	vertice->weight = weight;
	vertice->next = NULL;

	return vertice;
}

graph *create_graph(int num_vertices){ 
	graph *grafo = (graph *) malloc(sizeof(graph));
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

void add_edge(graph *grafo, int dest, int src, int weight){   
	if (dest != src){  //if usado para garantir que nao haja insercao de arestas de um vertice para ele mesmo
		//grafo nao direcionado temos colocar a aresta dos dois lados
		node *newnode = create_node(dest, weight);
		newnode->next = grafo->adjlist[src];
		grafo->adjlist[src] = newnode;

		newnode = create_node(src, weight);
		newnode->next = grafo->adjlist[dest];
		grafo->adjlist[dest] = newnode;

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


void dfs(graph *grafo, int* vis, int k, int cor) {

	if (grafo->visited[k] == 1)  //se o vertice ja foi visitado, retorna  
		return;
	
	grafo->visited[k] = 1;
	vis[k] = cor;  //colore um vetor que indica quantos componentes conexos existem no grafo

	if (grafo->adjlist[k] == NULL)
		return;

	node *aux = grafo->adjlist[k];
	while(aux != NULL) {
		// para cada aresta, se o vertice nao foi visitado, chama dfs para ele
		if (grafo->visited[aux->dest] != 1){
			dfs(grafo, vis, aux->dest, cor);
		}
			aux = aux->next;
	}

}


edge_t *merge (edge_t *left, edge_t *right, int tam_l, int tam_r){  //funcao de juncao utilizada pelo mergeSort para junta dois vetores ja ordenados
	edge_t *result = (edge_t *) malloc ((tam_l+tam_r)*sizeof (edge_t));
	int i=0;
	int j=0;
	int k=0;
	while (i<tam_l && j<tam_r){
		if (left[i].edge < right[j].edge) {
			result[k] = left[i];
			i++;
			}
		else {
			result[k] = right[j];
			j++;
			}
		k++;
	}
	if (k<tam_l + tam_r){
		for (; i<tam_l; i++){
			result[k] = left[i];
			k++;
		}
		for (; j<tam_r; j++){
			result[k] = right[j];
			k++;
		}
	}
	return result;
}

edge_t *mergeSort(edge_t* vector, int start, int end){ //realiza a ordenacao de um vetor
	edge_t *result;
	if (end == start){
		result = (edge_t *) malloc (1*sizeof(edge_t));
		result[0] = vector[start];
		return result;
	}
	int mid = (end+start)/2;
	edge_t *left = mergeSort (vector, start, mid);
	edge_t *right = mergeSort (vector, mid+1, end);
	result = merge(left, right, mid-start+1, end-mid);
	free(left);
	free(right);
	return result;
}

int mom_select(edge_t* arestas, int num_arestas){
	//separar n grupos de 5 elementos
	int num_grupos = num_arestas/5;   
    edge_t median_grupos[num_grupos];  
    edge_t Grupos[5];
    
    int retorno;
    if (num_arestas <= 5){
    	if (num_arestas > 1){
    		edge_t *result = mergeSort(arestas, 0, num_arestas-1); 
    		retorno = result[num_arestas/2].edge;
    		free(result);
    		return retorno; 
    	}
    	else
    		return arestas[0].edge;
    }

  
    for (int i=0; i < num_grupos; i++){  //para cada 5 elementos realiza o mergeSort e encontra a mediana do conjunto
    	for (int j= 0; j < 5; j++)
    		Grupos[j] = arestas[5*i+j];

        edge_t *result = mergeSort(Grupos, 0, 4);
        median_grupos[i] = result[2]; //armazena a mediana de cada grupo
        free(result);
    }
    
    return mom_select(median_grupos, num_grupos);
}

edge_t* separate_vector(edge_t* arestas, int median, int num_arestas, int* position){ //funcao usada para colocar a mediana na posicao devida, de pivot
	edge_t *separated = (edge_t *) malloc (num_arestas * sizeof(edge_t));
	edge_t *medians = (edge_t *) malloc (num_arestas * sizeof(edge_t));

	int k = 0;
	int j = num_arestas-1;
	int count = 0; //contar quantos valores sao iguais a mediana

	for (int i = 0; i < num_arestas; i++){
		if (arestas[i].edge < median){
			separated[k] = arestas[i];
			k++;
		}
		if (arestas[i].edge > median){
			separated[j] = arestas[i];
			j--; 
		}
		if (arestas[i].edge == median){ //forma de tratar quando existe mais de um valor igual a mediana
			medians[count] = arestas[i];
			count++;
		}
	}
	for (int i = 0; i < count; i++)
		separated[k+i] = medians[i];  //insere os valores iguais a mediana depois, nos espacos restantes
	

	*position = k; //atualiza a posicao da mediana

	if (*position < num_arestas/2){ //quando temos que decidir quais das arestas iguais sera a mediana buscamos escolher a maia proxima do centro
		while ((count > 1)&&(*position <= num_arestas/2)){ //testar para mais de uma aresta igual a mediana
			count--;
			*position+=1;
		}
	}

	free(medians);
	return separated;
} 

graph *create_subgraph(int num_vertices, int* vis, edge_t* arestas, int median, int begin, int num_arestas){
    graph* sub = create_graph(num_vertices);
    
    int i = 0;
    if (begin == 0){ //nesse caso sera criado o subgrafo B que possui todas as arestas menores que a mediana
        while(arestas[i].edge <= median){
            if (i >= num_arestas) 
                break;
            add_edge(sub, arestas[i].src, arestas[i].dest, arestas[i].edge);
            i++;
        }
        sub->arestas = (edge_t *) malloc(sub->num_arestas *sizeof(edge_t));
        separe_edges(sub, arestas, 0, num_arestas, vis); 
    }
    else { //neste caso sera criado o subgrafo A, que contem supervertices e a possibilidade de ter mais de uma aresta entre eles
        i = begin;
        while (i < num_arestas){ 
            int j = arestas[i].src;
            int k = arestas[i].dest;
           	add_edge(sub, vis[j], vis[k], arestas[i].edge);
            i++;
        }
        
        sub->arestas = (edge_t *) malloc(sub->num_arestas *sizeof(edge_t)); //porque o numero de arestas devera excluir arestas entre o mesmo componente conexo
        separe_edges(sub, arestas, begin, num_arestas, vis);;
    }

    return sub;    
}


int Camerine(graph* grafo, int num_arestas, int num_vertices){ //colocar grafo aqui 
    if (num_arestas == 1){ //condicao de parada e encontrarmos apenas uma aresta
    	int retorno = grafo->arestas[0].edge;
        return retorno;
    }
    
    int bottleneck;
    int median = mom_select(grafo->arestas, grafo->num_arestas); //encontre a mediana dos valores
    int position = num_arestas/2;
    edge_t* vector = separate_vector(grafo->arestas, median, num_arestas, &position); //retorne um vetor com a mediana no seu lugar de pivot
    
    int vis[num_vertices];
    for (int i = 0; i < num_vertices; i++){ //inicializa um vetor de visitados
        vis[i] = -1;
    }

    graph* GB = create_subgraph(num_vertices, vis, vector, median, 0, position); //cria um subgrafo induzido para as arestas da esquerda do mediana
 
    int cor = -1;
    for(int i = 0; i < num_vertices; i++){ //encontra componentes conexas
        if (vis[i] == -1){
            cor++;
            dfs(GB, vis, i, cor);
        }
    }

    graph* GA = create_subgraph(cor+1, vis, vector, median, position, num_arestas); //cria um subgrafo induzido para as arestas a dieita da mediana

    if (cor > 0)  //se GB for um grafo desconexo
        bottleneck = Camerine(GA, GA->num_arestas, cor+1);
     
    
    else 
        bottleneck =  Camerine(GB, GB->num_arestas, num_vertices);

    free(vector);
    clear_graph(GA);
    clear_graph(GB);
    return bottleneck;

}

void separe_edges(graph* G, edge_t* vector, int begin, int end, int* vis){ //separa qual parte pertence ao grupo de valores a esquerda da mediana e a parte da direita
	
    int k = 0;
    if (begin == 0){ //quando temos apenas um componente conexo
    	for (int i = begin; i < end; i++){
    		G->arestas[i] = vector[i];
       		k++;
    	}
    }
    else {
    	for (int i = begin; i < end; i++){
    		if(vis[vector[i].dest] != vis[vector[i].src]){  //desconsiderar arestas que conectam o mesmo componente conexo
      			G->arestas[k].edge = vector[i].edge;
       			G->arestas[k].dest = vis[vector[i].dest];
       			G->arestas[k].src = vis[vector[i].src];
       			k++;
       		}
    	}
    }
    
}