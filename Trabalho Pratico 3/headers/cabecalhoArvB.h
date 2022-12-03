#ifndef __CABECALHO_ARV_B_C__
#define __CABECALHO_ARV_B_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 
 * @struct CabecalhoArvB.
 * 
 * @var statius - Status de inconsistencia do arquivo.
 * @var noRaiz - RRN do atual no raiz da Arvore B.
 * @var nroChavesTotal - Quantidade total de chaves na arvore B.
 * @var alturaArvore - Altura atual da arvore.
 * @var RRNproxNo - proximo RRN disponivel para insercao de no.
 */
typedef struct
{
    char *status;
    int *noRaiz;
    unsigned int *nroChavesTotal;
    unsigned int *alturaArvore;
    unsigned int *RRNproxNo;
} CabecalhoArvB;

/**
 * Aloca memoria para todos os ponteiros do CabecalhoArvB.
 * 
 * @param registros Ponteiro para CabecalhoArvB.
 */
void alocaCabecalhoArvB(CabecalhoArvB **registro);

/**
 * Desaloca memoria para todos os ponteiros do CabecalhoArvB.
 * 
 * @param registros Ponteiro para CabecalhoArvB.
 */
void desalocaCabecalhoArvB(CabecalhoArvB *registro);

/**
 * Exibe na tela um CabecalhoArvB.
 * 
 * @param  registro CabecalhoArvB a ser exibido na tela.
 */
void imprimeCabecalhoArvBTela(CabecalhoArvB *cabecalho);

#endif