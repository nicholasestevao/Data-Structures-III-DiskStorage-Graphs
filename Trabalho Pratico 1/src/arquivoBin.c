#include "../headers/arquivoBin.h"
#include <stdlib.h>

FILE * abrirLeitura_bin(char * nome_arquivo){
    FILE *arq = fopen(nome_arquivo, "rb");
    if(arq == NULL){
        msg_erro_Arq_Inexistente();
        return NULL;
    }else{
        return arq;
    }
}
FILE * abrirEscrita_bin(char * nome_arquivo){
    FILE *arq = fopen(nome_arquivo, "wb");
        return arq;
}

RegistroDados * lerRegistroDadosArquivoBin_RRN(FILE * arquivoBin,int RRN){
    int byteoffset = 960 + 64*RRN;
    fseek(arquivoBin, byteoffset, SEEK_SET);
    char* removido;
    fread(removido, sizeof(char), 1, arquivoBin);
    RegistroDados * registro;
    if(removido == '0'){
        alocaRegistrosDados(&registro, 1);
        registro->removido = removido;
        fread(registro->encadeamento, sizeof(int), 1, arquivoBin);
        fread(registro->idConecta, sizeof(int), 1, arquivoBin);
        fread(registro->siglaPais, sizeof(char), 2, arquivoBin);
        fread(registro->idPoPsConectado, sizeof(int), 1, arquivoBin);
        fread(registro->unidadeMedida, sizeof(char), 1, arquivoBin);
        fread(registro->velocidade, sizeof(int), 1, arquivoBin);
        int indice = 0;
        char c = fgetc(arquivoBin);
        while(c != '|'){
            registro->nomePoPs[indice] = c;
            c = fgetc(arquivoBin);
            indice++;
        }
        registro->nomePoPs[indice] = '\0';
        indice = 0;
        char c = fgetc(arquivoBin);
        while(c != '|'){
            registro->nomePais[indice] = c;
            c = fgetc(arquivoBin);
            indice++;
        }
        registro->nomePoPs[indice] = '\0';
        
        
    }else{
        //registro removido
    }
}

RegistroCabecalho * lerRegistroCabecalhoArquivoBin(FILE * arquivoBin){
    RegistroCabecalho* registro;
    alocaRegistrosCabecalho(registro);
    fseek(arquivoBin, 0, SEEK_SET);
    fread(registro->status, sizeof(char), 1, arquivoBin);
    fread(registro->topo, sizeof(int), 1, arquivoBin);
    fread(registro->proxRRN, sizeof(int), 1, arquivoBin);
    fread(registro->nroRegRem, sizeof(int), 1, arquivoBin);
    fread(registro->nroPagDisco, sizeof(int), 1, arquivoBin);
    fread(registro->qttCompacta, sizeof(int), 1, arquivoBin);
}

void funcionalidade2Select(char* nome_arquivo){
    FILE * arquivoBin = abrirLeitura_bin(nome_arquivo);
    RegistroCabecalho * cabecalho = lerRegistroCabecalhoArquivoBin(arquivoBin);
    RegistroDados * dados;
    for(int i = 0; i<cabecalho->proxRRN; i++){
        dados = lerRegistroDadosArquivoBin_RRN(arquivoBin,i);
        imprimeRegistroDadosTela(dados);
        desalocaRegistrosDados(&dados,1);
    }
    printf("Numero de paginas de disco: %d\n", cabecalho->nroPagDisco);
    desalocaRegistrosCabecalho(cabecalho);
    fclose(arquivoBin);
}