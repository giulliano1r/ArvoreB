#ifndef ARVORE_B_H_
#define ARVORE_B_H_
#define GRAU_MINIMO 2

#include <stdint.h>
#include <stdbool.h>
#define nullptr NULL

struct nodo {
    int n;
    int chaves[2 * GRAU_MINIMO - 1];
    struct nodo *filhos[2 * GRAU_MINIMO];
    bool ehFolha;
};

struct arvoreB {
  struct nodo* raiz;
  int32_t t_arvore;
};

struct arvoreB* criarArvoreB(int32_t t_arvore);
void inserirArvoreB(struct arvoreB* arvore, int32_t chave);
void imprimirArvoreB(struct arvoreB* arvore);
void imprimirEmOrdem(struct arvoreB* arvore);
struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave, int32_t* idxEncontrado);
void deletarArvore(struct arvoreB* arvore);

#endif
