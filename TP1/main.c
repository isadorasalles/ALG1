#include <stdio.h>
#include <stdlib.h>
#include "candidato.h"
#include "universidades.h"

#define MAIOR_NOTA 1000

int main(int argc, char const *argv[]){

	int i, num_candidatos;
	universidade *uni = alocar_universidades(argv);  //leitura e criacao da estrutura que armazena os dados das universidades

	FILE *candidatos_file = fopen(argv[2] , "r");
	fscanf (candidatos_file, "%d", &num_candidatos); //inicia a leitura do arquivo de candidatos
	
	preferencias *pref = (preferencias *) malloc (num_candidatos * sizeof(preferencias)); //aloca vetor de listas, que ira armazenar as prioridades de cada candidato

	hash_table_t *hash_notas = createTable(MAIOR_NOTA); //criacao da estrutura que vai armazenar uma lista de candidatos que tiraram cada nota

	//termina a leitura do arquivo de candidatos e faz a alocacao dos mesmos nas universidades, retornando um vetor que representa o casamento estavel
  	int *casamento = alocar_candidatos(candidatos_file, hash_notas, pref, num_candidatos, uni); 
  
  	imprime_saida(casamento, num_candidatos); //printa na tela a saida na formatacao desejada

  	limpar_hash(hash_notas, MAIOR_NOTA);

  	for (i = 0; i < num_candidatos; i++){
  		clear_list(pref[i].list_pref);
  	}	

  	free(pref);
  	free(uni);
  	free(casamento);

	return 0; 
}
