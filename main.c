#include <stdio.h>
#include <stdlib.h>
#include "arquivos.h"
#include "registros.h"

void opcao1(char * nome_arquivo){
    Registro * registros;
    int numReg;

    scanf("%d", &numReg);
    //aloca memoria para a quantidade de registros escolhida
    alocaRegistros(&registros, numReg);
    
    //Lendo registros do teclado
    for(int i=0; i<numReg; i++){
        printf("Lendo registro %d:\n",i);
        lerRegistro(&(registros[i]));    
    }

    FILE * arquivo = abrirEscrita_bin(nome_arquivo);
    armazenarRegistro(arquivo, numReg, registros);
    
    //desaloca registros e fecha arquivo
    desalocaRegistros(&registros, numReg);
    fclose(arquivo);
}

void opcao2(char* nome_arquivo){
    Registro * registros;
    long qntReg;
    //abre arquivo
    FILE * arquivo = abrirLeitura_bin(nome_arquivo);

    //Descobre quantidade de registros a serem lidos
    fseek(arquivo, 0, SEEK_END);
    qntReg = ftell(arquivo) / 238;
    fseek(arquivo, 0, SEEK_SET);

    //aloca quantidade de registros
    alocaRegistros(&registros, qntReg);

    //le todos os registros do arquivo
    if(!recuperarArquivo(arquivo, &registros, qntReg)){//verifica se conseguiu ler o registro
        imprimeRegistro(registros);
    }

    //desaloca registros e fecha arquivo
    desalocaRegistros(&registros, qntReg);
    fclose(arquivo);
}

void opcao3(char* nome_arquivo){
    Registro * registro;
    int RRN;
    scanf("%d", &RRN); 
    FILE * arquivo = abrirLeitura_bin(nome_arquivo);
    //aloca memoria para a quantidade de registros escolhida
    alocaRegistros(&registro, 1);

    //le registro do arquivo pelo RRN
    if(!recuperarRegistroRRN(arquivo, RRN, registro)){//verifica se conseguiu ler o registro
        imprimeRegistro(registro);
    }

    //desaloca registros e fecha arquivo
    desalocaRegistros(&registro, 1);
    fclose(arquivo);
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

