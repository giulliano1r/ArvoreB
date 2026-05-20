#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "arvoreB.h"
#include "fila.h"

int main()
{
    struct arvoreB *a = criarArvoreB(2);
    
    int teste[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int num_inserir = sizeof(teste) / sizeof(teste[0]);

    for (int i = 0; i < num_inserir; i++) 
        inserirArvoreB(a, teste[i]);
    

    imprimirArvoreB(a); 
    imprimirEmOrdem(a);

    int idx;
    struct nodo *encontrado = buscarArvoreB(a, 60, &idx);
    if (encontrado != nullptr) 
        printf("Chave 60 encontrada no indice [%d]\n", idx);
    else 
        printf("Chave 60 nao encontrada\n");
    
    // remocao na folha
    printf("Chave : 100\n");
    removerChaveArvoreB(a, 100);
    imprimirArvoreB(a);

    //remocao no interno
    printf("Chave : 40\n");
    removerChaveArvoreB(a, 40);
    imprimirArvoreB(a);

    // remocao com merge
    printf("Chave : 10\n");
    removerChaveArvoreB(a, 10);
    printf("Chave : 20\n");
    removerChaveArvoreB(a, 20);
    imprimirArvoreB(a);
    imprimirEmOrdem(a);

    //a chave nao esta na arvore
    printf("Chave : 100\n");
    removerChaveArvoreB(a,100);

    deletarArvore(a);
    printf("\nMemoria liberada\n");
    return 0;
}