#include "arquivos.h"

FILE * abrirLeitura_bin(char * nome_arquivo){
    FILE * arq = fopen(nome_arquivo, "rb");
    if(arq != NULL){
        return arq;
    }else{
        msg_erro_Arq_Inexistente();
    }
}

FILE * abrirEscrita_bin(char * nome_arquivo){
    return fopen(nome_arquivo, "wb");
}

int armazenarRegistro(FILE * arquivo, int numReg, Registro * registros){
    int i;
    for(i = 0; i<numReg; i++){
        fwrite((registros[i]).firstname, sizeof(char), 51, arquivo);
        fwrite((registros[i]).lastname, sizeof(char), 51, arquivo);
        fwrite((registros[i]).email, sizeof(char), 81, arquivo);
        fwrite((registros[i]).nationality, sizeof(char), 51, arquivo);
        fwrite((registros[i]).age, sizeof(int), 1, arquivo);
    }
}

int recuperarArquivo(FILE * arquivo){

}

int recuperarRegistroRRN(FILE * arquivo, int RRN){

}