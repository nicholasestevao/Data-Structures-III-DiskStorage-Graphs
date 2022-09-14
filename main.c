#include <stdio.h>

int main(void){
    int opcao;
    char nome_arquivo[20]; 
    scanf("%d %s", &opcao, nome_arquivo);
   // scanf("%s", nome_arquivo);
    printf("%d \n%s", opcao, nome_arquivo);

}