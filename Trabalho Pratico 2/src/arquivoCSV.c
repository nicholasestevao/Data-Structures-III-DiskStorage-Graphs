#include "../headers/arquivoCsv.h"

//Abre arquivo .csv para leitura
FILE * abrirLeitura_csv(char * nome_arquivo){
    FILE * arq = fopen(nome_arquivo, "r");
    if(arq != NULL){
        return arq;
    }else{
        return NULL;
    }
}

//Abre arquivo .csv para escrita
FILE * abrirEscrita_csv(char * nome_arquivo){
    return fopen(nome_arquivo, "w");
}