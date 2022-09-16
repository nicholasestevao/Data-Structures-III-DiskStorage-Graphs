#include "../HEADERS/arquivos.h"

//abre arquivo binario para leitura
FILE * abrirLeitura_bin(char * nome_arquivo){
    FILE * arq = fopen(nome_arquivo, "rb");
    if(arq != NULL){
        return arq;
    }else{
        msg_erro_Arq_Inexistente();
    }
}

//abre arquivo binario para escrita
FILE * abrirEscrita_bin(char * nome_arquivo){
    return fopen(nome_arquivo, "wb");
}

//escreve todos os registros no arquivobinario
int armazenarRegistro(FILE * arquivo, int numReg, Registro * registros){
    //escreve cada registro sequencialmente no arquivo binario
    for(int i = 0; i<numReg; i++){
        fwrite((registros[i]).firstname, sizeof(char), 51, arquivo);
        fwrite((registros[i]).lastname, sizeof(char), 51, arquivo);
        fwrite((registros[i]).email, sizeof(char), 81, arquivo);
        fwrite((registros[i]).nationality, sizeof(char), 51, arquivo);
        fwrite((registros[i]).age, sizeof(int), 1, arquivo);
    }

    return 0;//sucesso
}

//recupera todos os registros no arquivo binario
int recuperarArquivo(FILE * arquivo, Registro ** registros, long qntReg){
    //Descobre quantidade de registros a serem lidos
    fseek(arquivo, 0, SEEK_END);
    qntReg = ftell(arquivo) / 238;
    fseek(arquivo, 0, SEEK_SET);

    //aloca quantidade de registros
    alocaRegistros(&(*registros), qntReg);
    
    //recupera cada registro do arquivo binario
    for(int i = 0; i < qntReg; i++){
        if(recuperaCampos(arquivo, &((*registros)[i]))) {
            msg_erro_RRN_Invalido();
            return 1; //falha
        } 
    }
    return 0;//sucesso
}

//recupera um registro especifico por RRN
int recuperarRegistroRRN(FILE * arquivo, int RRN, Registro * registro){
    //se o registro nao estiver alocado aloca o registro
    if(registro == NULL) {
        //aloca regisros
        alocaRegistros(&registro, 1);
    }

    //posiciona o ponteriro no registro desejado
    fseek(arquivo, (234 * sizeof(char) + sizeof(int)) * RRN, SEEK_SET);
    
    //se o RRN for invalido printa a mensagem de erro e retorna 1
    if(recuperaCampos(arquivo, registro)) {
        msg_erro_RRN_Invalido();
        return 1;//falha
    }

    return 0;//sucesso
}