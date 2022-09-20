#include <stdio.h>
#include <stdlib.h>
#include "../headers/arquivos.h"
#include "../headers/registros.h"
#include "../headers/funcoesFornecidas.h"

void opcao1(char * nome_arquivo){
    Registro * registros;
    int numReg;

    //recebe numero de registros
    scanf("%d", &numReg);

    //aloca memoria para a quantidade de registros escolhida
    alocaRegistros(&registros, numReg);
    
    //lendo registros do teclado
    int i;
    for(i=0; i<numReg; i++){
        //printf("Lendo registro %d:\n",i);
        lerRegistro(&(registros[i]));    
    }

    //abre arquivo
    FILE * arquivo = abrirEscrita_bin(nome_arquivo);
    
    //grava registros no arquivo
    armazenarRegistro(arquivo, numReg, registros);
    
    //desaloca registros e fecha arquivo
    desalocaRegistros(&registros, numReg);
    fclose(arquivo);

    binarioNaTela(nome_arquivo);
}

void opcao2(char* nome_arquivo){
    Registro * registros;
    long qntReg;

    //abre arquivo para leitura
    FILE * arquivo = abrirLeitura_bin(nome_arquivo);
    if(arquivo == NULL){
        //Nao conseguiu abrir o arquivo
        return;
    }

    //le todos os registros do arquivo
    if(!recuperarArquivo(arquivo, &registros, &qntReg)){//verifica se conseguiu ler o registro
        //imprime todos os regitros recuperados
        int i;        
        for(i=0; i<qntReg; i++){
            imprimeRegistro(&(registros[i]));    
        }
    }

    //desaloca registros e fecha arquivo
    desalocaRegistros(&registros, qntReg);
    fclose(arquivo);
}

void opcao3(char* nome_arquivo){
    Registro * registro;
    int RRN;

    //abre arquivo para leitura
    FILE * arquivo = abrirLeitura_bin(nome_arquivo);
    if(arquivo == NULL){
        //Nao conseguiu abrir o arquivo
        return;
    }

    //recebe RRN do registro a ser recuperado
    scanf("%d", &RRN); 

    //aloca memoria para a quantidade de registros escolhida
    alocaRegistros(&registro, 1);

    //le registro do arquivo pelo RRN
    if(!recuperarRegistroRRN(arquivo, RRN, registro)){//verifica se conseguiu ler o registro
        //se conseguiu imprime
        imprimeRegistro(registro);
    }

    //desaloca registros e fecha arquivo
    desalocaRegistros(&registro, 1);
    fclose(arquivo);
}

int main(int argC, char *argV[]){
    int opcao = 0;

    //aloca string de nome do arquivo
    char* nome_arquivo = malloc(sizeof(char)*20); 

    //recebe a opcao e o nome do arquivo
    scanf("%d %s", &opcao, nome_arquivo);

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
    
    //desaloca string de nome do arquivo
    free(nome_arquivo);
    
    return 0;
}

