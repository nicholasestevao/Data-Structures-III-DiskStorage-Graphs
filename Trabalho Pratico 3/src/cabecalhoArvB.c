#include "../headers/cabecalhoArvB.h"

void alocaCabecalhoArvB(CabecalhoArvB **registro)
{
    (*registro) = (CabecalhoArvB*) malloc(sizeof(CabecalhoArvB));
    (*registro)->status = (char*) malloc(sizeof(char) * 1);
    (*registro)->noRaiz = (int*) malloc(sizeof(int) * 1);
    (*registro)->nroChavesTotal = (unsigned int*) malloc(sizeof(int) * 1);
    (*registro)->alturaArvore = (unsigned int*) malloc(sizeof(int) * 1);
    (*registro)->RRNproxNo = (unsigned int*) malloc(sizeof(int) * 1);

    *((*registro)->status) = '0';
    *((*registro)->noRaiz) = -1;
    *((*registro)->nroChavesTotal) = 0;
    *((*registro)->alturaArvore) = 0;
    *((*registro)->RRNproxNo) = 0;
}

void desalocaCabecalhoArvB(CabecalhoArvB *registro)
{
    free(registro->status);
    free(registro->noRaiz);
    free(registro->nroChavesTotal);
    free(registro->alturaArvore);
    free(registro->RRNproxNo);
    free(registro);
}

void imprimeCabecalhoArvBTela(CabecalhoArvB *cabecalho)
{
    printf("Status:\t\t%c\n", *(cabecalho->status));
    printf("Altura:\t\t%d\n", *(cabecalho->alturaArvore));
    printf("Raiz:\t\t%d\n", *(cabecalho->noRaiz));
    printf("Nro Chaves:\t%d\n", *(cabecalho->nroChavesTotal));
    printf("Prox. RRN:\t%d\n", *(cabecalho->RRNproxNo));
}
