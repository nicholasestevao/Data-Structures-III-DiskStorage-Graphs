#ifndef __REGISTROS_CABECALHO_C__
#define __REGISTROS_CABECALHO_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* status;
    int* topo;
    unsigned int* proxRRN;
    unsigned int* nroRegRem;
    unsigned int* nroPagDisco;
    unsigned int* qttCompacta;
}RegistroCabecalho;

void alocaRegistrosCabecalho(RegistroCabecalho **registro);
void desalocaRegistrosCabecalho(RegistroCabecalho *registro);
void imprimeRegistroCabecalhoTela(RegistroCabecalho * registro);
#endif