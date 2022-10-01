#ifndef __ARQUIVOS_BIN_C__
#define __ARQUIVOS_BIN_C__

#include <stdlib.h>
#include "mensagens.h"
#include "registroCabecalho.h"
#include "registroDados.h"

//Abre arquivo binario para leitura
//Nao atualiza o status
FILE * abrirLeitura_bin(char * nome_arquivo);

//Abre arquivo binario para escrita
//Atualiza o status do arquivo para (1) -> Inconsistente
FILE * abrirEscrita_bin(char * nome_arquivo);

//Fecha arquivo binario atualizando status
//Necessario usar essa funcao apenas quando o arquivo foi aberto para escrita
void fecharArquivo_bin(FILE * arquivo_bin);

//Le registro de dados do arquivo binario por RRN
RegistroDados * lerRegistroDadosArquivoBin_RRN(FILE * arquivoBin,int RRN);

//Le registro de cabecalho do arquivo binario
RegistroCabecalho * lerRegistroCabecalhoArquivoBin(FILE * arquivoBin);

//Insere registro de dados no arquivo binario
//Pode inserir registro ja como removidos (caso eles venham assim do arquivo CSV)
void inserirRegistroDadosArquivoBin(FILE * arquivoBin, RegistroCabecalho * registroCabecalho, RegistroDados * registroDados);

//Grava registro de cabecalho no arquivo binario
int escreverRegistroCabecalhoArquivoBin(FILE * arquivoBin, RegistroCabecalho * registroCabecalho); 

#endif