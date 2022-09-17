#include "../HEADERS/registros.h"

//aloca memoria para um registro
void alocaRegistros(Registro ** registros, int numReg){
    *registros = malloc(sizeof(Registro)*numReg);   
    int i;
    for(i = 0; i<numReg; i++){
        (*registros)[i].firstname = malloc(sizeof(char)*FIRSTNAME_TAM);
        (*registros)[i].lastname = malloc(sizeof(char)*LASTNAME_TAM);
        (*registros)[i].email = malloc(sizeof(char)*EMAIL_TAM);
        (*registros)[i].nationality = malloc(sizeof(char)*NATIONALITY_TAM);
        (*registros)[i].age = malloc(sizeof(int)*1);
    }
}

//desaloca a memoria do dedicada a um registro
void desalocaRegistros(Registro ** registros, int numReg) {
    int i;
    for(i = 0; i<numReg; i++){
        free((*registros)[i].firstname);
        free((*registros)[i].lastname);
        free((*registros)[i].email);
        free((*registros)[i].nationality);
        free((*registros)[i].age);
    }
    free((*registros));
}

//imprime na tela cada campo do Registro
void imprimeRegistro(Registro * registro){ 
    printf("Firstname: %s\n", registro->firstname);
    printf("Lastname: %s\n", registro->lastname);
    printf("Email: %s\n", registro->email);
    printf("Nationality: %s\n", registro->nationality);
    printf("Age: %d\n\n", (registro->age)[0]);
 }   

//recebe dados do usuario e cria um registro
void lerRegistro(Registro *registro){
    //alca buffers
    char* firstname = malloc(sizeof(char)*100);
    char* lastname = malloc(sizeof(char)*100);    
    char* email = malloc(sizeof(char)*150);
    char* nationality = malloc(sizeof(char)*100);
    int age;
    
    //recebe nome e sobrenome do usuario
    //printf("Digite o nome: ");
    fgetc(stdin);
    fgets(firstname, sizeof(char)*100, stdin);
    //printf("Digite o sobrenome: ");
    fgets(lastname, sizeof(char)*100, stdin);
    //recebe email, nacionalidade e idade do usuario
    //printf("Digite o email: ");
    fgets(email, sizeof(char)*150, stdin);
    //printf("Digite a nacionalidade: ");
    fgets(nationality, sizeof(char)*100, stdin);
    //printf("Digite a idade: ");
    scanf("%d", &age);


    //copia os dados pro registro
    strcpy(registro->firstname, strtok(firstname,"\n"));
    strcpy(registro->lastname, strtok(lastname,"\n"));
    strcpy(registro->email, strtok(email,"\n"));
    strcpy(registro->nationality, strtok(nationality,"\n"));
    (registro->age)[0] = age;

    //desaloca buffers
    free(firstname);
    free(lastname);
    free(email);
    free(nationality);
}

//recupera um registro de um arquivo binario
int recuperaCampos(FILE * arquivo, Registro * registro){
    //lê campos do arquivo e coloca no registro
    if(fread(registro->firstname, sizeof(char), FIRSTNAME_TAM, arquivo)){ //Se o arquivo não tiver chego no final
        fread(registro->lastname, sizeof(char), LASTNAME_TAM, arquivo);
        fread(registro->email, sizeof(char), EMAIL_TAM, arquivo);
        fread(registro->nationality, sizeof(char), NATIONALITY_TAM, arquivo);
        fread(registro->age, sizeof(int), 1, arquivo);
    } else {
        return 1; //falha
    }
    return 0; //sucesso
}