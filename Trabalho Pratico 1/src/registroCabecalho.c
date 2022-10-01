#include "../headers/registroCabecalho.h"

void alocaRegistrosCabecalho(RegistroCabecalho *registros) {
    registros->status = malloc(sizeof(char) * 1);
    registros->topo = malloc(sizeof(int) * 1);
    registros->proxRRN= malloc(sizeof(int) * 1);
    registros->nroRegRem = malloc(sizeof(int) * 1);
    registros->nroPagDisco = malloc(sizeof(int) * 1);
    registros->qttCompacta = malloc(sizeof(int) * 1);
}

void desalocaRegistrosCabecalho(RegistroCabecalho *registros) {
    free(registros->status);
    free(registros->topo);
    free(registros->proxRRN);
    free(registros->nroRegRem);
    free(registros->nroPagDisco);
    free(registros->qttCompacta);
}
