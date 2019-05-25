#ifndef UNIVERSIDADES
#define UNIVERSIDADES

#include "candidato.h"

typedef struct {
	int vagas;
	int nota_corte;
} universidade; 

universidade *alocar_universidades(char const *argv[]);
int *alocar_candidatos(FILE *candidatos_file, hash_table_t *hash, preferencias *pref, int num_candidatos, universidade *uni);

int *casamento_estavel(hash_table_t *hash, universidade *uni, preferencias *pref, int *notas, int num_candidatos, int n);
void inicializa_vetor(int *vector, int tam);
void imprime_saida(int *vector, int num_candidatos);



#endif