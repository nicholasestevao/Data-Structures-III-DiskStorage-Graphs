#include "registros.h"

void alocaRegistros(Registro * registros, int numReg){
    
}

void imprimeRegistro(Registro * registro){
    printf("Firstname: %s\n", registro->firstname);
    printf("Lastname: %s\n", registro->lastname);
    printf("Email: %s\n", registro->email);
    printf("Nationality: %s\n", registro->nationality);
    printf("Age: %d\n", (registro->age)[0]);
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

void recuperaCampos(char ** buffer, int buffer_tam, Registro * registro) {
    for(int i = 0; i < FIRSTNAME_TAM; i++) {
        printf("%d - %c\n", i, (*buffer)[i]);
        registro->firstname[i] = (*buffer)[i];
    }

    for(int i = LASTNAME_START; i <= LASTNAME_FINISH; i++) {
        registro->firstname[i - LASTNAME_START] = (*buffer)[i];
    }

    for(int i = EMAIL_START; i <= EMAIL_FINISH; i++) {
        registro->firstname[i - EMAIL_START] = (*buffer)[i];
    }

    for(int i = NATIONALITY_START; i <= NATIONALITY_FINISH; i++) {
        registro->firstname[i - NATIONALITY_START] = (*buffer)[i];
    }
}