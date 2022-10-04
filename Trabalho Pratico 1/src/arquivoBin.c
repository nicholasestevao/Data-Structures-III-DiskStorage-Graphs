#include "../headers/arquivoBin.h"

//abre arquivo binario para leitura
FILE * abrirLeitura_bin(char * nome_arquivo){
    FILE * arq = fopen(nome_arquivo, "rb");
    if(arq != NULL){
        return arq;
    }else{
        msg_erro_Arq_Inexistente();
        return NULL;
    }
}

//abre arquivo binario para escrita
FILE * abrirEscrita_bin(char * nome_arquivo){
    return fopen(nome_arquivo, "wb");
}

int createTable(FILE* arquivobin, FILE* arquivocsv) {
    if(arquivobin == NULL || arquivocsv == NULL) {
        return 1;
    }

    RegistroCabecalho *rCabecalho;
    RegistroDados *rDados;

    alocaRegistrosCabecalho(rCabecalho);
    alocaRegistrosDados(rDados, 1);

    char *buf = malloc(sizeof(char)*255);
    fgets(buf, 255, arquivocsv);
    free(buf);

    while(!feof(arquivocsv)) {
        fscanf(arquivocsv, "%c,%s,%s,%c%c,%d,%c,%d", rDados->idConecta, rDados->nomePoPs, rDados->nomePais, rDados->siglaPais[0], rDados->siglaPais[1], rDados->)
    }

}