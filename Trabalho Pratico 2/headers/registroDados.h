#ifndef __REGISTROS_DADOS_C__
#define __REGISTROS_DADOS_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesFornecidas.h"

/**
 * 
 * @struct RegistroDados 
 * 
 * @var removido - status de remocao
 * @var encadeamento - proximo RRN da pilha
 * @var idConecta - campo
 * @var siglaPais - campo
 * @var idPoPsConectado - campo
 * @var unidadeMedida - campo
 * @var velocidade - campo
 * @var nomePoPs - campo
 * @var nomePais - campo
 */
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

/**
 * Aloca memoria para todos os ponteiros do RegistroDados.
 * 
 * @param registros vetor de RegistroDados.
 * @param numReg quantidade de itens do vetor de RegistroDados
 */
void alocaRegistrosDados(RegistroDados ** registros, int numReg);

/**
 * Desaloca memoria de todos os ponteiros do RegistroDados.
 * 
 * @param registros vetor de RegistroDados.
 * @param numReg quantidade de itens do vetor de RegistroDados.
 */
void desalocaRegistrosDados(RegistroDados ** registros, int numReg);

/**
 * Exibe na tela um RegistroDados.
 * 
 * @param  registro RegistroDados a ser exibido na tela.
 */
void imprimeRegistroDadosTela(RegistroDados * registro);

/**
 * Exibe na tela a juncao de dois Registro de dados.
 * 
 * @param dado1 RegistroDados a ser exibido na tela.
 * @param dado2 RegistroDados a ser exibido na tela.
 */
void imprimeJuncaoRegistrosDados(RegistroDados *dado1, RegistroDados * dado2);

/**
 * Recebe um RegisroDados do teclado e 
 * coloca na RAM.
 * 
 * @param registro Ponteiro para o RegistroDados na RAM.
 */
void lerRegistroDadosTeclado(RegistroDados *registro);

#endif