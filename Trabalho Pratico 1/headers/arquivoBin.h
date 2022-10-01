#ifndef __ARQUIVOS_BIN_C__
#define __ARQUIVOS_BIN_C__

#include <stdlib.h>
#include "mensagens.h"
#include "registroCabecalho.h"
#include "registroDados.h"


FILE * abrirLeitura_bin(char * nome_arquivo);
FILE * abrirEscrita_bin(char * nome_arquivo);

void fecharArquivo_bin(FILE * arquivo_bin);

RegistroDados * lerRegistroDadosArquivoBin_RRN(FILE * arquivoBin,int RRN);
RegistroCabecalho * lerRegistroCabecalhoArquivoBin(FILE * arquivoBin);

RegistroCabecalho * inserirRegistroDadosArquivoBin(FILE * arquivoBin, RegistroCabecalho * registroCabecalho, RegistroDados * registroDados);
int escreverRegistroCabecalhoArquivoBin(FILE * arquivoBin, RegistroCabecalho * registroCabecalho); 

#endif