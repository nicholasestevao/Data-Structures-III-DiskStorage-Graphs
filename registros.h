#ifndef __REGISTROS_C__
#define __REGISTROS_C__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FIRSTNAME_TAM 51
#define LASTNAME_TAM 51
#define EMAIL_TAM 81
#define NATIONALITY_TAM 51

#define LASTNAME_START FIRSTNAME_TAM + 1
#define EMAIL_START LASTNAME_TAM + 1
#define NATIONALITY_START EMAIL_TAM + 1

#define LASTNAME_FINISH FIRSTNAME_TAM + LASTNAME_TAM
#define EMAIL_FINISH LASTNAME_FINISH + EMAIL_TAM
#define NATIONALITY_FINISH EMAIL_FINISH + NATIONALITY_TAM

typedef struct {
    char* firstname;
    char* lastname;
    char* email;
    char* nationality;
    int* age;
}Registro;

void alocaRegistros(Registro * registros, int numReg);
void imprimeRegistro(Registro * registro);
void completarCifrao(char ** string, int tamMax);
void lerRegistro(Registro *registro);
void recuperaCampos(char ** buffer, int buffer_tam, Registro * registro);


#endif