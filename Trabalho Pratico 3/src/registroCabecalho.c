#include "../headers/registroCabecalho.h"

//Inicia as variaveis do RegistroCabecalho com os valores padrao.
void iniciaRegistrosCabecalho(RegistroCabecalho *registros)
{
    *(registros->status) = '0';
    *(registros->topo) = -1;
    *(registros->proxRRN) = 0;
    *(registros->nroRegRem) = 0;
    *(registros->nroPagDisco) = 1;
    *(registros->qttCompacta) = 0;
}

//Aloca memoria para todos os ponteiros do RegistroCabecalho.
void alocaRegistrosCabecalho(RegistroCabecalho **registros)
{
    (*registros) = (RegistroCabecalho*) malloc(sizeof(RegistroCabecalho));
    (*registros)->status = (char*) malloc(sizeof(char) * 1);
    (*registros)->topo = (int*) malloc(sizeof(int) * 1);
    (*registros)->proxRRN = (unsigned int*) malloc(sizeof(int) * 1);
    (*registros)->nroRegRem = (unsigned int*) malloc(sizeof(int) * 1);
    (*registros)->nroPagDisco = (unsigned int*) malloc(sizeof(int) * 1);
    (*registros)->qttCompacta = (unsigned int*) malloc(sizeof(int) * 1);
    iniciaRegistrosCabecalho((*registros));
}

//Desaloca memoria de todos os ponteiros do RegistroCabecalho.
void desalocaRegistrosCabecalho(RegistroCabecalho *registros)
{
    free(registros->status);
    free(registros->topo);
    free(registros->proxRRN);
    free(registros->nroRegRem);
    free(registros->nroPagDisco);
    free(registros->qttCompacta);
    free(registros);
}

//Exibe na tela um RegistroCabecalho.
void imprimeRegistroCabecalhoTela(RegistroCabecalho *registro)
{

    printf("Status: %c\n", *(registro->status));
    printf("Topo: %d\n", *(registro->topo));
    printf("Prox RRN: %d\n", *(registro->proxRRN));
    printf("Nro Pag Disco: %d\n", *(registro->nroPagDisco));
    printf("Nro Reg Rem: %d\n", *(registro->nroRegRem));
    printf("Qtt Compactacao: %d\n", *(registro->qttCompacta));
}
