#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/funcoesFornecidas.h"
#include "../headers/arquivoBin.h"
#include "../headers/funcionalidades.h"

int main(int argC, char *argV[]){
    int opcao;
    char * nome_arquivo = malloc(sizeof(char)*20);
    
    scanf("%d %s", &opcao, nome_arquivo);
    
    //Create table (1) - Isaac e Nicholas
    //le do csv
    if(opcao == 1) {
        char* nome_arquivo_bin = malloc(sizeof(char)*20);
        scanf("%s", nome_arquivo_bin);
        funcionalidade1CreateTable(nome_arquivo_bin, nome_arquivo);
        free(nome_arquivo_bin);
    }
    
    //Select (2) - Nicholas
    // mostra tudo (so le do binario)
    if(opcao == 2){
        funcionalidade2Select(nome_arquivo);
    }    

    //Select where (3) - Isaac
    //le comando da tela
    if(opcao == 3){
        funcionalidade3SelectWhere(nome_arquivo);
    }

    //Remocao logica (4) - Isaac
    //le comando da tela
    if(opcao == 4){
        funcionalidade4Remove(nome_arquivo);
    }

    //Insercao (5) - Nicholas
    //insere no binario
    //le da tela
    if(opcao == 5){
        int nro_reg;
        scanf("%d", &nro_reg);
        funcionalidade5Insert(nome_arquivo, nro_reg);
    }

    //Compactacao (6) - Nicholas
    //cria outro binario
    if(opcao == 6){
        funcionalidade6Compactacao(nome_arquivo);
    }

    free(nome_arquivo);

    return 0;
}   

