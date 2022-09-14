#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "arquivos.h"

void completarCifrao(char * string, int tamMax){
    
    int tam = strlen(string);
    printf("%s : %d\n", string, tam);
    int i;
    for(i = tam; i<tamMax; i++){
        string[i] = '$';
    }
    string[tamMax] = '\0';
    //printf("%s\n", string);
}

int lerRegistro(Registro *registro){
    char firstname[51];
    char lastname[51];
    
    char email[81];
    char nationality[51];
    int age;

    printf("Digite o nome: ");
    scanf("%s", firstname);
    fgetc(stdin);
    fgets(lastname, sizeof(char)*51, stdin);
    //printf("%s\n", firstname);
    lastname[strlen(lastname)-1] = '\0';
    //printf("%s : %d\n", lastname, strlen(lastname));
    printf("Digite o email: ");
    scanf("%s", email);
    getchar();
    printf("Digite a nacionalidade: ");
    scanf("%s", nationality);
    getchar();
    printf("Digite a idade: ");
    scanf("%d", &age);

    strcpy(registro->firstname, firstname);
    strcpy(registro->lastname, lastname);
    strcpy(registro->email, email);
    strcpy(registro->nationality, nationality);
    registro->age = age;

    //completarCifrao(registro->firstname, 51);
    //completarCifrao(registro->lastname, 51);
    //completarCifrao(registro->email, 81);
    //completarCifrao(registro->nationality, 51);


    //printf(" %s\n", registro->firstname);
    //printf(" %s\n", registro->lastname);
    //printf(" %s\n", registro->email);
    //printf(" %s\n", registro->nationality);
    //printf(" %s", registro->age);
    

    return 0;
}

int opcao1(){
    int numReg;
    scanf("%d", &numReg);
    Registro * registros = malloc(sizeof(Registro)*numReg);
    //Lendo registros do teclado
    int i;
    for(i=0; i<numReg; i++){
        printf("Lendo registro %d:\n",i);
        lerRegistro(&(registros[i]));        
    }
    return 0;
}


int main(int argC, char *argV[]){
    int opcao = 0;
    char nome_arquivo[20]; 
    
    scanf("%d %s", &opcao, nome_arquivo);
    //printf("%d \n%s", opcao, nome_arquivo);

    if(opcao == 1){
        //gravar registro
        opcao1();
    }
    if(opcao == 2){
        //recuperar todos os registros
    }
    if(opcao == 3){
        //recuperar registro por RRN
    }
    
    return 0;
}

