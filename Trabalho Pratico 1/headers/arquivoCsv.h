#ifndef __ARQUIVOS_CSV_C__
#define __ARQUIVOS_CSV_C__

#include <stdlib.h>
#include "mensagens.h"

FILE * abrirLeitura_csv(char * nome_arquivo);
FILE * abrirEscrita_csv(char * nome_arquivo);

#endif