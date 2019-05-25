#ifndef CANDIDATO
#define CANDIDATO


typedef struct node {
	int value;
	struct node *next;
	int hashKey;
} node_t;

typedef struct list {
	node_t *start;
	node_t *end;
	int num_elements;
} lista_t;

typedef struct {
	lista_t **entries; 
	int size;               
} hash_table_t;

typedef struct {
	lista_t *list_pref;
} preferencias;


lista_t *create_list ();
void insert_list (lista_t *list, int value, int hashKey);
void remove_element (lista_t *list, int i);
void clear_list (lista_t *list);
void print_list (lista_t *list);

hash_table_t *createTable(int size);
void hashPut(hash_table_t *tab, int hashKey , int valueData);
lista_t *hashGet(hash_table_t *tab, int hashKey);
void hashRemove(hash_table_t *tab, int hashKey, int i);
void limpar_hash(hash_table_t *tab, int size);
void print_hash(hash_table_t *tab, int i);

int pivotPosition(int *values, int start, int end);
void quickSort (int *values, int start, int end, int k);


#endif