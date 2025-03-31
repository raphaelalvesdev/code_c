#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"

struct arv{
    char info;
    struct arv* esq;
    struct arv* dir;
};

Arv* arv_criavazia(){
    return NULL;
}

Arv* arv_cria(char c, Arv* sae, Arv* sad){
    Arv* a = (Arv*) malloc(sizeof(Arv));
    a->info = c;
    a->esq = sae;
    a->dir = sad;
    return a;
}

int arv_pertence(Arv* a, char c){
    if (arv_vazia(a))
        return 0; // A árvore está vazia, não pode conter o elemento
    else
        return a->info == c || arv_pertence(a->esq, c) || arv_pertence(a->dir, c);
}

Arv* arv_libera(Arv* a){
    if(!arv_vazia(a)){
        arv_libera(a->esq);
        arv_libera(a->dir);
        free(a);
    }
    return NULL;
}

int arv_vazia(Arv* a){
    return (a == NULL);
}

void arv_imprime (Arv* a) {
    if (!arv_vazia(a)) {
        printf("%c ", a->info); /* mostra raiz */
        arv_imprime(a->esq); /* mostra sae */
        arv_imprime(a->dir); /* mostra sad */
    }
}

int main(){
    Arv* a1 = arv_cria('d', arv_criavazia(), arv_criavazia());
    Arv* a2 = arv_cria('b', arv_criavazia(), a1);
    Arv* a3 = arv_cria('e', arv_criavazia(), arv_criavazia());
    Arv* a4 = arv_cria('f', arv_criavazia(), arv_criavazia());
    Arv* a5 = arv_cria('c', a3, a4);
    Arv* a = arv_cria('a', a2, a5);

    printf("A árvore pré ordem é:\n");
    arv_imprime(a);
    printf("\n");

    // a = arv_libera(a);

    // Criando uma nova árvore do zero
    a->esq->esq = arv_cria('x',
        arv_cria('y',
        arv_criavazia(),
        arv_criavazia()),
        arv_cria('z',
        arv_criavazia(),
        arv_criavazia())
        );

    printf("A nova árvore é:\n");
    arv_imprime(a);
    printf("\n");

    a->dir->esq = arv_libera (a->dir->esq);

    printf("A nova árvore agora é:\n");
    arv_imprime(a);
    printf("\n");

    // Libera a nova árvore
    a = arv_libera(a);

    return 0;
}