#ifndef __ARQUIVOS_BIN_C__
#define __ARQUIVOS_BIN_C__

#include <stdlib.h>
#include "arquivoCsv.h"
#include "mensagens.h"
#include "registroCabecalho.h"
#include "registroDados.h"

FILE * abrirLeitura_bin(char * nome_arquivo);
FILE * abrirEscrita_bin(char * nome_arquivo);

int createTable(FILE* arquivobin, FILE* arquivocsv);

#endif