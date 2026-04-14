#include<stdio.h>
#include<stdlib.h>
#include "arvoreB.h"
#include "fila.h"

void verifica_erro(void *ptr)
{
    if (ptr == nullptr)
    {
        fprintf(stderr, "Falha ao alocar memória.\n");
        exit(1);
    }
}
struct arvoreB* criarArvoreB(int32_t t_arvore)
{
    struct nodo *novaArvore;
    novaArvore = malloc(sizeof(t_arvore));
    verifica_erro(novaArvore);

    novaArvore->n = 0;
    novaArvore->ehFolha = true;

     for(int i = 0; i < 2 * GRAU_MINIMO; i++)
        novaArvore->filhos[i] = nullptr;

    return novaArvore;
}

void dividirFilho(struct nodo *no, int32_t indice, int32_t t)
{
    struct nodo *y = no->filhos[indice];
    struct nodo *z = malloc(sizeof(struct nodo));
    verifica_erro(z);

    z->ehFolha = y->ehFolha;
    z->n = t - 1;

    for(int32_t i = 0; i < t - 1; i++)
        z->chave[i] = y->chave[i+t];

    if(y->ehFolha == false)
        for(int32_t i = 0; i < t; i++)
            z->filhos[i] = y->filhos[i+t];

    y->n = t - 1;

    for(int32_t i = (no->n + 1); i > indice + 1; i--)
        no->filhos[i+1] = no->filhos[i];

    no->filhos[indice + 1] = z;

    for(int32_t i = no->n; i > indice; i--)
        no->chaves[i+1] = no->chaves[i];

    no->chaves[indice] = y->chaves[t - 1];
    no->n = no->n + 1;
}

void inserirNaoCheio(struct nodo *no, int32_t chave, int32_t t)
{
    int32_t i = no->n -1;
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
        verifica_erro(s);

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


void imprimirArvoreB(struct arvoreB* arvore)
{

    if(arvore == nullptr || arvore->raiz == nullptr)
        return;

    struct fila_t *fila;
    struct nodo *nodo_atual;
    int32_t nivel = 0;
    fila = cria_fila();

    fila_insere(arvore, arvore->raiz);
    
    while(fila->num > 0) 
    {
        printf("----//----\n");
        printf("Nível %d\n", nivel);
        printf("----//----\n");

        //mostra quantos nós tem no nível
        int32_t nos = fila->num;

        for (int32_t j = 0; j<nos; j++) 
        {
            nodo_atual = fila_retira(fila);

            char tipo;
            if(nodo_atual->ehFolha)
                tipo = 'F';
            else
                tipo = 'I';

            printf("%c  (n:%d) [", tipo, nodo_atual->n);
            for(int32_t i = 0; i <nodo_atual->n; i++)
            {
                printf("%d", nodo_atual->chaves[i]);
                if(i < nodo_atual->n-1)
                    printf(" ");
            }
            printf("]");

            if(j<nos -1)
                printf(" ");

            if(nodo_atual->ehFolha == nullptr)
            {
                for (int32_t k = 0; k<= nodo_atual->n; k++)
                    if(nodo_atual->filhos[j] != nullptr)
                        fila_insere(fila, nodo_atual->filhos[j]);
            }
        }
        printf("\n");
        nivel++;
    }

    printf("----//----\n");
    free(fila);
  
}
void imprimirEmOrdem(struct arvoreB* arvore); // eu
struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave,
                          int32_t* idxEncontrado); // eu
static void deleta_nodo(struct nodo *n)
{
    if(n == nullptr)
        return;

    if(!n->ehFolha)
    {
        for(int32_t i = 0; i <= n->n; i++)
            deleta_nodo(n->filhos[i]);
    }
}
void deletarArvore(struct arvoreB* arvore) 
{
    if(arvore == nullptr)
        return;

    deleta_nodo(arvore->raiz);
    free(arvore);
}
