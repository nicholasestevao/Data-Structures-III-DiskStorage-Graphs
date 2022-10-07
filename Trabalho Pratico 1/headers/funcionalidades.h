#ifndef __FUNCIONALIDADES_C__
#define __FUNCIONALIDADES_C__

#include <stdlib.h>
#include "mensagens.h"
#include "arquivoBin.h"
#include "arquivoCsv.h"
#include "funcoesFornecidas.h"

void funcionalidade1CreateTable(char* nome_arquivo_bin, char* nome_arquivo_csv);

void funcionalidade2Select(char* nome_arquivo);

void funcionalidade3SelectWere(char* nome_arquivo);

void funcionalidade5Insert(char* nome_arquivo, int nro_reg);


#endif