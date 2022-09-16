#include "../HEADERS/registros.h"

//aloca memoria para um registro
void alocaRegistros(Registro ** registros, int numReg){
    *registros = malloc(sizeof(Registro)*numReg);   
    for(int i = 0; i<numReg; i++){
        (*registros)[i].firstname = malloc(sizeof(char)*FIRSTNAME_TAM);
        (*registros)[i].lastname = malloc(sizeof(char)*LASTNAME_TAM);
        (*registros)[i].email = malloc(sizeof(char)*EMAIL_TAM);
        (*registros)[i].nationality = malloc(sizeof(char)*NATIONALITY_TAM);
        (*registros)[i].age = malloc(sizeof(int)*1);
    }
}

//desaloca a memoria do dedicada a um registro
void desalocaRegistros(Registro ** registros, int numReg) {
    for(int i = 0; i<numReg; i++){
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

//coloca $(lixo) nos espaços vazios da strings    
void completarCifrao(char ** string, int tamMax){
    //descobre tamanho real da string
    int tam = strlen(*string);
    
    //troca quebras de linha por $
    for(int i = 0; i<tam; i++){
        if((*string)[i] == '\n') {
            (*string)[i] = '$';
        }
    }

    //insere $ no final da string caso não tenha ocupado o tamanho maximo
    for(int i = tam; i<tamMax; i++){
        (*string)[i] = '$';
    }

    //insere \0 no ultimo caractere para indicar fim da string
    (*string)[tamMax-1] = '\0';
}

//tira $(lixo) das strings
void tiraCifrao(char * string, int tamMax) {
    //cria buffer para manipulacao da string
    char * buffer = malloc(sizeof(char) * tamMax);

    //copia a string para o buffer
    strcpy(buffer, string);

    //troca o primeiro $ por \0
    for(int i = 0; i<tamMax; i++){
        if(buffer[i] == '$') {
            buffer[i] = '\0';
        }
    }

    //copia o buffer para string original
    strcpy(string, buffer);
    
    //desaloca buffers
    free(buffer);
}

//recebe dados do usuario e cria um registro
void lerRegistro(Registro *registro){
    //alca buffers
    char* firstname = malloc(sizeof(char)*100);
    char* lastname = malloc(sizeof(char)*100);    
    char* first_e_lastname = malloc(sizeof(char)*200);
    char* email = malloc(sizeof(char)*150);
    char* nationality = malloc(sizeof(char)*100);
    int age;
    
    //recebe nome e sobrenome do usuario
    printf("Digite o nome: ");
    fgetc(stdin);
    fgets(first_e_lastname, sizeof(char)*200, stdin);

    //divide a string em nome e sobrenome
    strcpy(firstname,strtok(first_e_lastname, " "));
    strcpy(lastname, strtok(NULL, "\n"));
    
    //recebe email, nacionalidade e idade do usuario
    printf("Digite o email: ");
    fgets(email, sizeof(char)*150, stdin);
    printf("Digite a nacionalidade: ");
    fgets(nationality, sizeof(char)*100, stdin);
    printf("Digite a idade: ");
    scanf("%d", &age);

    //completa os espaços vazios das strings com $(lixo)
    completarCifrao(&(firstname), 51);
    completarCifrao(&(lastname), 51);
    completarCifrao(&(email), 81);
    completarCifrao(&(nationality), 51);

    //copia os dados pro registro
    strcpy(registro->firstname, firstname);
    strcpy(registro->lastname, lastname);
    strcpy(registro->email, email);
    strcpy(registro->nationality, nationality);
    (registro->age)[0] = age;

    //desaloca buffers
    free(firstname);
    free(lastname);
    free(first_e_lastname);
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

        //tira o $(lixo) das strings
        tiraCifrao(registro->firstname, FIRSTNAME_TAM);
        tiraCifrao(registro->lastname, LASTNAME_TAM);
        tiraCifrao(registro->email, EMAIL_TAM);
        tiraCifrao(registro->nationality, NATIONALITY_TAM);
    } else {
        return 1; //falha
    }
    return 0; //sucesso
}