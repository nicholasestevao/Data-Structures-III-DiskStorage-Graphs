#ifndef __ARQUIVOS_C__
#define __ARQUIVOS_C__

#include <stdlib.h>
#include "mensagens.h"

FILE * abrirLeitura_bin(char * nome_arquivo);
FILE * abrirEscrita_bin(char * nome_arquivo);

int armazenarRegistro(FILE * arquivo);
int recuperarArquivo(FILE * arquivo);
int recuperarRegistroRRN(FILE * arquivo, int RRN);

#endif