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
    return 0;
}

int recuperarArquivo(FILE * arquivo, Registro ** registros, long qntReg){
    if(*registros == NULL) {
        //aloca regisros
        alocaRegistros(&(*registros), qntReg);
    }

    for(int i=0; i < qntReg; i++){
       if(recuperaCampos(arquivo, &(*registros)[i])) {
            msg_erro_RRN_Invalido();
            return 1;
       } 
    }
    return 0;
}

int recuperarRegistroRRN(FILE * arquivo, int RRN, Registro * registro){
    if(registro == NULL) {
        //aloca regisros
        alocaRegistros(&registro, 1);
    }

    fseek(arquivo, (234 * sizeof(char) + sizeof(int)) * RRN, SEEK_SET);
    
    if(recuperaCampos(arquivo, registro)) {
        msg_erro_RRN_Invalido();
        return 1;
    }
    return 0;
}