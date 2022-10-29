#include "../headers/arvoreB.h"

cabecalhoArvB* lecabecalhoArvB(FILE *arquivoArvB) {
    cabecalhoArvB *cabecalho;
    alocaCabecalhoArvB(&cabecalho);
    fseek(arquivoArvB, 0, SEEK_SET);
    
    fread(cabecalho->status, sizeof(char), 1, arquivoArvB);
    fread(cabecalho->noRaiz, sizeof(int), 1, arquivoArvB);
    fread(cabecalho->nroChavesTotal, sizeof(int), 1, arquivoArvB);
    fread(cabecalho->alturaArvore, sizeof(int), 1, arquivoArvB);
    fread(cabecalho->RRNproxNo, sizeof(int), 1, arquivoArvB);

    return cabecalho;
}

noArvB* leNoArvB_RRN(FILE *arquivoArvB, int RRN) {

}

int buscaArvoreB(FILE *arquivoArvB) {

}