#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"
#include "registros.h"

void opcao1(char * nome_arquivo){
    int numReg;

    scanf("%d", &numReg);
    //aloca memoria para a quantidade de registros escolhida
    Registro * registros = malloc(sizeof(Registro)*numReg);
    for(int i = 0; i<numReg; i++){
        registros[i].firstname = malloc(sizeof(char)*FIRSTNAME_TAM);
        registros[i].lastname = malloc(sizeof(char)*LASTNAME_TAM);
        registros[i].email = malloc(sizeof(char)*EMAIL_TAM);
        registros[i].nationality = malloc(sizeof(char)*NATIONALITY_TAM);
        registros[i].age = malloc(sizeof(int)*1);
    }

    //Lendo registros do teclado
    for(int i=0; i<numReg; i++){
        printf("Lendo registro %d:\n",i);
        lerRegistro(&(registros[i]));    
    }

    FILE * arquivo = abrirEscrita_bin(nome_arquivo);
    armazenarRegistro(arquivo, numReg, registros);
    fclose(arquivo);
}

void opcao2(char* nome_arquivo){
    FILE * arquivo = abrirLeitura_bin(nome_arquivo);
    
}

void opcao3(char* nome_arquivo){
    int RRN;
    scanf("%d", &RRN); 
    FILE * arquivo = abrirLeitura_bin(nome_arquivo);
    //aloca memoria para a quantidade de registros escolhida
    Registro * registro = malloc(sizeof(Registro)*1);
    registro->firstname = malloc(sizeof(char)*FIRSTNAME_TAM);
    registro->lastname = malloc(sizeof(char)*LASTNAME_TAM);
    registro->email = malloc(sizeof(char)*EMAIL_TAM);
    registro->nationality = malloc(sizeof(char)*NATIONALITY_TAM);
    registro->age = malloc(sizeof(int)*1);

    recuperarRegistroRRN(arquivo, RRN, registro);
    imprimeRegistro(registro);
}

int main(int argC, char *argV[]){
    int opcao = 0;
    char* nome_arquivo = malloc(sizeof(char)*20); 
    
    scanf("%d %s", &opcao, nome_arquivo);
    //printf("%d \n%s", opcao, nome_arquivo);

    if(opcao == 1){
        //gravar registro
        opcao1(nome_arquivo);
    }
    if(opcao == 2){
        //recuperar todos os registros
        opcao2(nome_arquivo);
    }
    if(opcao == 3){
        //recuperar registro por RRN
        opcao3(nome_arquivo);
    }
    
    return 0;
}

