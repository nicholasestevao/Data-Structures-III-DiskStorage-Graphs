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

int recuperarArquivo(FILE * arquivo, Registro * registros){
    if(registros == NULL) {
        //aloca regisros
        registros = malloc(sizeof(Registro)*1);
        registros->firstname = malloc(sizeof(char)*FIRSTNAME_TAM);
        registros->lastname = malloc(sizeof(char)*LASTNAME_TAM);
        registros->email = malloc(sizeof(char)*EMAIL_TAM);
        registros->nationality = malloc(sizeof(char)*NATIONALITY_TAM);
        registros->age = malloc(sizeof(int));
    }

    char * char_buffer = malloc(sizeof(char)*234);
    int * int_buffer = malloc(sizeof(int)*1);

    if(fread(char_buffer, sizeof(char), 234, arquivo)) {
        fread(int_buffer, sizeof(int), 1, arquivo);
        recuperaCampos(&(char_buffer), 234, registros);
        registros->age = int_buffer;
    }

    int i = 2;
    while(fread(char_buffer, sizeof(char), 234, arquivo)) {
        fread(int_buffer, sizeof(int), 1, arquivo);
        //realloc(registros, sizeof(registros) * i);
    }
    return 0;
}

int recuperarRegistroRRN(FILE * arquivo, int RRN, Registro * registro){
    if(registro == NULL) {
        //aloca regisros
        registro = malloc(sizeof(Registro)*1);
        registro->firstname = malloc(sizeof(char)*FIRSTNAME_TAM);
        registro->lastname = malloc(sizeof(char)*LASTNAME_TAM);
        registro->email = malloc(sizeof(char)*EMAIL_TAM);
        registro->nationality = malloc(sizeof(char)*NATIONALITY_TAM);
        registro->age = malloc(sizeof(int));
    }

    char * char_buffer = malloc(sizeof(char)*234);
    int * int_buffer = malloc(sizeof(int)*1);

    fseek(arquivo, (234 * sizeof(char) + sizeof(int)) * RRN, SEEK_SET);
    if(fread(registro->firstname, sizeof(char), FIRSTNAME_TAM, arquivo)) {
        fread(registro->lastname, sizeof(char), LASTNAME_TAM, arquivo);
        fread(registro->email, sizeof(char), EMAIL_TAM, arquivo);
        fread(registro->nationality, sizeof(char), NATIONALITY_TAM, arquivo);
        fread(int_buffer, sizeof(int), 1, arquivo);
        registro->age = int_buffer;
    }
    return 0;
}