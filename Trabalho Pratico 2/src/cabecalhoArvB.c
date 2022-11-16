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

    iniciaCabecalhoArvB((*registro));
}

void desalocaCabecalhoArvB(cabecalhoArvB *registro){
    free(registro->status);
    free(registro->noRaiz);
    free(registro->nroChavesTotal);
    free(registro->alturaArvore);
    free(registro->RRNproxNo);
    free(registro);
}
