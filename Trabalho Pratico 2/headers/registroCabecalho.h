#ifndef __REGISTROS_CABECALHO_C__
#define __REGISTROS_CABECALHO_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 
 * @struct RegistroCabecalho.
 * 
 * @var statius - status de inconsistencia do arquivo.
 * @var topo - RRN no topo da pilha.
 * @var proxRRN - proximo RRN disponivel (nao removido).
 * @var nroRegRem - quantidade de registros removidos.
 * @var nroPagDisco - quantidade de paginas de disco usadas.
 * @var qttCompacta - quantidade de vezes que o arquivo foi compactado/desfragmentado.
 */
typedef struct {
    char* status;
    int* topo;
    unsigned int* proxRRN;
    unsigned int* nroRegRem;
    unsigned int* nroPagDisco;
    unsigned int* qttCompacta;
}RegistroCabecalho;

/**
 * Aloca memoria para todos os ponteiros do RegistroCabecalho.
 * 
 * @param registros Ponteiro para RegistroCabecalho.
 */
void alocaRegistrosCabecalho(RegistroCabecalho **registro);

/**
 * Desaloca memoria de todos os ponteiros do RegistroCabecalho.
 * 
 * @param registros Ponteiro de RegistroDados.
 */
void desalocaRegistrosCabecalho(RegistroCabecalho *registro);

/**
 * Exibe na tela um RegistroCabecalho.
 * 
 * @param  registro RegistroCabecalho a ser exibido na tela.
 */
void imprimeRegistroCabecalhoTela(RegistroCabecalho * registro);
#endif