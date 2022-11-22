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
    fread(&(no->descendentes[0]), sizeof(int), 1, arquivoArvB);
    fread(no->chaves[0].chave, sizeof(int), 1, arquivoArvB);
    fread(no->chaves[0].rrnDados, sizeof(int), 1, arquivoArvB);
    fread(&(no->descendentes[1]), sizeof(int), 1, arquivoArvB);
    fread(no->chaves[1].chave, sizeof(int), 1, arquivoArvB);
    fread(no->chaves[1].rrnDados, sizeof(int), 1, arquivoArvB);
    fread(&(no->descendentes[2]), sizeof(int), 1, arquivoArvB);
    fread(no->chaves[2].chave, sizeof(int), 1, arquivoArvB);
    fread(no->chaves[2].rrnDados, sizeof(int), 1, arquivoArvB);
    fread(&(no->descendentes[3]), sizeof(int), 1, arquivoArvB);
    fread(no->chaves[3].chave, sizeof(int), 1, arquivoArvB);
    fread(no->chaves[3].rrnDados, sizeof(int), 1, arquivoArvB);
    fread(&(no->descendentes[4]), sizeof(int), 1, arquivoArvB);

    return no;
}

int buscaChaveNo(noArvB *no, int chave, int* rrnBusca){
    int i = 0;
    printf("Buscando %d\n", chave);
    imprimeNoTela(no);
    while(i< *(no->nroChavesNo) && *((no->chaves[i]).chave) <= chave){
        if(*((no->chaves[i]).chave) == chave){
            *rrnBusca = -1;
            return -1;//encontrou
        }
        i++;
    }
    printf("Filho da posicao %d\n", i);
    *rrnBusca = no->descendentes[i];
    return i;
}

int buscaChaveArvoreB(FILE* arquivoArvB, long RRN, int chave, noArvB *resultado, int *pos) {
    long nroPagDiscoAcessadas = 0;
    if(RRN != -1) {
        nroPagDiscoAcessadas = 1;
        noArvB* no = leNoArvB_RRN(arquivoArvB, RRN);
        int i = 0 ;
        while(i < *(no->nroChavesNo) && *((no->chaves[i]).chave) <= chave){
            if(*((no->chaves[i]).chave) == chave) {
                resultado = no;
                *pos = i;
                return nroPagDiscoAcessadas;
            }
            i++;
        }
        RRN = no->descendentes[i];
        desalocaNoArvB(&no, 1);
        nroPagDiscoAcessadas += buscaChaveArvoreB(arquivoArvB, RRN, chave, resultado, pos);
    }
    return nroPagDiscoAcessadas;
}

void escreveNoArqIndice(FILE* arqIndice,cabecalhoArvB* cabecalho ,noArvB* no, int rrn){
    int byteoffset = TAM_PAGINA_DISCO_ARV_B*(rrn + 1);
    fseek(arqIndice, byteoffset, SEEK_SET);

    fwrite(no->folha, sizeof(char), 1, arqIndice);
    fwrite(no->nroChavesNo, sizeof(int), 1, arqIndice);
    fwrite(no->alturaNo, sizeof(int), 1, arqIndice);
    fwrite(no->RRNdoNo, sizeof(int), 1, arqIndice);
    fwrite(&(no->descendentes[0]), sizeof(int), 1, arqIndice);
    fwrite(no->chaves[0].chave, sizeof(int), 1, arqIndice);
    fwrite(no->chaves[0].rrnDados, sizeof(int), 1, arqIndice);
    fwrite(&(no->descendentes[1]), sizeof(int), 1, arqIndice);
    fwrite(no->chaves[1].chave, sizeof(int), 1, arqIndice);
    fwrite(no->chaves[1].rrnDados, sizeof(int), 1, arqIndice);
    fwrite(&(no->descendentes[2]), sizeof(int), 1, arqIndice);
    fwrite(no->chaves[2].chave, sizeof(int), 1, arqIndice);
    fwrite(no->chaves[2].rrnDados, sizeof(int), 1, arqIndice);
    fwrite(&(no->descendentes[3]), sizeof(int), 1, arqIndice);
    fwrite(no->chaves[3].chave, sizeof(int), 1, arqIndice);
    fwrite(no->chaves[3].rrnDados, sizeof(int), 1, arqIndice);
    fwrite(&(no->descendentes[4]), sizeof(int), 1, arqIndice);    
}

void escreveCabecalhoArqIndice(FILE* arqIndice, cabecalhoArvB* cabecalho){
    fseek(arqIndice, 0, SEEK_SET);
    
    fwrite(cabecalho->status, sizeof(char), 1, arqIndice);
    fwrite(cabecalho->noRaiz, sizeof(int), 1, arqIndice);
    fwrite(cabecalho->nroChavesTotal, sizeof(int), 1, arqIndice);
    fwrite(cabecalho->alturaArvore, sizeof(int), 1, arqIndice);
    fwrite(cabecalho->RRNproxNo, sizeof(int), 1, arqIndice);

    char * lixo = malloc(sizeof(char)* TAM_PAGINA_DISCO_ARV_B);
    for(int i = 0; i<TAM_PAGINA_DISCO_ARV_B; i++){
        lixo[i] = '$';
    }
    fwrite(lixo, sizeof(char),TAM_PAGINA_DISCO_ARV_B -17, arqIndice);
}



void splitNosArvB(Chave chave, int filho_chave, noArvB * pagina, Chave* chave_promocao, int * filho_chave_promocao, noArvB * novaPagina, int rrnNovaPagina){
    //recebe um no cheio, uma chave para inserir e um no vazio
    //retorna a chave que foi promovida
    printf("Split para inserir chave %d\n", *(chave.chave));
    int no[16];
    for(int i=0; i<4; i++){
        no[i*3] = pagina->descendentes[i];
        no[i*3+1] = *(pagina->chaves[i].chave);
        no[i*3+2] = *(pagina->chaves[i].rrnDados);
    }
    no[12] = pagina->descendentes[4];
    for(int i = 13; i<16; i++){
        no[i] = -1;
    }
    for(int i=0; i<16; i++){
       // printf("%d ", no[i]);
    }
   // printf("\n ");
    int i = 0;
    while(i<5 && no[i*3 + 1] < *(chave.chave)){
        i++;
    }
    //printf("i: %d", i);
    for(int j=3; j>=i; j--){
        no[j*3+3] = no[j*3];
        no[j*3+4] = no[j*3+1];
        no[j*3+5] = no[j*3+2]; 
    }
    no[3*i+1] = *(chave.chave);
    no[3*i+2] = *(chave.rrnDados); 

    for(int i=0; i<16; i++){
        //printf("%d ", no[i]);
    }
    pagina->descendentes[0] = no[0];
    *(pagina->chaves[0].chave) = no[1];
    *(pagina->chaves[0].rrnDados) = no[2];
    pagina->descendentes[1] = no[3];
    *(pagina->chaves[1].chave) = no[4];
    *(pagina->chaves[1].rrnDados) = no[5];
    pagina->descendentes[2] = no[6];
    *(pagina->chaves[2].chave) = -1;
    *(pagina->chaves[2].rrnDados) = -1;
    pagina->descendentes[3] = -1;
    *(pagina->chaves[3].chave) = -1;
    *(pagina->chaves[3].rrnDados) = -1;
    pagina->descendentes[4] = -1;

    *(chave_promocao->chave) = no[7];
    *(chave_promocao->rrnDados) = no[8];
    *filho_chave_promocao = rrnNovaPagina;

    novaPagina->descendentes[0] = no[9];
    *(novaPagina->chaves[0].chave) = no[10];
    *(novaPagina->chaves[0].rrnDados) = no[11];
    novaPagina->descendentes[1] = no[12];
    *(novaPagina->chaves[1].chave) = no[13];
    *(novaPagina->chaves[1].rrnDados) = no[14];
    novaPagina->descendentes[2] = no[15];

    *(pagina->nroChavesNo) = 2;
    *(novaPagina->nroChavesNo) = 2;
    
    *(novaPagina->RRNdoNo) = rrnNovaPagina;
    printf("Promoveu: %d (rrn: %d), filho: %d rrn novo: %d\n", *(chave_promocao->chave), *(chave_promocao->rrnDados), *filho_chave_promocao, rrnNovaPagina);
    printf("Fez split: \n");
    imprimeNoTela(pagina);
    imprimeNoTela(novaPagina);
}

int insercaoRecursiva(FILE* arqIndice, Chave Cn, noArvB* raiz, cabecalhoArvB* cabecalho, int RRN_atual, Chave* chave_promocao, int* filho_chave_promocao){
    
    noArvB * pagina;
    int resBusca = -1;    
    int rrnBusca = -1; // rrn de onde a chave buscada deveria estar
    printf("insercao recursiva. RRN Atual: %d\n", RRN_atual);

    if(RRN_atual == -1){
        *chave_promocao = Cn;
        *filho_chave_promocao = -1; //fiz mudancaaa
        printf("voltou na recursao para promover\n");
        return PROMOCAO;
    }else{
        if(RRN_atual == *(cabecalho->noRaiz)){
            pagina = raiz;
            imprimeNoTela(pagina);
        }else{
            pagina = leNoArvB_RRN(arqIndice, RRN_atual);
        }    
        printf("Buscando no %d\n", rrnBusca);    
        resBusca = buscaChaveNo(pagina, *(Cn.chave), &rrnBusca);
    }

    if(resBusca == -1){
        printf("Chave duplicada\n");
        return ERRO;
    }else{
        printf("Chave nao duplicada. Resultado busca: %d - RRN Atual: %d\n", rrnBusca, RRN_atual);
    }
    Chave chave_promocao_below;
    chave_promocao_below.chave = malloc(sizeof(int));
    chave_promocao_below.rrnDados = malloc(sizeof(int));
    *(chave_promocao_below.chave) = -1;
    *(chave_promocao_below.rrnDados) = -1;
    int filho_chave_promocao_below = -1;

    int retorno = insercaoRecursiva(arqIndice, Cn, raiz, cabecalho, rrnBusca, &chave_promocao_below, &filho_chave_promocao_below);

    if(retorno == SEM_PROMOCAO || retorno == ERRO){
        return retorno;
    }else if(*(pagina->nroChavesNo) <4){ // se tem espaço no nó
        printf("promoveu: %d (rrn: %d) filho: %d\n",*(chave_promocao_below.chave), *(chave_promocao_below.rrnDados), filho_chave_promocao_below);
        imprimeNoTela(pagina);
        insereChaveOrdenadaNoArvB(pagina, chave_promocao_below, filho_chave_promocao_below);
        *(cabecalho->nroChavesTotal) +=1;
        escreveNoArqIndice(arqIndice, cabecalho, pagina, *(pagina->RRNdoNo));
        return SEM_PROMOCAO;
    }else{
        noArvB * nova_pagina;
        alocaNoArvB(&nova_pagina, 1);
        splitNosArvB(chave_promocao_below, filho_chave_promocao_below, pagina, chave_promocao, filho_chave_promocao, nova_pagina, *(cabecalho->RRNproxNo));

        *(cabecalho->nroChavesTotal) +=1;
        *(cabecalho->RRNproxNo) = *(cabecalho->RRNproxNo) + 1;
        *(cabecalho->alturaArvore) +=1;
        escreveNoArqIndice(arqIndice, cabecalho, pagina, RRN_atual);
        escreveNoArqIndice(arqIndice, cabecalho, nova_pagina, *filho_chave_promocao);
        //incrementar proximo rrn e tals  (conferir se função escrever faz isso)
        printf("Retornou promocao\n");
        return PROMOCAO;      
        
    }


}

int insercaoArvoreB(FILE* arqIndice, int Cn, int PRn, noArvB* raiz, cabecalhoArvB* cabecalho){
    Chave chave;
    chave.chave = malloc(sizeof(int));
    chave.rrnDados = malloc(sizeof(int));
    *(chave.chave) = Cn;
    *(chave.rrnDados) = PRn;
    
    if(*(cabecalho->noRaiz) == -1){
        //Situacao inicial (nenhum nó nem registro) 
        printf("Nenhum no ainda\n");
        insereChaveOrdenadaNoArvB(raiz, chave, -1);
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
        Chave chave_promo;
        chave_promo.chave = malloc(sizeof(int));
        chave_promo.rrnDados = malloc(sizeof(int));
        *(chave_promo.chave) = -1;
        *(chave_promo.rrnDados) = -1;
        int filho_chave_promo = -1;

       if( insercaoRecursiva(arqIndice, chave, raiz, cabecalho, *(cabecalho->noRaiz), &chave_promo, &filho_chave_promo) == PROMOCAO){
            printf("Ocorreu split na raiz\n");
            inicializaNoArvB(raiz);
            *(raiz->RRNdoNo)  = *(cabecalho->RRNproxNo);
            raiz->descendentes[0] = *(cabecalho->noRaiz);
            raiz->descendentes[1] = filho_chave_promo;
            *(raiz->chaves[0].chave) = *(chave_promo.chave); 
            *(raiz->chaves[0].rrnDados) = *(chave_promo.rrnDados); 
            *(raiz->nroChavesNo) = 1;
            *(cabecalho->RRNproxNo) = *(cabecalho->RRNproxNo) + 1;
            *(cabecalho->noRaiz) = *(raiz->RRNdoNo);
            //printf("Nova raiz:\n");
            //imprimeNoTela(raiz);
            escreveCabecalhoArqIndice(arqIndice,cabecalho);
            escreveNoArqIndice(arqIndice, cabecalho, raiz, *(raiz->RRNdoNo));

       }
    }

    return PROMOCAO;
}