#include "../headers/arquivoBin.h"
<<<<<<< Updated upstream

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
=======
#include<stdlib.h>

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
>>>>>>> Stashed changes
}

