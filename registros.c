#include "registros.h"

void imprimeRegistro(Registro * registro){
    printf("%s\n", registro->firstname);
    printf("%s\n", registro->lastname);
    printf("%s\n", registro->email);
    printf("%s\n", registro->nationality);
    printf("%d\n", (registro->age)[0]);
 }   

void completarCifrao(char ** string, int tamMax){    
    int tam = strlen(*string);
    int i;
    for(i = tam; i<tamMax; i++){
        (*string)[i] = '$';
    }
    (*string)[tamMax-1] = '\0';
}

void lerRegistro(Registro *registro){
    char* firstname = malloc(sizeof(char)*100);
    char* lastname = malloc(sizeof(char)*100);    
    char* email = malloc(sizeof(char)*150);
    char* nationality = malloc(sizeof(char)*100);
    int age;
    char* first_e_lastname = malloc(sizeof(char)*200);
    
    printf("Digite o nome: ");
    fgetc(stdin);
    fgets(first_e_lastname, sizeof(char)*200,stdin);
    strcpy(firstname,strtok(first_e_lastname, " "));
    strcpy(lastname, strtok(NULL, "\n"));
    
    printf("Digite o email: ");
    scanf("%s", email);
    getchar();
    printf("Digite a nacionalidade: ");
    scanf("%s", nationality);
    getchar();
    printf("Digite a idade: ");
    scanf("%d", &age);

    completarCifrao(&(firstname), 51);
    completarCifrao(&(lastname), 51);
    completarCifrao(&(email), 81);
    completarCifrao(&(nationality), 51);

    strcpy(registro->firstname, firstname);
    strcpy(registro->lastname, lastname);
    strcpy(registro->email, email);
    strcpy(registro->nationality, nationality);
    (registro->age)[0] = age;

    imprimeRegistro(registro);
}
