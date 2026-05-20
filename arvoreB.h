#ifndef ARVORE_B_H_
#define ARVORE_B_H_
#define GRAU_MINIMO 2

#include <stdint.h>

//COMPATIBILIDADE COM O C23: Remover as duas linhas de código abaixo 
//(#include <stdbool.h> e #define nullptr NULL), pois já são nativas do c23
#include <stdbool.h>
#define nullptr NULL

struct nodo {
    int32_t n;
    int32_t chaves[2 * GRAU_MINIMO - 1];
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
bool removerChaveArvoreB(struct arvoreB* arvore, int32_t chave);
void deletarArvore(struct arvoreB* arvore);

#endif
