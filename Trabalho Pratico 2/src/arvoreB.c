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
    while(i< *(no->nroChavesNo) && *((no->chaves[i]).chave) <= chave){
        if(*((no->chaves[i]).chave) == chave){
            *rrnBusca = -1;
            return -1;//encontrou
        }
        i++;
    }
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


void splitNosArvB(FILE * arq_indice, Chave chave, int filho_chave, noArvB * pagina, Chave* chave_promocao, int * filho_chave_promocao, noArvB * novaPagina, int rrnNovaPagina){
    //Recebe um nó cheio, uma chave para inserir e um nó vazio
    //Retorna a chave que foi promovida

    int no[16]; // vetor auxiliar que funciona como um no que cabe 5 chaves (armezana todos os ponteiros, chaves e RRNs)
    // Preenche vetor no com os dados do nó atual (cheio)
    for(int i=0; i<4; i++){
        no[i*3] = pagina->descendentes[i];
        no[i*3+1] = *(pagina->chaves[i].chave);
        no[i*3+2] = *(pagina->chaves[i].rrnDados);
    }
    no[12] = pagina->descendentes[4];
    // Preenche final do vetor (dados da quinta chave) no com -1
    for(int i = 13; i<16; i++){
        no[i] = -1;
    }

    // Encontra posicao onde a chave deve ser inserida
    int i = 0;
    while(i<4 && no[i*3 + 1] < *(chave.chave)){
        i++;
    }

    // Desloca dados das chaves maiores do que a que será inserida para a direita (abre espaço para inserir a chave no "meio")
    no[15] = no[12]; // descendente[4]
    for(int j=3; j>=i; j--){
        no[j*3+3] = no[j*3];
        no[j*3+4] = no[j*3+1];
        no[j*3+5] = no[j*3+2]; 
    }
    // Insere dados da quinta chave no "meio"
    no[3*i+1] = *(chave.chave);
    no[3*i+2] = *(chave.rrnDados); 
    no[3*i+3] = filho_chave;

    // Passa os dados do vetor no para a pagina original
    pagina->descendentes[0] = no[0];
    *(pagina->chaves[0].chave) = no[1];
    *(pagina->chaves[0].rrnDados) = no[2];
    pagina->descendentes[1] = no[3];
    *(pagina->chaves[1].chave) = no[4];
    *(pagina->chaves[1].rrnDados) = no[5];
    pagina->descendentes[2] = no[6];
    // Reseta as duas ultima das chaves do no que estava cheio
    *(pagina->chaves[2].chave) = -1;
    *(pagina->chaves[2].rrnDados) = -1;
    pagina->descendentes[3] = -1;
    *(pagina->chaves[3].chave) = -1;
    *(pagina->chaves[3].rrnDados) = -1;
    pagina->descendentes[4] = -1;

    // Preenche dados da chave a ser promovida (a que esta no meio do vetor no)
    *(chave_promocao->chave) = no[7];
    *(chave_promocao->rrnDados) = no[8];
    *filho_chave_promocao = rrnNovaPagina;

    // Passa os dados do vetor no para a nova pagina
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
    
    // Novo nó criado no mesmo nivel
    *(novaPagina->alturaNo) = *(pagina->alturaNo);

    // Como estao no mesmo nivel, configuracao de folha permanece a mesma
    if(*(pagina->alturaNo) != 1){
        *(pagina->folha) = '0';
        *(novaPagina->folha) = '0';
    }else{
        *(pagina->folha) = '1';
        *(novaPagina->folha) = '1';
    }
    
    //printf("Promoveu: %d (rrn: %d), filho: %d rrn novo: %d\n", *(chave_promocao->chave), *(chave_promocao->rrnDados), *filho_chave_promocao, rrnNovaPagina);
    
}

int insercaoRecursiva(FILE* arqIndice, Chave Cn, noArvB* raiz, cabecalhoArvB* cabecalho, int RRN_atual, Chave* chave_promocao, int* filho_chave_promocao){
    
    noArvB * pagina;
    int resBusca = -1;    
    int rrnBusca = -1; // rrn de onde a chave buscada deveria estar

    // Desce na arvore ate encontrar o no onde a chave deve ser inserida
    if(RRN_atual == -1){
        *chave_promocao = Cn;
        *filho_chave_promocao = -1;
        return PROMOCAO;
    }else{
        if(RRN_atual == *(cabecalho->noRaiz)){
            pagina = raiz;
        }else{
            pagina = leNoArvB_RRN(arqIndice, RRN_atual);
        }    
        resBusca = buscaChaveNo(pagina, *(Cn.chave), &rrnBusca);
    }

    if(resBusca == -1){
        //Chave duplicada
        return ERRO;
    }

    Chave chave_promocao_below;
    chave_promocao_below.chave = malloc(sizeof(int));
    chave_promocao_below.rrnDados = malloc(sizeof(int));
    *(chave_promocao_below.chave) = -1;
    *(chave_promocao_below.rrnDados) = -1;
    int filho_chave_promocao_below = -1;

    //Tenta inserir na posicao (descendente) onde a chave deveria estar
    int retorno = insercaoRecursiva(arqIndice, Cn, raiz, cabecalho, rrnBusca, &chave_promocao_below, &filho_chave_promocao_below);
    
    if(retorno == SEM_PROMOCAO || retorno == ERRO){
        return retorno;
    }else if(*(pagina->nroChavesNo) <4){ // se tem espaço no nó
        insereChaveOrdenadaNoArvB(pagina, chave_promocao_below, filho_chave_promocao_below);
        escreveNoArqIndice(arqIndice, cabecalho, pagina, *(pagina->RRNdoNo));
        return SEM_PROMOCAO;
    }else{ // se nao tem espaco no nó -> ocorre split
        // Cria novo no
        noArvB * nova_pagina;
        alocaNoArvB(&nova_pagina, 1);
        // Divide as chaves entre os nós e decide qual vai ser promovida
        splitNosArvB(arqIndice, chave_promocao_below, filho_chave_promocao_below, pagina, chave_promocao, filho_chave_promocao, nova_pagina, *(cabecalho->RRNproxNo));

        
        *(cabecalho->RRNproxNo) = *(cabecalho->RRNproxNo) + 1; // incrementa proxRRN

        //Grava nos atualizados no arquivo de indice
        escreveNoArqIndice(arqIndice, cabecalho, pagina, *(pagina->RRNdoNo));

        escreveNoArqIndice(arqIndice, cabecalho, nova_pagina, *(nova_pagina->RRNdoNo));

        return PROMOCAO;      
        
    }


}

int insercaoArvoreB(FILE* arqIndice, int Cn, int PRn, noArvB* raiz, cabecalhoArvB* cabecalho){
    //Cria nova chave
    Chave chave;
    chave.chave = malloc(sizeof(int));
    chave.rrnDados = malloc(sizeof(int));
    *(chave.chave) = Cn;
    *(chave.rrnDados) = PRn;
    
    if(*(cabecalho->noRaiz) == -1){
        //Situacao inicial (nenhum nó nem registro) 
        insereChaveOrdenadaNoArvB(raiz, chave, -1);
        *(raiz->folha) = '1';
        *(raiz->alturaNo) = 1;
        *(raiz->nroChavesNo) = 1;
        *(raiz->RRNdoNo) = 0;
        escreveNoArqIndice(arqIndice, cabecalho, raiz, 0);
        *(cabecalho->noRaiz) = 0;
        *(cabecalho->alturaArvore) = 1;
        *(cabecalho->nroChavesTotal) = 1;
        *(cabecalho->RRNproxNo) = 1;
        return SEM_PROMOCAO;
    }else{
        // Inicializa variaveis da chave promovida
        Chave chave_promo;
        chave_promo.chave = malloc(sizeof(int));
        chave_promo.rrnDados = malloc(sizeof(int));
        *(chave_promo.chave) = -1;
        *(chave_promo.rrnDados) = -1;
        int filho_chave_promo = -1;

        if( insercaoRecursiva(arqIndice, chave, raiz, cabecalho, *(cabecalho->noRaiz), &chave_promo, &filho_chave_promo) == PROMOCAO){
            // Ocorreu split na raiz (necessario criar nova raiz)
            inicializaNoArvB(raiz);
            *(raiz->RRNdoNo)  = *(cabecalho->RRNproxNo);            // nova raiz armazenada em um novo no
            raiz->descendentes[0] = *(cabecalho->noRaiz);           // descendente esquerdo é a raiz antiga
            raiz->descendentes[1] = filho_chave_promo;              // descendente direito é o filho da chave que foi promovida (a nova raiz)
            *(raiz->chaves[0].chave) = *(chave_promo.chave);        // nova raiz é a chave que foi promovida
            *(raiz->chaves[0].rrnDados) = *(chave_promo.rrnDados); 
            *(raiz->nroChavesNo) = 1;
            *(cabecalho->RRNproxNo) = *(cabecalho->RRNproxNo) + 1;  // incrementa o proxRRN pois foi inserido um novo no
            *(cabecalho->noRaiz) = *(raiz->RRNdoNo);                // armazena RRN da nova raiz
            *(raiz->alturaNo) = *(cabecalho->alturaArvore) + 1;     //Altura da raiz um nivel acima (arvore aumentou um nivel)
            *(cabecalho->alturaArvore) = *(cabecalho->alturaArvore) + 1; //Aumenta a altura da arvore
            *(raiz->folha) = '0';                                   // raiz nao é folha pois tem filhos
    
            escreveCabecalhoArqIndice(arqIndice,cabecalho);
            escreveNoArqIndice(arqIndice, cabecalho, raiz, *(raiz->RRNdoNo));
        }
       *(cabecalho->nroChavesTotal) = *(cabecalho->nroChavesTotal) + 1;
    }
}

void imprimeOrdenado(FILE * arq_indice, int rrn){
    noArvB * no_atual = leNoArvB_RRN(arq_indice, rrn);
    for(int i = 0; i<4; i++){
        if(no_atual->descendentes[i] != -1){
            imprimeOrdenado(arq_indice, no_atual->descendentes[i]);
            printf("%d ", *(no_atual->chaves[i].chave));
        }else if(*(no_atual->chaves[i].chave) != -1){
            printf("%d ", *(no_atual->chaves[i].chave));
        }else{
            break;
        }
        
    }

    return PROMOCAO;
}