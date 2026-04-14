#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fila.h"

struct fila_t *fila_cria ()
{
    struct fila_t *f;

    f = malloc (sizeof (struct fila_t));

    if(f == nullptr)
    {
        fprintf(stderr, "Falha ao alocar memória.\n");
        exit(1);
    }

    f->prim = nullptr;
    f->ult = nullptr;
    f->num = 0;

    return f;
}

void fila_insere (struct fila_t *f, struct nodo *n)
{
    if(f == nullptr || n == nullptr)
        return;
    struct fila_nodo_t *novo;
    novo = malloc (sizeof (struct fila_nodo_t));

    if(novo == nullptr)
    {
        fprintf(stderr, "Falha ao alocar memória.\n");
        exit(1);
    }

    novo->arvore = n;
    novo->prox = nullptr;

    // caso a fila esteja vazia
    if(f->prim == nullptr)
    {
        f->prim = novo;
        f->ult = novo;
    }

    else
    {
        f->ult->prox = novo;
        f->ult = novo;
    }

    f->num++;
    return;
}

struct nodo *fila_retira (struct fila_t *f)
{

    if(f == nullptr || f->num == 0)
        return nullptr;

    struct fila_nodo_t *temp = f->prim;
    struct nodo *retorno = temp->arvore;

    //o primeiro da fila se torna o proximo
    f->prim = f->prim->prox;
    f->num--;

    // se a fila ficou vazia, primeiro e ultimo são nulos
    if(f->num == 0)
    {
        f->ult = nullptr;
        f->prim = nullptr;
    }

    free(temp);
    return retorno;
}
