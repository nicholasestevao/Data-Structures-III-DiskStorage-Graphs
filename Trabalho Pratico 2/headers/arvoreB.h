#ifndef __ARVORE_B_C__
#define __ARVORE_B_C__

#include <stdlib.h>
#include "arquivoBin.h"
#include "arquivoCsv.h"
#include "mensagens.h"
#include "cabecalhoArvB.h"
#include "noArvB.h"

cabecalhoArvB* lecabecalhoArvB(FILE *arquivoArvB);
noArvB* leNoArvB_RRN(FILE *arquivoArvB, int RRN);
int buscaChaveArvoreB(FILE *arquivoArvB, int Cn, noArvB* raiz, noArv * resultado);

void escreveNoArqIndice(FILE *arqIndice, noArvB * no, int rrn);

int insercaoArvoreB(FILE* arqIndice, int Cn, int PRn, noArvB* raiz, cabecalhoArvB* cabecalho);

void splitNosArvB(noArvB * no1, noArvB * no2);
#endif