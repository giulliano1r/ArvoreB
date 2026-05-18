#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
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
    struct arvoreB *arvore = malloc(sizeof(struct arvoreB));
    verifica_erro(arvore);
    struct nodo *novaArvore = malloc(sizeof(struct nodo));
    verifica_erro(novaArvore);

    novaArvore->n = 0;
    novaArvore->ehFolha = true;

     for(int32_t i = 0; i < 2 * GRAU_MINIMO; i++)
        novaArvore->filhos[i] = nullptr;

    arvore->raiz = novaArvore;
    arvore->t_arvore = t_arvore;

    return arvore;
}

// funcao responsavel pelo processo que envolve a divisao de um no cheio.
void dividirFilho(struct nodo *no, int32_t indice, int32_t t)
{
    struct nodo *y = no->filhos[indice];

    // criamos um novo nodo para poder fazer a divisao.
    struct nodo *z = malloc(sizeof(struct nodo));
    verifica_erro(z);

    // garantimos que eles estejam no mesmo nivel para ser uma arvoreb.
    z->ehFolha = y->ehFolha;
    z->n = t - 1;

    // transferimos metade das chaves de y para o novo nodo.
    for(int32_t i = 0; i < t - 1; i++)
        z->chaves[i] = y->chaves[i+t];

    // fazemos a mesma coisa com os filhos para caso y nao seja folha.
    if(y->ehFolha == false)
        for(int32_t i = 0; i < t; i++)
            z->filhos[i] = y->filhos[i+t];

    y->n = t - 1;

    // para o pai conseguir apontar para z, liberamos espaco no vetor de filhos
    // de no do final ate a posicao indicada.
    for(int32_t i = (no->n + 1); i > indice + 1; i--)
        no->filhos[i + 1] = no->filhos[i];

    //entao conectamos o pai(no) com o novo nodo(z)
    no->filhos[indice + 1] = z;

    // aqui fazemos o deslocamento necessario para subir para o pai a chave
    // que vai ser a divisora entre o nodo existente e o novo.
    for(int32_t i = no->n; i > indice; i--)
        no->chaves[i+1] = no->chaves[i];

    // aqui subimos a chave do meio para o espaco reservado no pai.
    no->chaves[indice] = y->chaves[t - 1];
    no->n = no->n + 1;
}

// funcao responsavel por inserir uma chave na arvore.
void inserirNaoCheio(struct nodo *no, int32_t chave, int32_t t)
{
    int32_t i = no->n -1;
    // caso 1 : inserir na folha.
    if(no->ehFolha == true)
    {
        // abrimos espaco para no vetor de chaves para insercao da chave.
        while(i >= 0  && chave < no->chaves[i])
        {
            no->chaves[i + 1] = no->chaves[i];
            i--;
        }
        // inserimos na posicao reservada no while.
        no->chaves[i + 1] = chave;
        no->n = no->n + 1;
    }
    else
    {
        // caso 2 : nao e folha

        // precisamos encontrar em qual filho a nossa chave deve ser inserida.
        while(i >= 0 && chave < no->chaves[i])
            i--;
        i++;
        // se o filho indicado para insercao estiver cheio, aplicamos dividirFilho()
        // para liberar espaco necessario.
        if(no->filhos[i]->n == (2 * t) - 1)
        {
            dividirFilho(no,i,t);
            if(chave > no->chaves[i])
                i++;
        }

        // vamos descendo dentro dos filhos até encontrar uma folha.
        inserirNaoCheio(no->filhos[i],chave, t);
    }
}

// funcao responsavel por gerenciar os casos de insercao.
void inserirArvoreB(struct arvoreB* arvore, int32_t chave)
{
    struct nodo *r = arvore->raiz;
    int32_t t = arvore->t_arvore;

    // caso 1 : raiz cheia -> logo precisamos dividir.
    if(r->n == (2 * t) - 1)
    {
        // quando esta tudo cheio entao a raiz sobe.
        struct nodo *s = malloc(sizeof(struct nodo));
        verifica_erro(s);

        // criamos a nova raiz.
        arvore->raiz = s;
        s->ehFolha = false;
        s->n = 0;
        s->filhos[0] = r;

        // divide o nodo cheio entao insere normalmente.
        dividirFilho(s,0,t);
        inserirNaoCheio(s,chave, t);
    }
    else
        inserirNaoCheio(r,chave,t); // caso 2 : insere normalmente pois existe espaco.
}

void imprimirArvoreB(struct arvoreB* arvore)
{

    if(arvore == nullptr || arvore->raiz == nullptr)
    {
        printf("Arvore nula\n");
        return;
    }

    struct fila_t *fila;
    struct nodo *nodo_atual;
    int32_t nivel = 0;
    fila = fila_cria();

    //enfileira o primeiro filho para a fila
    fila_insere(fila, arvore->raiz);

    //enquanto há nodos na fila
    while(fila->num > 0)
    {
        printf("----//----\n");
        printf("Nível %d\n", nivel);
        printf("----//----\n");

        //mostra quantos nós tem no nível
        int32_t nos = fila->num;

        for (int32_t j = 0; j<nos; j++)
        {
            //desenfileira a fila
            nodo_atual = fila_retira(fila);

            char tipo;
            if(nodo_atual->ehFolha)
                tipo = 'F';
            else
                tipo = 'I';

            printf("%c  (n:%d) [", tipo, nodo_atual->n);
            //imprime todas as chaves do nodo
            for(int32_t i = 0; i <nodo_atual->n; i++)
            {
                printf("%d", nodo_atual->chaves[i]);
                if(i < nodo_atual->n-1)
                    printf(" ");
            }
            printf("]");

            //caso ainda haja mais nodos, imprime um espaço a mais
            if(j<nos -1)
                printf(" ");

            //se o nodo eh interno, insere os nodos dilhos em ordem na fila
            if(!nodo_atual->ehFolha)
            {
                for (int32_t k = 0; k<= nodo_atual->n; k++)
                    if(nodo_atual->filhos[k] != nullptr)
                        fila_insere(fila, nodo_atual->filhos[k]);
            }
        }
        printf("\n");
        nivel++;
    }

    printf("----//----\n");
    free(fila);

}

void imprimirEmOrdemRecursivamente(struct nodo* no)
{
    for(int32_t i = 0; i <= no->n; i++)
    {
        // desce para esquerda até encontrar uma folha.
        if(no->ehFolha == false)
            imprimirEmOrdemRecursivamente(no->filhos[i]);

        // imprime a atual e volta recursivamente imprimindo da esquerda para direita da arvore.
        if(i < no->n)
            printf(" %d", no->chaves[i]);
    }
}

void imprimirEmOrdem(struct arvoreB* arvore)
{
    verifica_erro(arvore);

    printf("Em ordem:");
    imprimirEmOrdemRecursivamente(arvore->raiz);
    printf("\n");
}

// retorna o indice exato de uma chave dentro de um no.
int32_t percorreNodo(struct nodo *no, int32_t chave)
{
    int32_t indice = 0;

    // vai avancar até encontrar a chave que seja menor que a chave de algum no.
    while (indice < no->n && chave > no->chaves[indice])
        indice++;

    return indice;
}

struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave, int32_t *idxEncontrado)
{
    if(arvore == NULL || arvore->raiz == NULL)
    {
        *idxEncontrado = -1;
        return nullptr;
    }
    struct nodo *no = arvore->raiz;

    while(no != nullptr)
    {
        // para nao percorrer a arvore toda, diminuimos nosso escopo, encontrando
        // o indice provavel que a nossa chave se enconta dentro de um nodo.
        int32_t indice = percorreNodo(no,chave);

        // verifica se na posicao provavel encontramos a chave que estavamos buscando.
        if(indice < no->n && no->chaves[indice] == chave)
        {
            *idxEncontrado = indice;
            return no;
        }
        // se é folha entao encerramos a busca sem sucesso, retornando -1.
        if( no->ehFolha)
        {
            *idxEncontrado = -1;
            return nullptr;
        }

        // tentamos mais uma vez para o filho para caso nao tenhamos encontrado nem é folha.
        no = no->filhos[indice];
    }
    *idxEncontrado = -1;
    return nullptr;
}

//garante que essa função so eh vista no arvoreB.c
static void deleta_nodo(struct nodo *n)
{
    if(n == nullptr)
        return;

    //se o nodo nao eh folha, a função desce até a folha e deleta recursivamente
    if(!n->ehFolha)
    {
        for(int32_t i = 0; i <= n->n; i++)
            deleta_nodo(n->filhos[i]);
    }

    free(n);

}

void deletarArvore(struct arvoreB* arvore)
{
    if(arvore == nullptr)
        return;

    deleta_nodo(arvore->raiz);
    free(arvore);

}

//encontra o maior numero dos filhos
static int encontrarPred(struct nodo *pred)
{
    if(pred == nullptr)
        return -1;

    while(!pred->ehFolha)
        pred = pred->filhos[pred->n];
    return pred->chaves[pred->n - 1]; // pegamos o ultimo elemento do vetor de chaves

}

//encontra o menor numero dos filhos
static int encontrarSuc(struct nodo *suc)
{
    if(suc == nullptr)
        return -1;

    while(!suc->ehFolha)
        suc = suc->filhos[0];
    return suc->chaves[0]; // pegamos o ultimo elemento do vetor de chaves
}

//remove o numero de um vetor, diminui o numero de chaves do nodo (parametro n)
static void remove_vetor(int32_t vetor[], int32_t chave, int *n )
{
    if(*n == 0 || n == nullptr)
        return;

    int i = 0;
    while(i < *n - 1)
    {
        if(chave == vetor[i])
        {
            // substitui a chave no vetor
            for(int j = i; j < *n - 1; j++)
                vetor[j] = vetor[j + 1];
            (*n)--;
            return;
        }
        i++;
    }
    return;
}

struct nodo* irmaoImediatoComMaisChaves(struct nodo* x, int32_t i)
{
    //olhar pros vizinhos de x e verificar se algum deles pode emprestar uma chave
    // vizinhos = [x-1] e [x+1]

    if(x == nullptr)
        return nullptr;

    struct nodo* irmaoEsq;
    struct nodo* irmaoDir;
    struct nodo* atual = x->filhos[i]

    if(i > 0)
        irmaoEsq = x->filhos[i - 1];
    else
        irmaoEsq = nullptr;

    if(i > x->n)
        irmaoDir = x->filhos[i + 1];
    else
        irmaoDir = nullptr;

    // se x[i-1] tiver mais chaves do que x[i] ele sera do irmaoImediatoComMaisChaves
    if(irmaoEsq != nullptr && irmaoEsq->n > atual->n)
        return irmaoEsq;
    // se x[i+1] tiver mais chaves do que x[i], ele sera do irmaoImediatoComMaisChaves
    if(irmaoDir != nullptr && irmaoDir->n > atual->n)
        return irmaoDir;

    return nullptr;
}

//faz o merge de dois nodos
static void merge(struct nodo* filho1, struct nodo* filho2, int32_t chave, int32_t t)
{

}

// x = x->filhos[i] y = x
void inclusaoDireita(struct nodo* x, struct nodo* y, int32_t i)
{

}

void inclusaoEsquerda(struct nodo* x, struct nodo* y, int32_t i)
{

}

bool removerChaveArvoreB(struct arvoreB* arvore, int32_t chave)
{
    if(!arvore || !arvore->raiz)
    {
        printf("Arvore nula\n");
        return false;
    }

    excluirArvoreB(arvore, arvore->raiz, chave);
}

int32_t excluirArvoreB(struct arvoreB* arvore, struct nodo *x, int32_t chave)
{
    if(arvore == nullptr || x == nullptr)
    {
        printf("Arvore nula\n");
        return 0;
    }

    int32_t i = 0;

    // descobre em qual filho k esta
    while ( i<= x->n && chave > x->chaves[i])
        i++;

    if(i < x->n && chave == x->chaves[i]) // achou a chave, não tem só ela no vetor
    {
        if(x->filhos == nullptr) // se for uma folha, só remove a chave do vetor
        {
            remove_vetor(x->chaves, chave, &x->n);
            return 1;
        }
        else //eh um nó interno
        {
            if(x->filhos[i]->n >= arvore->t_arvore) //o filho esquerdo tem o numero minimo de chaves
            {
                int32_t pred;  //guarda o predecessor do numero
                pred = encontrarPred(x->filhos[i]);
                x->chaves[i] = pred;
                return excluirArvoreB(arvore, x->filhos[i], pred);
            }
            else //o filho direito tem o numero minimo de chaves
            {
                if(x->filhos[i+1]->n >= arvore->t_arvore)
                {
                    int32_t suc;
                    suc = encontrarSuc(x->filhos[i+1]);
                    x->chaves[i] = suc;
                    return excluirArvoreB(arvore, x->filhos[i+1], suc);
                }
                else // nenhum dos filhos tem o numero minimo de chaves
                {
                    remove_vetor(x->chaves, chave, &x->n);
                    merge(x->filhos[i], x->filhos[i+1], chave, arvore->t_arvore);
                    deleta_nodo(x->filhos[i+1]);
                    excluirArvoreB(arvore, x->filhos[i], chave);

                    if(x->n < 1)
                    {
                        arvore->raiz = x->filhos[0];
                        deleta_nodo(x);
                    }
                    return 1;
                }
            }
        }
    }
    else //chave nao encontrada ou a chave é única
    {
        if(x->chaves == nullptr)
            return 0;
        else
        {
            if(x->filhos[i]->n <= arvore->t_arvore)
            {
                struct nodo *b;
                b = irmaoImediatoComMaisChaves(x, i);
                if(b == nullptr)
                    // caso de nao ter irmao imediato, faz oq? pensar depois
                if(b->n >= arvore->t_arvore)
                {

                    x->filhos[i]->n = n + 1;

                    if(b == x->filhos[i+1])
                    {
                        inclusaoDireita(); // nao entendi essa parte ainda ayuda
                    }
                    else
                    {
                        inclusaoEsquerda(); //tambem nao entend ayuda
                    }
                }
                else
                {
                    merge(x->filhos[i], )
                }

            }
        }
    }

    return excluirArvoreB(arvore, x->filhos[i], chave);
}
