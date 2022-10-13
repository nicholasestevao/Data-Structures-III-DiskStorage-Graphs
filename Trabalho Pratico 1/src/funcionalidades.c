#include "../headers/funcionalidades.h"

void cortaDados(char *buf, char *dado) {
    //garante dado vazio
    for(int i = 0; i < sizeof(dado); i++) {
        dado[i] = '\0';
    }

    //verifica se o buffer recebido esta vazio
    if(buf == NULL) {
        return; //encerra a funcao
    }

    //cria buffer para copia do restante do buffer
    char buf_res[100];
    //garate que buf_res vaizo
    for(int i = 0; i < 100; i++) {
        buf_res[i] = '\0';
    }
    
    int i = 0;
    while((buf[i] != '\0') && (buf[i] != ',')) { //enquanto caractere atual do buffer for diferente de ,    
        dado[i] = buf[i];
        i++;
    }
    dado[i] = '\0';
    i++;

    int j = 0;
    while (buf[i+j] != '\0') {
       buf_res[j] = buf[i+j];
       j++;
    }
    buf_res[j] = '\0';
    strcpy(buf, buf_res);

    while(j < 100) { //enquanto caractere atual do buffer for diferente de ,    
        buf[j] = '\0';
        j++;
    }
}

void copiaInt(int *dest, char *src) {
    if((src != NULL) && (src[0] != '\0')) {
        *dest = atoi(src);
    } else {
        *dest = -1;
    }
}

void copiaStrFix(char *dest, char *src) {
    if(src[0] == '\0'){
        dest[0] = '\0';
    }else if((src != NULL) && (src[0] != '\0')) {
        strcpy(dest, src);
    }
    
}

void copiaStrVar(char *dest, char *src) {
    if((src != NULL) && (src[0] != '\0')) {
        strcpy(dest, src);
    } else {
        dest[0] = '\0';
    }
}

void pegaDados(char *buf, RegistroDados *dados) {
    char dado[50];
    cortaDados(buf, dado);
    if((dado != NULL) && (dado[0] == '*')) {
            *(dados->removido) = '1';
            return;
    } else {
        *(dados->removido) = '0';
        *(dados->encadeamento) = -1;
        copiaInt((dados->idConecta), dado);
        
        cortaDados(buf, dado);
        copiaStrVar((dados->nomePoPs), dado);
        
        cortaDados(buf, dado);
        copiaStrVar((dados->nomePais), dado);

        cortaDados(buf, dado);
        copiaStrFix((dados->siglaPais), dado);
        cortaDados(buf, dado);
        copiaInt((dados->idPoPsConectado), dado);

        cortaDados(buf, dado);
        copiaStrFix((dados->unidadeMedida), dado);
        cortaDados(buf, dado);
        copiaInt((dados->velocidade), dado);
    }
}

void funcionalidade1CreateTable(char* nome_arquivo_bin, char* nome_arquivo_csv) {
    FILE *arquivoBin = abrirEscrita_bin(nome_arquivo_bin);
    FILE *arquivoCSV = abrirLeitura_csv(nome_arquivo_csv);
    RegistroCabecalho *cabecalho;
    alocaRegistrosCabecalho(&cabecalho);
    RegistroDados *dados;
    alocaRegistrosDados(&dados, 1);

    char *buf = malloc(sizeof(char) * 100);
    
    fgets(buf, 100, arquivoCSV);
    for (int i = 0; i < 100; i++) {
        buf[i] = '\0';
    }
    
    while (fgets(buf, 100, arquivoCSV) != NULL) {
        int i = strlen(buf);
        buf[i-1] = '\0';
        //printf("buf: %s\n", buf);
        pegaDados(buf, dados);
        //imprimeRegistroDadosTela(dados);
        inserirRegistroDadosArquivoBin(arquivoBin, cabecalho, dados);
        //printf("Topo: %d\n", *(cabecalho->topo));
    }
    
    escreverRegistroCabecalhoArquivoBin(arquivoBin, cabecalho);
    
    desalocaRegistrosCabecalho(cabecalho);
    desalocaRegistrosDados(&dados, 1);
    fecharArquivo_bin(arquivoBin);
    fclose(arquivoCSV);
    free(buf);
    binarioNaTela(nome_arquivo_bin);
}

void funcionalidade2Select(char* nome_arquivo){
    FILE * arquivoBin = abrirLeitura_bin(nome_arquivo);
    RegistroCabecalho *cabecalho = lerRegistroCabecalhoArquivoBin(arquivoBin);
    RegistroDados * dados;
    for(int i = 0; i<*(cabecalho->proxRRN); i++){
        dados = lerRegistroDadosArquivoBin_RRN(arquivoBin,i);
        if(dados !=  NULL){
            imprimeRegistroDadosTela(dados);
            printf("\n");
            desalocaRegistrosDados(&dados,1);
        }
        
    }
    printf("Numero de paginas de disco: %d\n", *(cabecalho->nroPagDisco));
    desalocaRegistrosCabecalho(cabecalho);
    fecharArquivo_bin(arquivoBin);
}

void funcionalidade5Insert(char* nome_arquivo, int nro_reg){
    RegistroDados *registro;
    alocaRegistrosDados(&registro, 1);

    FILE * arquivo = abrirEscrita_bin(nome_arquivo);
    
    RegistroCabecalho * cabecalho =  lerRegistroCabecalhoArquivoBin(arquivo);
    for(int i = 0; i<nro_reg; i++){
        lerRegistroDadosTeclado(registro);
        //imprimeRegistroDadosTela(registro);
        //imprimeRegistroCabecalhoTela(cabecalho);
        inserirRegistroDadosArquivoBin(arquivo,cabecalho, registro);
    }
    
    escreverRegistroCabecalhoArquivoBin(arquivo, cabecalho);
    binarioNaTela(nome_arquivo);
    fecharArquivo_bin(arquivo);
    desalocaRegistrosDados(&registro, 1);
}

void funcionalidade6Compactacao(char* nome_arquivo){
    RegistroCabecalho *cabecalhoNovo;
    alocaRegistrosCabecalho(&cabecalhoNovo);
    FILE *arq_compactado = fopen("compactado.bin", "wb+");

    FILE * arq_original = abrirLeitura_bin(nome_arquivo);
    RegistroCabecalho *cabecalhoAntigo = lerRegistroCabecalhoArquivoBin(arq_original);

    for(int i=0; i<*(cabecalhoAntigo->proxRRN); i++){
        RegistroDados * dados = lerRegistroDadosArquivoBin_RRN(arq_original, i);
        if(dados == NULL){
            //Registro removido
            //printf("registro removido\n");
        }else{
            inserirRegistroDadosArquivoBin(arq_compactado, cabecalhoNovo, dados);
            desalocaRegistrosDados(&dados, 1);
        }        
    }
    *(cabecalhoNovo->qttCompacta) = *(cabecalhoAntigo->qttCompacta) + 1;
    escreverRegistroCabecalhoArquivoBin(arq_compactado, cabecalhoNovo);
    desalocaRegistrosCabecalho(cabecalhoNovo);
    desalocaRegistrosCabecalho(cabecalhoAntigo);

    binarioNaTela(nome_arquivo);
    fecharArquivo_bin(arq_compactado);
    fecharArquivo_bin(arq_original);

    remove(nome_arquivo);
    rename("compactado.bin", nome_arquivo);
    

}