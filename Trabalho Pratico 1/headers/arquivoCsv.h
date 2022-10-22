#ifndef __ARQUIVOS_CSV_C__
#define __ARQUIVOS_CSV_C__

#include <stdlib.h>
#include "mensagens.h"

/**
 * Abre arquivo .csv para leitura. 
 * 
 * @param nome_arquivo Nome do arquivo.
 * @return Retorna um ponteiro de arquivo em modo de leitura.
 */
FILE * abrirLeitura_csv(char * nome_arquivo);

/**
 * Abre arquivo csv para escrita. 
 * 
 * @param nome_arquivo Nome do arquivo.
 * @return Retorna um ponteiro de arquivo em modo de escrita.
 */
FILE * abrirEscrita_csv(char * nome_arquivo);
#endif