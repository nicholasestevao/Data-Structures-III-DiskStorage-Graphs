#include "../headers/noArvB.h"

// inicializa no
void inicializaNoArvB(noArvB *no)
{
    for (int j = 0; j < 4; j++)
    {
        (no->chaves[j].chave) = -1;
        (no->chaves[j].rrnDados) = -1;
    }
    for (int j = 0; j < 5; j++)
    {
        no->descendentes[j] = -1;
    }

    *(no->folha) = '1';
    *(no->nroChavesNo) = 0;
    *(no->alturaNo) = 1;
    *(no->RRNdoNo) = 0;
}

// Aloca memoria para todos os ponteiros do RegistroDados.
void alocaNoArvB(noArvB **registros, int numReg)
{
    *registros = malloc(sizeof(noArvB) * numReg);
    for (int i = 0; i < numReg; i++)
    {
        (*registros)[i].folha = malloc(sizeof(char));
        (*registros)[i].nroChavesNo = malloc(sizeof(int));
        (*registros)[i].alturaNo = malloc(sizeof(int));
        (*registros)[i].RRNdoNo = malloc(sizeof(int));
        (*registros)[i].chaves = malloc(sizeof(Chave) * 4);
        (*registros)[i].descendentes = malloc(sizeof(int) * 5);
        inicializaNoArvB(registros[i]);
    }
}

// Desaloca memoria de todos os ponteiros do RegistroDados.
void desalocaNoArvB(noArvB **registros, int numReg)
{
    for (int i = 0; i < numReg; i++)
    {
        free((*registros)[i].folha);
        free((*registros)[i].nroChavesNo);
        free((*registros)[i].alturaNo);
        free((*registros)[i].RRNdoNo);
        free((*registros)[i].chaves);
        free((*registros)[i].descendentes);
    }
    free(*registros);
}

// Insere uma chave de forma ordenada em um no da arvore-B.
// Assume que tem espaço
void insereChaveOrdenadaNoArvB(noArvB *no, Chave Cn, int filho)
{
    int i = 0;
    // Encontra posicao onde a chave deve ser inserida
    while (i < *(no->nroChavesNo) && ((no->chaves[i]).chave) <= (Cn.chave))
    {
        if (((no->chaves[i]).chave) == Cn.chave)
        {
            return;
        }
        i++;
    }

    // Desloca as chaves maiores do que a que será inserida para a direita
    for (int j = 3; j > i; j--)
    {
        (no->chaves[j].chave) = (no->chaves[j - 1].chave);
        (no->chaves[j].rrnDados) = (no->chaves[j - 1].rrnDados);
    }
    // Desloca os descendentes das chaves maiores do que a que será inserida para a direita
    for (int j = 4; j > i; j--)
    {
        (no->descendentes[j]) = (no->descendentes[j - 1]);
    }
    // Insere nova chave na posicao correta
    ((no->chaves[i]).chave) = (Cn.chave);
    ((no->chaves[i]).rrnDados) = (Cn.rrnDados);
    no->descendentes[i + 1] = filho;

    // Incrementa contagem de chaves
    *(no->nroChavesNo) += 1;
}

void imprimeNoTela(noArvB *no)
{
    printf("RRN do no: %d\n", *(no->RRNdoNo));
    printf("Opupacao: %d\n", *(no->nroChavesNo));
    printf("Altura: %d\n", *(no->alturaNo));
    printf("Folha: %c\n", *(no->folha));
    printf("%d %d %d\n", (no->descendentes[0]), (no->chaves[0].chave), (no->chaves[0].rrnDados));
    printf("%d %d %d\n", (no->descendentes[1]), (no->chaves[1].chave), (no->chaves[1].rrnDados));
    printf("%d %d %d\n", (no->descendentes[2]), (no->chaves[2].chave), (no->chaves[2].rrnDados));
    printf("%d %d %d %d\n", (no->descendentes[3]), (no->chaves[3].chave), (no->chaves[3].rrnDados), (no->descendentes[4]));
}