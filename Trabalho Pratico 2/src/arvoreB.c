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
    noArvB *no;
    alocaNoArvB(&no, 1);

    long byteofset = (RRN * TAM_PAGINA_DISCO_ARV_B) + TAM_PAGINA_DISCO_ARV_B;

    fseek(arquivoArvB, byteofset, SEEK_SET);
    
    fread(no->folha, sizeof(char), 1, arquivoArvB);
    fread(no->nroChavesNo, sizeof(int), 1, arquivoArvB);
    fread(no->alturaNo, sizeof(int), 1, arquivoArvB);
    fread(no->RRNdoNo, sizeof(int), 1, arquivoArvB);
    fread(no->P1, sizeof(int), 1, arquivoArvB);
    fread(no->C1, sizeof(int), 1, arquivoArvB);
    fread(no->PR1, sizeof(int), 1, arquivoArvB);
    fread(no->P2, sizeof(int), 1, arquivoArvB);
    fread(no->C2, sizeof(int), 1, arquivoArvB);
    fread(no->PR2, sizeof(int), 1, arquivoArvB);
    fread(no->P3, sizeof(int), 1, arquivoArvB);
    fread(no->C3, sizeof(int), 1, arquivoArvB);
    fread(no->PR3, sizeof(int), 1, arquivoArvB);
    fread(no->P4, sizeof(int), 1, arquivoArvB);
    fread(no->C4, sizeof(int), 1, arquivoArvB);
    fread(no->PR4, sizeof(int), 1, arquivoArvB);
    fread(no->P5, sizeof(int), 1, arquivoArvB);

    return no;
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