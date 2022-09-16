#include "registros.h"

void alocaRegistros(Registro * registros, int numReg){
    
}

void imprimeRegistro(Registro * registro){
    printf("Firstname: %s\n", registro->firstname);
    printf("Lastname: %s\n", registro->lastname);
    printf("Email: %s\n", registro->email);
    printf("Nationality: %s\n", registro->nationality);
    printf("Age: %d\n\n", (registro->age)[0]);
 }   

void completarCifrao(char ** string, int tamMax){    
    int tam = strlen(*string);
    int i;
    for(i = tam; i<tamMax; i++){
        (*string)[i] = '$';
    }
    (*string)[tamMax-1] = '\0';
}

void tiraCifrao(char ** string, int tamMax) {
    char * buffer = malloc(sizeof(char) * tamMax);
    strcpy(buffer, (*string));
    int i;
    for(i = 0; i<tamMax; i++){
        if(buffer[i] == '$') {
            buffer[i] = '\0';
            break;
        }
    }
    strcpy((*string), buffer);
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

int recuperaCampos(FILE * arquivo, Registro * registro) {
    if(fread(registro->firstname, sizeof(char), FIRSTNAME_TAM, arquivo) != 0) {
        fread(registro->lastname, sizeof(char), LASTNAME_TAM, arquivo);
        fread(registro->email, sizeof(char), EMAIL_TAM, arquivo);
        fread(registro->nationality, sizeof(char), NATIONALITY_TAM, arquivo);
        fread(registro->age, sizeof(int), 1, arquivo);
        tiraCifrao(&(registro->firstname), FIRSTNAME_TAM);
        tiraCifrao(&(registro->lastname), LASTNAME_TAM);
        tiraCifrao(&(registro->email), EMAIL_TAM);
        tiraCifrao(&(registro->nationality), NATIONALITY_TAM);
    } else {
        return 1;
    }
    return 0;
}