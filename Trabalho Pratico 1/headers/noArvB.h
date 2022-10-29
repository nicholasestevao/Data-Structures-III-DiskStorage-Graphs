#ifndef __NO_ARV_B__
#define __NO_ARV_B__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesFornecidas.h"

typedef struct {
    char* folha;
    int* nroChavesNo;
    int* alturaNo;
    int* RRNdoNo;
    int* P1;
    int* C1;
    int* PR1;
    int* P2;
    int* C2;
    int* PR2;
    int* P3;
    int* C3;
    int* PR3;
    int* P4;
    int* C4;
    int* PR4;
    int* P5;
}noArvB;

void alocaNoArvB(noArvB ** registros, int numReg);

void desalocaNoArvB(noArvB ** registros, int numReg);

//void imprimeNoArvBTela(noArvB * registro);

void lerRegistroDadosTeclado(RegistroDados *registro);

#endif