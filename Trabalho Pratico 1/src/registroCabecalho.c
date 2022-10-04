#include "../headers/registroCabecalho.h"

void alocaRegistrosCabecalho(RegistroCabecalho **registros) {
    *registros = malloc(sizeof(RegistroCabecalho));
     (*registros)[0].status = malloc(sizeof(char) * 1);
     (*registros)[0].topo = malloc(sizeof(int) * 1);
     (*registros)[0].proxRRN= malloc(sizeof(int) * 1);
     (*registros)[0].nroRegRem = malloc(sizeof(int) * 1);
     (*registros)[0].nroPagDisco = malloc(sizeof(int) * 1);
     (*registros)[0].qttCompacta = malloc(sizeof(int) * 1);
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
