#ifndef __NO_ARV_B__
#define __NO_ARV_B__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesFornecidas.h"

/**
 * 
 * @struct noArvB 
 * 
 * @var folha - 
 * @var nroChavesNo - 
 * @var alturaNo - 
 * @var RRNdoNo - 
 * @var P1 -
 * @var C1 -
 * @var PR1 -
 * @var P2 -
 * @var C2 -
 * @var PR2 -
 * @var P3 -
 * @var C3 -
 * @var PR3 -
 * @var P4 -
 * @var C4 -
 * @var PR4 -
 * @var P5 - 
 */
typedef struct {
    char* folha;
    int* nroChavesNo;
    int* alturaNo;
    int* RRNdoNo;
    int* P1;
    int* C1;
    int* PR1;
    int* P2;
    int* C2;
    int* PR2;
    int* P3;
    int* C3;
    int* PR3;
    int* P4;
    int* C4;
    int* PR4;
    int* P5;
}noArvB;


/**
 * Aloca memoria para todos os ponteiros do RegistroDados.
 * 
 * @param registros vetor de RegistroDados.
 * @param numReg quantidade de itens do vetor de RegistroDados
 */
void alocaNoArvB(noArvB ** registros, int numReg);

/**
 * Desaloca memoria de todos os ponteiros do RegistroDados.
 * 
 * @param registros vetor de RegistroDados.
 * @param numReg quantidade de itens do vetor de RegistroDados.
 */
void desalocaNoArvB(noArvB ** registros, int numReg);

/**
 * Insere uma chave de forma ordenada em um no da arvore-B.
 * 
 * @param  no No onde sera inserido a chave de forma ordenada.
 * @param Cn Chave a ser inserida.
 * @param PRn RRN da chave (Cn) no arquivo de dados.
 */
void insereChaveOrdenadaNoArvB(noArvB *no, int Cn, int PRn);

#endif