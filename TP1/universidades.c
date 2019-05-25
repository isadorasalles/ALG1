#include <stdlib.h>
#include <stdio.h>
#include "universidades.h"
#include "candidato.h"

universidade *alocar_universidades(char const *argv[]){
	FILE *universidades_file = fopen(argv[1], "r");
	int num_universidades, i;
	fscanf(universidades_file, "%d", &num_universidades);
	universidade *vector = (universidade *) malloc(num_universidades * sizeof(universidade));

	for (i = 0; i < num_universidades; i++){
		fscanf(universidades_file, "%d %d", &vector[i].vagas, &vector[i].nota_corte);
	}

	fclose(universidades_file);

	return vector;
}

int *alocar_candidatos(FILE *candidatos_file, hash_table_t *hash, preferencias *pref, int num_candidatos, universidade *uni){
	int num_pref, nota, aux;
	int i, j, k = 0;
	int notas[num_candidatos];
	inicializa_vetor(notas, num_candidatos);

	for (i = 0; i < num_candidatos; i++){
		fscanf (candidatos_file, "%d %d", &num_pref, &nota);

		if (hash->entries[nota] == NULL){ //se nao existe nenhum cadidato com essa nota na tabela hash
			notas[k] = nota;	//acrescente a nota ao vetor de notas (de forma a criar um vetor sem valores repetidos)
			k++;
		}
		hashPut(hash, nota, i+1);  
		pref[i].list_pref = create_list();

		for (j = 0; j < num_pref; j++){ //loop para preencher a lista de prioridades de cada candidato
			fscanf (candidatos_file, "%d ", &aux);
			insert_list(pref[i].list_pref, aux, nota);
			
		}
	}
	
	fclose(candidatos_file);

	quickSort(notas, 0, k, k-1); //ordenar o vetor de notas de forma decrescente

  	int *stable_matching = casamento_estavel(hash, uni, pref, notas, num_candidatos, k);


  	return stable_matching;

} 

int *casamento_estavel(hash_table_t *hash, universidade *uni, preferencias *pref, int *notas, int num_candidatos, int n){
	int i, k, num_elements;
	int *casamento = (int *) malloc (num_candidatos * sizeof(int));
	inicializa_vetor(casamento, num_candidatos);
	lista_t *busca;
	node_t *aux_busca;
	lista_t *pref_candidato;

	for (i = 0; i < n; i++){  //caminha pelo vetor de notas
		busca = hashGet(hash, notas[i]);  //busca no hash a lista de candidatos que tiraram a nota em questao

		while (busca->start != NULL){ //para quando todos os candidatos da lista em questao forem alocados ou se ja percorreu toda as prioridades e nao conseguiu alocar
			num_elements = busca->num_elements;
			aux_busca = busca->start; 

			for (k = 0; k < num_elements; k++) { //caminha pela lista de candidatos
				pref_candidato = pref[aux_busca->value-1].list_pref;

				if (pref_candidato->start != NULL){ //verifica se a lista de preferencias do candidato nao esta vazia
					//se o candidato atende ao requisito de nota e a universidade tem vagas, aloque-o nela
					if((uni[pref_candidato->start->value-1].vagas >= 1)&&(notas[i] >= uni[pref_candidato->start->value-1].nota_corte)){
						casamento[aux_busca->value-1] = pref_candidato->start->value;
						uni[pref_candidato->start->value-1].vagas -=1;
						hashRemove(hash, notas[i], k); //remove o candidato do hash pois o mesmo esta alocado
						break;
					}
					else {
						remove_element(pref_candidato, 0); //caso o candidadto nao possa ser alocado na universidade, remova-a da sua lista de preferencias
					}
				}
				else {
					hashRemove(hash, notas[i], k); //remove o candidato do hash pois o mesmo nao pode ser alocado, ocorre quando a lista de preferencias acaba
					break;
				}

				aux_busca = aux_busca->next; 

			}

			busca = hashGet(hash, notas[i]); 
		}
	}
	
	return casamento;

}

void inicializa_vetor(int *vector, int tam){
	int i;
	for (i = 0; i < tam; i++){
		vector[i] = 0;
	}

}

void imprime_saida(int *vector, int num_candidatos){
	int i = 0;
	printf("Grupos com alocacao\n");  
	for (i = 0; i < num_candidatos; i++){
		if(vector[i] != 0){  //quando ha um numero no vetor significa que o candidato foi alocado
			printf ("%d %d\n", i+1, vector[i]);
		}
	}
	printf("Candidatos nao alocados\n");
	for (i = 0; i < num_candidatos; i++){
		if(vector[i] == 0){
			printf("%d\n", i+1);
		}
	}
}
