#ifndef __ARVORE_B_C__
#define __ARVORE_B_C__

#include <stdlib.h>
#include "arquivoBin.h"
#include "arquivoCsv.h"
#include "mensagens.h"
#include "cabecalhoArvB.h"
#include "noArvB.h"

/**
 * Tamanho do registro de dados (no da arv-B) do 
 * arquivo da arvore-B.
 */
#define TAM_REGISTRO_DADOS_ARV_B 65

/**
 * Tamanho do registro de cabecalho (no da arv-B) do 
 * arquivo da arvore-B.
 */
#define TAM_REGISTRO_CABECALHO_ARV_B 17

/**
 * Tamanho da pagina de disco do arquivo da arvore-B.
 */
#define TAM_PAGINA_DISCO_ARV_B TAM_REGISTRO_DADOS_ARV_B

//=====================================================================

/**
 * Abre arquivo da arvore-B para leitura. 
 * Nao atualiza o status.
 * 
 * @param nome_arquivo Nome do arquivo.
 * @return Retorna um ponteiro de arquivo em modo de leitura.
 * Se o arquivo estiver inconsistente na hora de abertura retorna NULL.
 */
FILE* abrirLeitura_ArvB(char* nome_arquivo);

/**
 * Abre arquivo da arvore-B para escrita. 
 * Atualiza o status do arquivo para (1) -> Inconsistente.
 * 
 * @param nome_arquivo Nome do arquivo.
 * 
 * @return Retorna um ponteiro de arquivo em modo de leitrua + escrita.
 * Se o arquivo estiver inconsistente na hora de abertura retorna NULL.
 */
FILE* abrirEscrita_ArvB(char* nome_arquivo);

/**
 * 
 */
int buscaChaveArvoreB(FILE* arquivoArvB, int Cn, noArvB* raiz, noArvB* resultado);

/**
 * Escreve registro de cabecalho no arquivo da arvore-B.
 * 
 * @param arquivoArvB Ponteiro para arquivo da arcore-B.
 * @param cabecalho Ponteiro para cabecalho a ser 
 * escrito no aquivo da arvore-B.  
 */
void escreverCabecalhoArquivoAvrB(FILE* arquivoArvB, cabecalhoArvB* cabecalho); 

/**
 * Escreve noh no arquivo da arvore-B no RRN do noh.
 * 
 * @param arquivoArvB Ponteiro para arquivo da arvore-B.
 * @param no Ponteiro para no a ser 
 * escrito no arquivo da arvore-B.
 * @param RRN onde sera escrito o no no arquivo da arvore-B.
 */
void escreveNoArvB(FILE* arquivoArvB, noArvB* no);

/**
 * Não Lembro o q era pra fazer.
 */
void escreveNoArqIndice(FILE* arqIndice, noArvB* no, long RRN);

/**
 * Fecha arquivo binario atualizando status
 * Necessario usar essa funcao apenas quando o arquivo foi aberto 
 * para escrita.
 * 
 * @param arquivo_ArvB Ponteiro para arquivo da arvore-B.
 */
void fecharArquivo_ArvB(FILE* arquivo_ArvB);

/**
 * 
 */
int insercaoArvoreB(FILE* arqIndice, int Cn, int PRn, noArvB* raiz, cabecalhoArvB* cabecalho);

/**
 * Le registro de cabecalho do arquivo da arvore-B.
 * 
 * @param arquivoArvB Nome do arquivo.
 */
cabecalhoArvB* lecabecalhoArvB(FILE* arquivoArvB);

/**
 * Le registro de dados do arquivo da arvore-B por RRN.
 * 
 * @param arquivoArvB Nome do arquivo.
 * @param RRN Numero Relativo do Registro.
 * 
 * @return Retorna um ponteiro para o dado do RRN.
 */ 
noArvB* leNoArvB_RRN(FILE* arquivoArvB, long RRN);

/**
 * 
 */
void splitNosArvB(noArvB* no1, noArvB* no2);

#endif