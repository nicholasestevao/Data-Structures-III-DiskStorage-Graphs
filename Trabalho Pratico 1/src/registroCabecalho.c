#include "../headers/registroCabecalho.h"

void iniciaRegistrosCabecalho(RegistroCabecalho *registros) {
    *(registros->status) = '0';
    *(registros->topo) = -1;
    *(registros->proxRRN) = 0;
    *(registros->nroRegRem) = 0;
    *(registros->nroPagDisco) = 0;
    *(registros->qttCompacta) = 0;
}

void alocaRegistrosCabecalho(RegistroCabecalho **registros) {
    (*registros) = malloc(sizeof(RegistroCabecalho));
    (*registros)->status = malloc(sizeof(char) * 1);
    (*registros)->topo = malloc(sizeof(int) * 1);
    (*registros)->proxRRN= malloc(sizeof(int) * 1);
    (*registros)->nroRegRem = malloc(sizeof(int) * 1);
    (*registros)->nroPagDisco = malloc(sizeof(int) * 1);
    (*registros)->qttCompacta = malloc(sizeof(int) * 1);
    iniciaRegistrosCabecalho((*registros));
}

void desalocaRegistrosCabecalho(RegistroCabecalho *registros) {
    free(registros->status);
    free(registros->topo);
    free(registros->proxRRN);
    free(registros->nroRegRem);
    free(registros->nroPagDisco);
    free(registros->qttCompacta);
}

void imprimeRegistroCabecalhoTela(RegistroCabecalho * registro) {
    
    printf("Status: %c\n", *(registro->status));
    printf("Topo: %d\n", *(registro->topo));
    printf("Prox RRN: %d\n", *(registro->proxRRN));
    printf("Nro Pag Disco: %d\n", *(registro->nroPagDisco));
    printf("Nro Reg Rem: %d\n", *(registro->nroRegRem));
    printf("Qtt Compactacao: %d\n", *(registro->qttCompacta));
    
}
