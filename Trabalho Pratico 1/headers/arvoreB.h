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
int buscaArvoreB(FILE *arquivoArvB);


#endif