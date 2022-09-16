#ifndef __REGISTROS_C__
#define __REGISTROS_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRSTNAME_TAM 51
#define LASTNAME_TAM 51
#define EMAIL_TAM 81
#define NATIONALITY_TAM 51

typedef struct {
    char* firstname;
    char* lastname;
    char* email;
    char* nationality;
    int* age;
}Registro;

void alocaRegistros(Registro ** registros, int numReg);
void desalocaRegistros(Registro ** registros, int numReg);
void imprimeRegistro(Registro * registro);
void completarCifrao(char ** string, int tamMax);
void tiraCifrao(char * string, int tamMax);
void lerRegistro(Registro *registro);
int recuperaCampos(FILE * arquivo, Registro * registro);


#endif