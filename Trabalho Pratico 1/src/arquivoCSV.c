#include "../headers/arquivoCSV.h"

//abre arquivo binario para leitura
FILE * abrirLeitura_csv(char * nome_arquivo){
    FILE * arq = fopen(nome_arquivo, "r");
    if(arq != NULL){
        return arq;
    }else{
        msg_erro_Arq_Inexistente();
        return NULL;
    }
}

//abre arquivo binario para escrita
FILE * abrirEscrita_csv(char * nome_arquivo){
    return fopen(nome_arquivo, "w");
}