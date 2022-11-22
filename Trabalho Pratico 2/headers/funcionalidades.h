#ifndef __FUNCIONALIDADES_C__
#define __FUNCIONALIDADES_C__

#include <stdlib.h>
#include "mensagens.h"
#include "arquivoBin.h"
#include "arquivoCsv.h"
#include "arvoreB.h"
#include "funcoesFornecidas.h"

/**
 * Create Table (Funcionalidade_1).
 * Cria o arquivo binario a partir de uma tabela csv.
 * 
 * @param nome_arquivo_csv Nome do arquivo .csv.
 */
void funcionalidade1CreateTable(char* nome_arquivo_csv);

/**
 * Select (Funcionalidade_2).
 * Exibe na tela todos os registros de campos não nulos dos 
 * resgitros não removidos de um arquivo binario.
 * 
 * @param nome_arquivo Nome do arquivo .bin.
 */
void funcionalidade2Select(char* nome_arquivo);

/**
 * Select where (Funcionalidade_3).
 * Exibe na tela todos os registros que possuem um valor, 
 * de um campo específico, igual ao valor do campo buscado.
 * 
 * @param nome_arquivo Nome do arquivo binario.
 */
void funcionalidade3SelectWhere(char* nome_arquivo);

/**
 * Remove (Funcionalidade_4).
 * Remove todos registros logicamente que possuem o valor, 
 * de um campo específico, igual ao valor do campo buscado.
 * 
 * @param nome_arquivo Nome do arquivo .bin.
 */
void funcionalidade4Remove(char* nome_arquivo);

/**
 * Insert (Funcionalidade_5).
 * Insere registro, com valores obitidos do teclado, no arquivo binario.
 * 
 * @param nome_arquivo Nome do arquivo .bin.
 */
void funcionalidade5Insert(char* nome_arquivo);

/**
 * Compactacao (Funcionalidade_6).
 * Retira todos os registros logicamente removidos do arquivo binario.
 * 
 * @param nome_arquivo Nome do arquivo .bin.
 */
void funcionalidade6Compactacao(char* nome_arquivo);

/**
 * CreateIndex (Funcionalidade_7).
 * 
 * 
 * @param nome_arquivo Nome do arquivo .bin.
 */
void funcionalidade7CreateIndex(char * nome_arquivo);

/**
 * Select where (Funcionalidade_8).
 * 
 * @param nome_arquivo Nome do arquivo .bin.
 */
void funcionalidade8SelectWhere(char *nome_arquivo);

/**
 * Juncao (Funcionalidade_10).
 * 
 * @param nome_arquivo Nome do arquivo .bin.
 */
void funcionalidade10Juncao(char *nome_arquivo);


#endif