#define PROMOCAO 0
#define SEM_PROMOCAO 1
#define ERRO 2

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

int buscaChaveNo(noArvB * no, int chave, int* rrnBusca){
    if(chave <= *(no->C1)){
        if(chave == *(no->C1)){
            //rrn busca permanece o mesmo
            return 0; //encontrada na posicao 0 (chave 1)
        }
        *rrnBusca = *(no->P1);
        return -1; // chave nao esta nessa pagina
    }else if(chave <= *(no->C2)){
        if(chave == *(no->C2)){
            //rrn busca permanece o mesmo
            return 1; //encontrada na posicao 1 (chave 2)
        }
        *rrnBusca = *(no->P2);
        return -1; // chave nao esta nessa pagina
    }else if(chave <= *(no->C3)){
        if(chave == *(no->C3)){
            //rrn busca permanece o mesmo
            return 2; //encontrada na posicao 2 (chave 3)
        }
        *rrnBusca = *(no->P3);
        return -1; // chave nao esta nessa pagina
    }else if(chave <= *(no->C4)){
        if(chave == *(no->C4)){
            //rrn busca permanece o mesmo
            return 3; //encontrada na posicao 3 (chave 4)
        }
        *rrnBusca = *(no->P4);
        return -1; // chave nao esta nessa pagina
    }else{
        *rrnBusca = *(no->P5);
        return -1; // chave nao esta nessa pagina
    }
}

void escreveNoArqIndice(FILE* arqIndice,cabecalhoArvB* cabecalho ,noArvB* no, int rrn){
    int byteoffset = TAM_PAGINA_DISCO_ARV_B*(rrn + 1);
    fseek(arqIndice, byteoffset, SEEK_SET);

    fwrite(no->folha, sizeof(char), 1, arqIndice);
    fwrite(no->nroChavesNo, sizeof(int), 1, arqIndice);
    fwrite(no->alturaNo, sizeof(int), 1, arqIndice);
    fwrite(no->RRNdoNo, sizeof(int), 1, arqIndice);
    fwrite(no->P1, sizeof(int), 1, arqIndice);
    fwrite(no->C1, sizeof(int), 1, arqIndice);
    fwrite(no->PR1, sizeof(int), 1, arqIndice);
    fwrite(no->P2, sizeof(int), 1, arqIndice);
    fwrite(no->C2, sizeof(int), 1, arqIndice);
    fwrite(no->PR2, sizeof(int), 1, arqIndice);
    fwrite(no->P3, sizeof(int), 1, arqIndice);
    fwrite(no->C3, sizeof(int), 1, arqIndice);
    fwrite(no->PR3, sizeof(int), 1, arqIndice);
    fwrite(no->P4, sizeof(int), 1, arqIndice);
    fwrite(no->C4, sizeof(int), 1, arqIndice);
    fwrite(no->PR4, sizeof(int), 1, arqIndice);
    fwrite(no->P5, sizeof(int), 1, arqIndice);
    
}

void escreveCabecalhoArqIndice(FILE* arqIndice, cabecalhoArvB* cabecalho){
    fseek(arqIndice, 0, SEEK_SET);
    
    fwrite(cabecalho->status, sizeof(char), 1, arqIndice);
    fwrite(cabecalho->noRaiz, sizeof(int), 1, arqIndice);
    fwrite(cabecalho->nroChavesTotal, sizeof(int), 1, arqIndice);
    fwrite(cabecalho->alturaArvore, sizeof(int), 1, arqIndice);
    fread(cabecalho->RRNproxNo, sizeof(int), 1, arqIndice);

    char * lixo = malloc(sizeof(char)* TAM_PAGINA_DISCO_ARV_B);
    for(int i = 0; i<TAM_PAGINA_DISCO_ARV_B; i++){
        lixo[i] = '$';
    }
    fwrite(lixo, sizeof(char),TAM_PAGINA_DISCO_ARV_B -17, arqIndice);
}



void splitNosArvB(int chave, int filho_chave, noArvB * pagina, int* chave_promocao, int * filho_chave_promocao, noArvB * novaPagina){
    printf("implementar");
}

int insercaoRecursiva(FILE* arqIndice, int Cn, int PRn, noArvB* raiz, cabecalhoArvB* cabecalho, int RRN_atual, int* chave_promocao, int* filho_chave_promocao){
    
    noArvB * pagina;
    int resBusca = -1;    
    int rrnBusca = -1; // rrn de onde a chave buscada deveria estar
    printf("insercao recursiva %d\n", rrnBusca);

    if(RRN_atual == -1){
        *chave_promocao = Cn;
        *filho_chave_promocao = PRn; //fiz mudancaaa
        printf("voltou na recursao para promover\n");
        return PROMOCAO;
    }else{
        if(RRN_atual == *(cabecalho->noRaiz)){
            pagina = raiz;
        }else{
            pagina = leNoArvB_RRN(arqIndice, RRN_atual);
        }        
        resBusca = buscaChaveNo(pagina, Cn, &rrnBusca);
    }

    if(resBusca != -1){
        printf("Chave duplicada");
        return ERRO;
    }
    int chave_promocao_below = -1;
    int filho_chave_promocao_below = -1;

    int retorno = insercaoRecursiva(arqIndice, Cn, PRn, raiz, cabecalho, rrnBusca, &chave_promocao_below, &filho_chave_promocao_below);

    if(retorno == SEM_PROMOCAO || retorno == ERRO){
        return retorno;
    }else if(*(pagina->nroChavesNo) <4){ // se tem espaço no nó
        printf("promoveu: %d %d\n",chave_promocao_below, filho_chave_promocao_below);
        insereChaveOrdenadaNoArvB(pagina, chave_promocao_below, filho_chave_promocao_below);
        escreveNoArqIndice(arqIndice, cabecalho, pagina, *(pagina->RRNdoNo));
        return SEM_PROMOCAO;
    }else{
        noArvB * nova_pagina;
        alocaNoArvB(&nova_pagina, 1);
        splitNosArvB(chave_promocao_below, filho_chave_promocao_below, pagina, chave_promocao, filho_chave_promocao, nova_pagina);
        escreveNoArqIndice(arqIndice, cabecalho, pagina, RRN_atual);
        escreveNoArqIndice(arqIndice, cabecalho, nova_pagina, *filho_chave_promocao);
        return PROMOCAO;      
        
    }


}

int insercaoArvoreB(FILE* arqIndice, int Cn, int PRn, noArvB* raiz, cabecalhoArvB* cabecalho){
    if(*(cabecalho->noRaiz) == -1){
        //Situacao inicial (nenhum nó nem registro) 
        printf("nenhum no ainda\n");
        insereChaveOrdenadaNoArvB(raiz, Cn, PRn);
        *(raiz->folha) = 1;
        *(raiz->alturaNo) = 0;
        *(raiz->nroChavesNo) = 1;
        *(raiz->RRNdoNo) = 0;
        escreveNoArqIndice(arqIndice, cabecalho, raiz, 0);
        *(cabecalho->noRaiz) = 0;
        *(cabecalho->alturaArvore) = 1;
        *(cabecalho->nroChavesTotal) = 1;
        *(cabecalho->RRNproxNo) = 1;
        return SEM_PROMOCAO;
    }else{
        int chave_promo = -1;
        int filho_chave_promo = -1;
        
        return insercaoRecursiva(arqIndice, Cn, PRn, raiz, cabecalho, 0, &chave_promo, &filho_chave_promo);
    }
}