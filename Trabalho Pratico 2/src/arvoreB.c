#include "../headers/arvoreB.h"

//Abre arquivo binario para leitura
//Nao atualiza o status
FILE* abrirLeitura_ArvB(char* nome_arquivo) {
    FILE *arq = fopen(nome_arquivo, "rb");
    if (arq == NULL)
    { //Se o arquivo nao existir existir
        msg_erro_Arq_Inexistente();
        return NULL;
    }
    //Se o arquivo existir
    char *status = malloc(sizeof(char));
    fread(status, sizeof(char), 1, arq);
    if (*status == '0')
    {//Se o arquivo estiver inconsistente
        fclose(arq);
        return NULL;
    }
    else
    { // Voltar para o inicio do arquivo
        fseek(arq, 0, SEEK_SET);
    }
    free(status);
    return arq;
}

//Abre arquivo binario para escrita
//Atualiza o status do arquivo para (1) -> Inconsistente
FILE* abrirEscrita_ArvB(char* nome_arquivo) {
    FILE *arq = fopen(nome_arquivo, "rb+");
    if (arq == NULL)
    {//Se o arquivo nao existir
        arq = fopen(nome_arquivo, "wb+");
    }
    //Se o arquivo existir
    fseek(arq, 0, SEEK_SET);
    char *status = malloc(sizeof(char) * 1);
    *status = '0';
    fwrite(status, sizeof(char), 1, arq);
    free(status);
    return arq;
}

int buscaArvoreB(FILE *arquivoArvB) {

}

//Escreve registro de cabecalho no arquivo da arvore-B.
void escreverCabecalhoArquivoAvrB(FILE* arquivoArvB, cabecalhoArvB* cabecalho) {
    fseek(arquivoArvB, 0, SEEK_SET);
    fwrite(cabecalho->status, sizeof(char), 1, arquivoArvB);
    fwrite(cabecalho->noRaiz, sizeof(int), 1, arquivoArvB);
    fwrite(cabecalho->nroChavesTotal, sizeof(int), 1, arquivoArvB);
    fwrite(cabecalho->alturaArvore, sizeof(int), 1, arquivoArvB);
    fwrite(cabecalho->RRNproxNo, sizeof(int), 1, arquivoArvB);
    char *lixo = malloc(sizeof(char) * TAM_PAGINA_DISCO_ARV_B);
    for (int i = 0; i < TAM_PAGINA_DISCO_ARV_B; i++)
    {
        lixo[i] = '$';
    }
    fwrite(lixo, sizeof(char), TAM_PAGINA_DISCO_ARV_B - TAM_REGISTRO_CABECALHO_ARV_B, arquivoArvB);
    free(lixo);
}

//Escreve noh no arquivo da arvore-B no RRN do noh.
void escreveNoArvB(FILE* arquivoArvB, noArvB* no) {
    int RRN = *(no->RRNdoNo);
    long byteofset = (RRN * TAM_REGISTRO_DADOS_ARV_B) + TAM_PAGINA_DISCO_ARV_B;
    
    fseek(arquivoArvB, byteofset, SEEK_SET);

    fwrite(no->folha, sizeof(char), 1, arquivoArvB);
    fwrite(no->nroChavesNo, sizeof(int), 1, arquivoArvB);
    fwrite(no->alturaNo, sizeof(int), 1, arquivoArvB);
    fwrite(no->RRNdoNo, sizeof(int), 1, arquivoArvB);
    fwrite(no->P1, sizeof(int), 1, arquivoArvB);
    fwrite(no->C1, sizeof(int), 1, arquivoArvB);
    fwrite(no->PR1, sizeof(int), 1, arquivoArvB);
    fwrite(no->P2, sizeof(int), 1, arquivoArvB);
    fwrite(no->C2, sizeof(int), 1, arquivoArvB);
    fwrite(no->PR2, sizeof(int), 1, arquivoArvB);
    fwrite(no->P3, sizeof(int), 1, arquivoArvB);
    fwrite(no->C3, sizeof(int), 1, arquivoArvB);
    fwrite(no->PR3, sizeof(int), 1, arquivoArvB);
    fwrite(no->P4, sizeof(int), 1, arquivoArvB);
    fwrite(no->C4, sizeof(int), 1, arquivoArvB);
    fwrite(no->PR4, sizeof(int), 1, arquivoArvB);
    fwrite(no->P5, sizeof(int), 1, arquivoArvB);
}

//Fecha arquivo binario atualizando status
//Necessario usar essa funcao apenas quando o arquivo foi aberto para escrita
void fecharArquivo_ArvB(FILE* arquivo_ArvB) {
    char *status = malloc(sizeof(char) * 1);
    *status = '1';
    fseek(arquivo_ArvB, 0, SEEK_SET);
    fwrite(status, sizeof(char), 1, arquivo_ArvB);
    fclose(arquivo_ArvB);
    free(status);
}

/*
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
            alocaNoArvB(&novoNo, 1);
            splitNosArvB(resultadoBusca, novoNo);
        }
    }
}*/

//Le registro de cabecalho do arquivo da arvore-B.
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

//Le registro de dados do arquivo da arvore-B por RRN.
noArvB* leNoArvB_RRN(FILE *arquivoArvB, long RRN) {
    noArvB *no;
    alocaNoArvB(&no, 1);

    long byteofset = (RRN * TAM_REGISTRO_DADOS_ARV_B) + TAM_PAGINA_DISCO_ARV_B;

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