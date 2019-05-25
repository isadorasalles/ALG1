#include <stdlib.h>
#include <stdio.h>
#include "candidato.h"
//#include <math.h>


lista_t *create_list (){
	lista_t *list = (lista_t *) malloc (sizeof(lista_t));
	list->start = NULL;
	list->end = NULL;
	list->num_elements = 0;
	return list;
}

void insert_list (lista_t *list, int value, int hashKey){
	node_t *N = (node_t *) malloc (sizeof(node_t));
	N->value = value;
	N->next = NULL;
	N->hashKey = hashKey;
	if (list->start == NULL) list->start = N;
	else list->end->next = N;
	list->end = N;
	list->num_elements++;
}


void remove_element (lista_t *list, int i){
	node_t *toFree = list->start;
	node_t *prev = NULL;
	int j=0;

	while ((j<i)&&(toFree!=NULL)){
		prev = toFree;
		toFree = toFree->next;
		j++;
	}
	if (toFree == NULL) return;
	if (toFree == list->start) 
		list->start = toFree->next;
	
	if (toFree == list->end)
		list->end = prev;
	
	
	if (prev!= NULL)
		prev->next = toFree->next;
	free(toFree);

	list->num_elements--;


}

void clear_list (lista_t *list){
	node_t *toVisit = list->start;
	node_t *toFree;
	while (toVisit != NULL){
		toFree = toVisit;
		toVisit = toVisit->next;
		free(toFree);
	}
	free(list);
}

void print_list (lista_t *list){
	node_t *print = list->start;
	while (print != NULL){
		printf ("%d ", print->value);
		print = print->next;
	}
	printf ("\n");
}


hash_table_t *createTable(int size) {
	hash_table_t *tab = (hash_table_t*) malloc(sizeof(hash_table_t));
	tab->entries = (lista_t**) malloc((size+1) * sizeof(lista_t*));
	tab->size = size;
	int i;
	for (i = 0; i < size+1; i++)
		tab->entries[i] = NULL;
	return tab;
}

void hashPut(hash_table_t *tab, int hashKey, int valueData) {
	if (tab->entries[hashKey] == NULL)
  		tab->entries[hashKey] = create_list();
	insert_list(tab->entries[hashKey], valueData, hashKey); //insere o valor no final da lista na posicao dada pela hashkey
}


lista_t *hashGet(hash_table_t *tab, int hashKey) {  //retorna a lista que se encontra na posicao da hashkey na tabela
	lista_t *returnVal = NULL;
	returnVal = tab->entries[hashKey];  
	return returnVal;
}

void hashRemove(hash_table_t *tab, int hashKey, int i){
	if (tab->entries[hashKey] != NULL){
		remove_element(tab->entries[hashKey], i); //remove o elemento da posicao i na celula dada pela hashkey
	}
}

void limpar_hash(hash_table_t *tab, int size){ 
	int i;
	for (i=0; i<=size; i++) {
		if (tab->entries[i] != NULL){
			clear_list(tab->entries[i]);
		}	
	}
	free(tab->entries);
	free(tab);
}

void print_hash(hash_table_t *tab, int i){
	print_list(tab->entries[i]);
}

int pivotPosition(int *values, int start, int end){
	int aux=0;
	int pivot = values[end-1];
	int i = start;
	int j = end-2;
	while (i<=j){
		while (values[j] < pivot) j--;
		while (values[i] > pivot) i++;
		if (j > i){
			aux = values[i];
			values[i] = values[j];
			values[j]= aux;
		}
	}
	aux = values[i];
	values[i] = values[end-1];
	values[end-1] = aux;
	return i;
}

void quickSort (int *values, int start, int end, int k){ //ordenando de forma decrescente
	int pivot;
	if ((end-start) > 1){
	pivot = pivotPosition (values, start, end);
	if (k < pivot) quickSort (values, start, pivot, k);
	if (k+1 > pivot) {
		quickSort (values, start, pivot, k);
		quickSort (values, pivot+1, end, k);
	}
	}
}

 
