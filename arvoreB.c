#include<stdio.h>
#include<stdlib.h>
#include "arvoreB.c"

struct arvoreB* criarArvoreB(int32_t t_arvore)
{
    struct nodo *novaArvore;
    novaArvore = malloc(sizeof(t_arvore));

    novaArvore->n = 0;
    novaArvore->ehFolha = true;

     for(int i = 0; i < 2 * GRAU_MINIMO; i++)
        novaArvore->filhos[i] = NULL;

    return novaArvore;
}

void dividirFilho(struct nodo *no, int32_t indice, int32_t t)
{
    struct nodo *y = no->filhos[indice];
    struct nodo *z = malloc(sizeof(struct nodo));
    if(z == NULL)
    {
        printf("z invalido\n");
        return;
    }

    z->ehFolha = y->ehFolha;
    z->n = t - 1;

    for(int i = 0; i < t - 1; i++)
        z->chave[i] = y->chave[i+t];

    if(y->ehFolha == false)
        for(int i = 0; i < t; i++)
            z->filhos[i] = y->filhos[i+t];

    y->n = t - 1;

    for(int i = (no->n + 1); i > indice + 1; i--)
        no->filhos[i+1] = no->filhos[i];

    no->filhos[indice + 1] = z;

    for(int i = no->n; i > indice; i--)
        no->chaves[i+1] = no->chaves[i];

    no->chaves[indice] = y->chaves[t - 1];
    no->n = no->n + 1;
}

void inserirNaoCheio(struct nodo *no, int32_t chave, int32_t t)
{
    int i = no->n -1;
    if(no->ehFolha == true)
    {
        while(i >= 1  && chave < no->chaves[i])
        {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        no->chaves[i + 1] = chave;
        x->n = x->n + 1;
    }
    else
    {
        while(i >= 1 && chave < no->chaves[i])
            i--;
        i++;
        if(no->filhos[i]->n == (2 * t) - 1)
        {
            dividirFilho(no,i,t);
            if(chave > nodo->chaves[i])
                i++;
        }
        inserirNaoCheio(no->filhos[i],chave, t;)
    }
}

void inserirArvoreB(struct arvoreB* arvore, int32_t chave)
{
    struct nodo *r = arvore->raiz;
    int t = arvore->t_arvore;

    if(r->n == (2 * t) - 1)
    {
        // quando esta tudo cheio entao a raiz sobe :
        struct nodo *s = malloc(sizeof(struct nodo));
        if(s == NULL)
            return;

        arvore->raiz = s;
        s->ehFolha = false;
        s->n = 0;
        s->filhos[0] = r;

        dividirFilho(s,0,t);
        inserirNaoCheio(s,chave);
    }
    else
        inserirNaoCheio(r,chave);
}

void imprimirArvoreB(struct arvoreB* arvore);
void imprimirEmOrdem(struct arvoreB* arvore); // eu
struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave,
                          int32_t* idxEncontrado); // eu
void deletarArvore(struct arvoreB* arvore);
