#ifndef __FUNCIONALIDADES_C__
#define __FUNCIONALIDADES_C__

#include <iostream>
#include "mensagens.h"
#include "arquivoBin.h"
#include "arquivoCsv.h"
#include "arvoreB.h"
#include "grafo.h"
#include "funcoesFornecidas.h"

using std::cin;
using std::cout;

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
 * Cria um arquivo de indice utilizando um arqvuivo de dados, 
 * já criado pela funcionalidade 1, implementando uma Arvore B.
 * 
 * @param nome_arquivo Nome do arquivo de dados .bin.
 */
void funcionalidade7CreateIndex(char * nome_arquivo);

/**
 * Select where (Funcionalidade_8).
 * Exibe na tela todos os registros que possuem um valor, 
 * de um campo específico, igual ao valor do campo buscado.
 * Utilizando da busca pelo indice na Arvore B, caso o campo buscado 
 * seja a chave de indice (idConecta).
 * 
 * @param nome_arquivo Nome do arquivo de dados .bin.
 */
void funcionalidade8SelectWhere(char *nome_arquivo);

/**
 * Insert (Funcionalidade_5).
 * Insere registro, com valores obitidos do teclado, no arquivo binario 
 * e no arquivo de indice (Arvore B).
 * 
 * @param nome_arquivo Nome do arquivo de dados .bin.
 */
void funcionalidade9InsertArvB(char *nome_arquivo);

/**
 * Juncao (Funcionalidade_10).
 * Realiza a busca em um arquivo de indice por meio dos valores,
 * de um campo especifico, de todos os dados de um arquivo de
 * registro de dados. Essa busca eh realizada pelo 
 * valor de um campo de um registro do arquivo de dados no 
 * arquivo de indice (Arvore B).
 * Para o nosso arquivo indice soh pode ser realizada a juncao
 * "idPoPsConectado" = "idConecta". 
 * 
 * @param nome_arquivo Nome do arquivo de dados .bin a ser 
 * retirado os valores a serem buscados.
 */
void funcionalidade10Juncao(char *nome_arquivo);


Grafo * funcionalidade11CriarGrafo(char * nome_arquivo);

void funcionalidade12ContaCiclos(Grafo * g);

#endif