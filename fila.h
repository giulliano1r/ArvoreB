#ifndef FILA
#define FILA
#include "arvoreb.h"

struct fila_nodo_t
{
	struct nodo *arvore;					
	struct fila_nodo_t *prox;	
};

struct fila_t
{
	struct fila_nodo_t *prim ;	
	struct fila_nodo_t *ult ;	
	int num ;					
};

//Cria uma fila vazia, retorna a fila ou nulo se deu erro
struct fila_t *fila_cria ();

//Insere os nodos da árvore na fila
void fila_insere (struct fila_t *f, struct nodo *n);

//Retira o nodo da fila, retorna nulo se a fila tiver vazia ou em caso de erro
struct nodo *fila_retira (struct fila_t *f);

#endif
