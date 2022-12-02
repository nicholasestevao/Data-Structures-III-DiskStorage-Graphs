#ifndef __NO_ARV_B__
#define __NO_ARV_B__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "funcoesFornecidas.h"

/**
 * 
 * @struct Chave 
 * 
 * @var chave - Valor da chave de indice.
 * @var rrnDados - RRN do registro de dados equivalente
 * no arquivo de dados.
 */
typedef struct
{
    int chave;
    int rrnDados;
} Chave;

/**
 * 
 * @struct NoArvB 
 * 
 * @var folha - indicacao de no folha.
 * @var nroChavesNo - quantidade de chaves inseridas no no.
 * @var alturaNo - altura do na Arvore B.
 * @var RRNdoNo - RRN do no no arquivo de indice.
 * @var chaves - Vetor de chaves do no.
 * @var descendentes - Descendentes de cada chave inserida no no.
 */
typedef struct
{
    char *folha;
    int *nroChavesNo;
    int *alturaNo;
    int *RRNdoNo;
    Chave *chaves;
    int *descendentes;
} NoArvB;

/**
 * Aloca memoria de todos os ponteiros de nos da 
 * arvore B.
 *
 * @param no vetor de no.
 * @param numReg quantidade de itens do vetor de nos.
 */
void alocaNoArvB(NoArvB **registros, int numReg);

/**
 * Desaloca memoria de todos os ponteiros de nos da 
 * arvore B.
 *
 * @param no vetor de no.
 * @param numReg quantidade de itens do vetor de nos.
 */
void desalocaNoArvB(NoArvB **no, int numReg);

/**
 * Insere uma chave de forma ordenada em um no da arvore-B.
 *
 * @param  no No onde sera inserido a chave de forma ordenada.
 * @param Cn Chave a ser inserida.
 * @param PRn RRN da chave (Cn) no arquivo de dados.
 */
void insereChaveOrdenadaNoArvB(NoArvB *no, Chave Cn, int filho);

/**
 * Imprime no da arvore B na tela.
 * 
 * @param no No a ser impresso na tela.
 */
void imprimeNoTela(NoArvB *no);

/**
 * Preenche os valores padrao de um no da arvore B.
 * 
 * @param no No a ser inicializado com os valores padrao. 
 */
void inicializaNoArvB(NoArvB *no);

/**
 * Busca uma chave em no um na da arvore B.
 * 
 * @param no No onde sera realizado a busca.
 * @param chave Que sera buscada no no.
 * @param rrnBusca Retorno por parametro do RRN do no 
 * filho onde a chave deveria estar.
 * 
 * @return retorna o RRN do registro de dado equivalente 
 * da chave encontrada.
*/
int buscaChaveNo(NoArvB *no, int chave, int* rrnBusca);
#endif