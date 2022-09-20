#ifndef __REGISTROS_C__
#define __REGISTROS_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRSTNAME_TAM 51
#define LASTNAME_TAM 51
#define EMAIL_TAM 81
#define NATIONALITY_TAM 51

#if (FIRSTNAME_TAM >= LASTNAME_TAM) && (FIRSTNAME_TAM >= EMAIL_TAM) && (FIRSTNAME_TAM >= NATIONALITY_TAM)
    #define CIFRAOSTRING FIRSTNAME_TAM
#elif (LASTNAME_TAM >= FIRSTNAME_TAM) && (LASTNAME_TAM >= EMAIL_TAM) && (LASTNAME_TAM >= NATIONALITY_TAM)
    #define CIFRAOSTRING LASTNAME_TAM
#elif (EMAIL_TAM >= FIRSTNAME_TAM) && (EMAIL_TAM >= LASTNAME_TAM) && (EMAIL_TAM >= NATIONALITY_TAM)
    #define CIFRAOSTRING EMAIL_TAM
#elif (NATIONALITY_TAM >= FIRSTNAME_TAM) && (NATIONALITY_TAM >= LASTNAME_TAM) && (NATIONALITY_TAM >= EMAIL_TAM)
    #define CIFRAOSTRING NATIONALITY_TAM 
#endif

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
void lerRegistro(Registro *registro);
int recuperaCampos(FILE * arquivo, Registro * registro);

#endif