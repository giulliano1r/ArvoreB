/*#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "arvoreB.h"
#include "fila.h"

int main()
{
    int x = 72;

    struct arvoreB *a = criarArvoreB(5);
    inserirArvoreB(a, 10);
    inserirArvoreB(a, 13);
    inserirArvoreB(a, 14);
    inserirArvoreB(a, 9);
    inserirArvoreB(a, 8);
    inserirArvoreB(a, 7);
    inserirArvoreB(a, 73);
    inserirArvoreB(a, x);
    inserirArvoreB(a, x);
    inserirArvoreB(a, x);
    inserirArvoreB(a, 71);
    inserirArvoreB(a, 2);
    inserirArvoreB(a, 1);
    imprimirArvoreB(a);
    imprimirEmOrdem(a);

    int32_t i;
    struct nodo *buscaAB = buscarArvoreB(a,79,&i);

    if(buscaAB)
        printf("\n Encontrou o %d no indice %d \n", x, i );
    else
        printf("\n Nao encontrou\n");

    deletarArvore(a);
    a = nullptr;
    imprimirArvoreB(a);
    return 0;
}*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "arvoreB.h"
#include "fila.h"
int main()
{
    struct arvoreB *a = criarArvoreB(3);
    
    // Apenas 3 inserções
    inserirArvoreB(a, 10);
    inserirArvoreB(a, 20);
    inserirArvoreB(a, 30);
    
    printf("Antes: ");
    imprimirEmOrdem(a);
    
    printf("\nRemovendo 20: ");
    removerChaveArvoreB(a, 20);
    
    printf("Depois: ");
    imprimirEmOrdem(a);
    
    deletarArvore(a);
    return 0;
}