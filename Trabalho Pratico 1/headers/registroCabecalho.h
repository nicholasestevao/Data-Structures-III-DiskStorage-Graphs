#ifndef __REGISTROS_CABECALHO_C__
#define __REGISTROS_CABECALHO_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* status;
    int* topo;
    int* proxRRN;
    int* nroRegRem;
    int* nroPagDisco;
    int* qttCompacta;
}RegistroCabecalho;

void alocaRegistrosCabecalho(RegistroCabecalho **registro);
void desalocaRegistrosCabecalho(RegistroCabecalho *registro);
void imprimeRegistroCabecalhoTela(RegistroCabecalho * registro);
#endif