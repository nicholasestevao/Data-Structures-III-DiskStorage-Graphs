#include <stdio.h>
#include "arquivos.h"

int main(void){
    int opcao = 0;
    char nome_arquivo[20]; 
    
    scanf("%d %s", &opcao, nome_arquivo);
    //printf("%d \n%s", opcao, nome_arquivo);

    if(opcao == 1){
        //gravar registro
    }
    if(opcao == 2){
        //recuperar todos os registros
    }
    if(opcao == 3){
        //recuperar registro por RRN
    }
    
    return 0;
}