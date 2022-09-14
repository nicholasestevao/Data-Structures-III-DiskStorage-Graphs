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
    
}

int recuperarArquivo(FILE * arquivo){

}

int recuperarRegistroRRN(FILE * arquivo, int RRN){

}