#ifndef __CABECALHO__ARV_B__
#define __CABECALHO__ARV_B__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* status;
    int* noRaiz;
    unsigned int* nroChavesTotal;
    unsigned int* alturaArvore;
    unsigned int* RRNproxNo;
}cabecalhoArvB;


void alocaCabecalhoArvB(cabecalhoArvB **registro);

void desalocaCabecalhoArvB(cabecalhoArvB *registro);

void imprimeCabecalhoArvBTela(cabecalhoArvB * cabecalho);


#endif