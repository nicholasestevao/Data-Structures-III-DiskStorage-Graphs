#include "../headers/cabecalhoArvB.h"

//Inicia as variaveis do RegistroCabecalho com os valores padrao.
void iniciaCabecalhoArvB(cabecalhoArvB *registro)
{
    *(registro->status) = '0';
    *(registro->noRaiz) = -1;
    *(registro->nroChavesTotal) = 0;
    *(registro->alturaArvore) = 0;
    *(registro->RRNproxNo) = 1;
}

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
    printf("Status:\t\t%c\n", *(cabecalho->status));
    printf("Altura:\t\t%d\n", *(cabecalho->alturaArvore));
    printf("Raiz:\t\t%d\n", *(cabecalho->noRaiz));
    printf("Nro Chaves:\t%d\n", *(cabecalho->nroChavesTotal));
    printf("Prox. RRN:\t%d\n", *(cabecalho->RRNproxNo));
}
