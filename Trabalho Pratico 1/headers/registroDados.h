#ifndef __REGISTROS_DADOS_C__
#define __REGISTROS_DADOS_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesFornecidas.h"

typedef struct {
    char* removido;
    int* encadeamento;
    int* idConecta;
    char* siglaPais;
    int* idPoPsConectado;
    char* unidadeMedida;
    int* velocidade;
    char* nomePoPs;
    char* nomePais;
}RegistroDados;

void alocaRegistrosDados(RegistroDados ** registros, int numReg);
void desalocaRegistrosDados(RegistroDados ** registros, int numReg);
void imprimeRegistroDadosTela(RegistroDados * registro);
void lerRegistroDadosTeclado(RegistroDados *registro);

typedef struct elemento {
    RegistroDados *dado;
    struct elemento *prox;
} elem;

void criaLista(elem *Lista, RegistroDados *dado);
void destroiLista(elem *Lista);
void imprimeLista(elem* Lista);
void insereLista(elem* Lista, RegistroDados *dado);

#endif