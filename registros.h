#ifndef __REGISTROS_C__
#define __REGISTROS_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char* firstname;
    char* lastname;
    char* email;
    char* nationality;
    int* age;
}Registro;

void imprimeRegistro(Registro * registro);
void completarCifrao(char ** string, int tamMax);
void lerRegistro(Registro *registro);


#endif