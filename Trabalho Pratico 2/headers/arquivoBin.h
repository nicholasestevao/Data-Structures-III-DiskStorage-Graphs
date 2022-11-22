#ifndef __ARQUIVOS_BIN_C__
#define __ARQUIVOS_BIN_C__

#include <stdlib.h>
#include "arquivoCsv.h"
#include "mensagens.h"
#include "registroCabecalho.h"
#include "registroDados.h"

/**
 * Abre arquivo binario para leitura. 
 * Nao atualiza o status.
 * 
 * @param nome_arquivo Nome do arquivo.
 * @return Retorna um ponteiro de arquivo em modo de leitura.
 * Se o arquivo estiver inconsistente na hora de abertura retorna NULL.
 */
FILE * abrirLeitura_bin(char * nome_arquivo);

/**
 * Abre arquivo binario para escrita. 
 * Atualiza o status do arquivo para Atualiza o status do 
 * arquivo para inconsistente (1) -> (0).
 * 
 * @param nome_arquivo Nome do arquivo.
 * 
 * @return Retorna um ponteiro de arquivo em modo de leitrua + escrita.
 * Se o arquivo estiver inconsistente na hora de abertura retorna NULL.
 */
FILE * abrirEscrita_bin(char * nome_arquivo);

/**
 * Fecha arquivo binario atualizando status
 * Necessario usar essa funcao apenas quando o arquivo foi aberto 
 * para escrita.
 * 
 * @param arquivo_bin Ponteiro para arquivo binario.
 */
void fecharArquivo_bin(FILE * arquivo_bin);

/**
 * Le registro de dados do arquivo binario por RRN.
 * 
 * @param arquivo_bin Ponteiro para arquivo binario.
 * @param RRN Numero Relativo do Registro.
 * 
 * @return Retorna um ponteiro para o dado do RRN.
 */ 
RegistroDados * lerRegistroDadosArquivoBin_RRN(FILE * arquivoBin,int RRN);

/**
 * Le registro de cabecalho do arquivo binario.
 * 
 * @param arquivo_bin Nome do arquivo.
 */
RegistroCabecalho * lerRegistroCabecalhoArquivoBin(FILE * arquivoBin);

/**
 * Insere registro de dados no arquivo binario
 * Pode inserir registro ja como removidos (caso eles 
 * venham assim do arquivo CSV).
 * 
 * @param arquivo_bin Ponteiro para arquivo binario.
 * @param registroCabecalho Registro de Cabecalho 
 * utilizado na insersao de dados no arquivo binario.
 * @param registroDados Registro de Dados a ser inserido no binario.
 */
void inserirRegistroDadosArquivoBin(FILE * arquivoBin, RegistroCabecalho * registroCabecalho, RegistroDados * registroDados);

/**
 * Grava registro de cabecalho no arquivo binario.
 * 
 * @param arquivo_bin Ponteiro para arquivo binario.
 * @param registroCabecalho Registro de Cabecalho 
 * a ser inserido no arquivo binario. 
 */
void escreverRegistroCabecalhoArquivoBin(FILE * arquivoBin, RegistroCabecalho * registroCabecalho); 

/**
 * Remove logicamente um registro do arquivo binario por RRN
 * e atualiza a pilha de registros removidos.
 * 
 * @param arquivo_bin Ponteiro para arquivo binario.
 * @param registroCabecalho Registro de Cabecalho 
 * utilizado na remocao de dados no arquivo binario 
 * para atualizar o topo da pilha de remocao.
 * @param RRN Numero Relativo do Registro.
 */
void removeRegistroDadosArquivoBin_RRN(FILE * arquivoBin, RegistroCabecalho * registroCabecalho, int RRN);

#endif