#include "../headers/cabecalhoArvB.h"

void alocaCabecalhoArvB(cabecalhoArvB **registro){
    (*registro) = malloc(sizeof(cabecalhoArvB));
    (*registro)->status = malloc(sizeof(char) * 1);
    (*registro)->noRaiz = malloc(sizeof(int) * 1);
    (*registro)->nroChavesTotal = malloc(sizeof(int) * 1);
    (*registro)->alturaArvore = malloc(sizeof(int) * 1);
    (*registro)->RRNproxNo = malloc(sizeof(int) * 1);

    *((*registro)->status) = '0';
    *((*registro)->noRaiz) = -1;
    *((*registro)->nroChavesTotal) = 0;
    *((*registro)->alturaArvore) = 0;
    *((*registro)->RRNproxNo) = 0;
}

void desalocaCabecalhoArvB(cabecalhoArvB *registro){
    free(registro->status);
    free(registro->noRaiz);
    free(registro->nroChavesTotal);
    free(registro->alturaArvore);
    free(registro->RRNproxNo);
    free(registro);
}

void imprimeCabecalhoArvBTela(cabecalhoArvB * cabecalho){
    printf("%c\n", *(cabecalho->status));
    printf("%d\n", *(cabecalho->alturaArvore));
    printf("%d\n", *(cabecalho->noRaiz));
    printf("%d\n", *(cabecalho->nroChavesTotal));
    printf("%d\n", *(cabecalho->RRNproxNo));
}
