#include "../headers/cabecalhoArvB.h"

void alocaCabecalhoArvB(cabecalhoArvB **registro){
    (*registro) = malloc(sizeof(cabecalhoArvB));
    (*registro)->status = malloc(sizeof(char) * 1);
    (*registro)->noRaiz = malloc(sizeof(int) * 1);
    (*registro)->nroChavesTotal = malloc(sizeof(int) * 1);
    (*registro)->alturaArvore = malloc(sizeof(int) * 1);
    (*registro)->RRNproxNo = malloc(sizeof(int) * 1);
}

void desalocaCabecalhoArvB(cabecalhoArvB *registro){
    free(registro->status);
    free(registro->noRaiz);
    free(registro->nroChavesTotal);
    free(registro->alturaArvore);
    free(registro->RRNproxNo);
    free(registro);
}
