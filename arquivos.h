#ifndef __ARQUIVOS_C__
#define __ARQUIVOS_C__

#include <stdlib.h>
#include "mensagens.h"

typedef struct {
    char firstname[51];
    char lastname[51];
    char email[81];
    char nationality[51];
    int age;
}Registro;

FILE * abrirLeitura_bin(char * nome_arquivo);
FILE * abrirEscrita_bin(char * nome_arquivo);

int armazenarRegistros(FILE * arquivo, int numReg, Registro * registros);
int tratarRegistro(Registro * registro);
int recuperarArquivo(FILE * arquivo);
int recuperarRegistroRRN(FILE * arquivo, int RRN);

#endif