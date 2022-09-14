#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"
#include "registros.h"

void opcao1(char * nome_arquivo){
    int numReg, i;
    scanf("%d", &numReg);
    Registro * registros = malloc(sizeof(Registro)*numReg);
    for(i = 0; i<numReg; i++){
        registros[i].firstname = malloc(sizeof(char)*51);
        registros[i].lastname = malloc(sizeof(char)*51);
        registros[i].email = malloc(sizeof(char)*81);
        registros[i].nationality = malloc(sizeof(char)*51);
        registros[i].age = malloc(sizeof(int));
    }
    //Lendo registros do teclado
    for(i=0; i<numReg; i++){
        printf("Lendo registro %d:\n",i);
        lerRegistro(&(registros[i]));    
        FILE * arquivo = abrirEscrita_bin(nome_arquivo);
        armazenarRegistro(arquivo, numReg, registros);
        fclose(arquivo);
    }
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
    }
    if(opcao == 3){
        //recuperar registro por RRN
    }
    
    return 0;
}

