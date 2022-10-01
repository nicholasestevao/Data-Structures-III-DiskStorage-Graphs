#ifndef __REGISTROS_C__
#define __REGISTROS_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct {
    char* status;
    int * topo;
    int * proxRRN;
    int * nroRegRem;
    int * nroPagDisco;
    int * qttCompacta;
}RegistroCabecalho;

void alocaRegistrosCabecalho(RegistroCabecalho ** registros, int numReg);
void desalocaRegistrosCabecalho(RegistroCabecalho ** registros, int numReg);

#endif