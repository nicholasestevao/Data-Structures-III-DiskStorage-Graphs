#ifndef __ARQUIVOS_C__
#define __ARQUIVOS_C__

#include <stdlib.h>
#include "mensagens.h"
#include "registros.h"

FILE * abrirLeitura_bin(char * nome_arquivo);
FILE * abrirEscrita_bin(char * nome_arquivo);

int armazenarRegistros(FILE * arquivo, int numReg, Registro * registros);
int tratarRegistro(Registro * registro);
int recuperarArquivo(FILE * arquivo);
int recuperarRegistroRRN(FILE * arquivo, int RRN);

#endif