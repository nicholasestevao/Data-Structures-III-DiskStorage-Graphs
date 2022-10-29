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

int insercaoArvoreB(FILE* arqIndice, int Cn, int PRn, noArvB* raiz, cabecalhoArvB* cabecalho){
    if(*(cabecalho->noRaiz) == -1){
        //Situacao inicial (nenhum nó nem registro) 
        insereChaveOrdenadaNoArvB(raiz, Cn, PRn);
        escreveNoArqIndice(arqIndice, raiz, 0);
        *(cabecalho->noRaiz) = 0;
    }else{
        noArvB * resultadoBusca;
        buscaChaveArvoreB(arqIndice, Cn, raiz,resultadoBusca);
        if(*(resultadoBusca->nroChavesNo) <= 4){
            insereChaveOrdenadaNoArvB(raiz, Cn, PRn);
            escreveNoArqIndice(arqIndice, raiz, 0);
        }else{
            //split
            noArvB * novoNo;
            alocaNoArvB(novoNo, 1);
            splitNosArvB(resultadoBusca, novoNo);
        }
    }
}