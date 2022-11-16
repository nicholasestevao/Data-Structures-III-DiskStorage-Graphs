#include "../headers/noArvB.h"

//Aloca memoria para todos os ponteiros do RegistroDados.
void alocaNoArvB(noArvB ** registros, int numReg){
    *registros = malloc(sizeof(noArvB) * numReg);
    for (int i = 0; i < numReg; i++)
    {
        (*registros)[i].folha = malloc(sizeof(char));
        (*registros)[i].nroChavesNo = malloc(sizeof(int));
        (*registros)[i].alturaNo = malloc(sizeof(int));
        (*registros)[i].RRNdoNo = malloc(sizeof(int));
        (*registros)[i].P1 = malloc(sizeof(int));
        (*registros)[i].C1 = malloc(sizeof(int));
        (*registros)[i].PR1 = malloc(sizeof(int));
        (*registros)[i].P2 = malloc(sizeof(int));
        (*registros)[i].C2 = malloc(sizeof(int));
        (*registros)[i].PR2 = malloc(sizeof(int));
        (*registros)[i].P3 = malloc(sizeof(int));
        (*registros)[i].C3 = malloc(sizeof(int));
        (*registros)[i].PR3 = malloc(sizeof(int));
        (*registros)[i].P4 = malloc(sizeof(int));
        (*registros)[i].C4 = malloc(sizeof(int));
        (*registros)[i].PR4 = malloc(sizeof(int));
        (*registros)[i].P5 = malloc(sizeof(int));

        *((*registros)[i].folha) = '0';
        *((*registros)[i].nroChavesNo) = 0;
        *((*registros)[i].alturaNo) = 0;
        *((*registros)[i].RRNdoNo) = 0;
        *((*registros)[i].P1) = -1;
        *((*registros)[i].C1) = -1;
        *((*registros)[i].PR1) = -1;
        *((*registros)[i].P2) = -1;
        *((*registros)[i].C2) = -1;
        *((*registros)[i].PR2) = -1;
        *((*registros)[i].P3) = -1;
        *((*registros)[i].C3) = -1;
        *((*registros)[i].PR3) = -1;
        *((*registros)[i].P4) = -1;
        *((*registros)[i].C4) = -1;
        *((*registros)[i].PR4) = -1;
        *((*registros)[i].P5) = -1;

    }
}

//Desaloca memoria de todos os ponteiros do RegistroDados.
void desalocaNoArvB(noArvB ** registros, int numReg){
    for (int i = 0; i < numReg; i++)
    {
        free((*registros)[i].folha);
        free((*registros)[i].nroChavesNo);
        free((*registros)[i].alturaNo);
        free((*registros)[i].RRNdoNo);
        free((*registros)[i].P1);
        free((*registros)[i].C1);
        free((*registros)[i].PR1);
        free((*registros)[i].P2);
        free((*registros)[i].C2);
        free((*registros)[i].PR2);
        free((*registros)[i].P3);
        free((*registros)[i].C3);
        free((*registros)[i].PR3);
        free((*registros)[i].P4);
        free((*registros)[i].C4);
        free((*registros)[i].PR4);
        free((*registros)[i].P5);
    }
    free(*registros);
}

//Insere uma chave de forma ordenada em um no da arvore-B.
int insereChaveOrdenadaNoArvB(noArvB *no, int Cn, int PRn) {
    if(*(no->nroChavesNo) == 0) {//Se o noh estiver vazio.
    //Insere na primeira chave.
        *(no->C1) = Cn;
        *(no->PR1) = PRn;
    } else {//Noh nao esta vazio.
        if(*(no->C4) > Cn) {
        //Se Cn for menor que C4 insere antes.
            *(no->P5) = *(no->P4);
            *(no->C4) = Cn;
            *(no->PR4) = PRn;

            *(no->P4) = -1;
        }else if (*(no->C3) > Cn) {
        //Se Cn for menor que C3 insere antes.
            *(no->P5) = *(no->P4);
            *(no->C4) = *(no->C3);
            *(no->PR4) = *(no->PR3);

            *(no->P4) = *(no->P3);
            *(no->C3) = Cn;
            *(no->PR3) = PRn;

            *(no->P3) = -1;
        } else if (*(no->C2) > Cn) {
        //Se Cn for menor que C2 insere antes.
            *(no->P5) = *(no->P4);
            *(no->C4) = *(no->C3);
            *(no->PR4) = *(no->PR3);

            *(no->P4) = *(no->P3);
            *(no->C3) = *(no->C2);
            *(no->PR3) = *(no->PR2);

            *(no->P3) = *(no->P2);
            *(no->C2) = Cn;
            *(no->PR2) = PRn;

            *(no->P2) = -1;
        } else if (*(no->C1) > Cn) {
        //Se Cn for menor que C1 insere antes.
            *(no->P5) = *(no->P4);
            *(no->C4) = *(no->C3);
            *(no->PR4) = *(no->PR3);

            *(no->P4) = *(no->P3);
            *(no->C3) = *(no->C2);
            *(no->PR3) = *(no->PR2);
            
            *(no->P3) = *(no->P2);
            *(no->C2) = *(no->C1);
            *(no->PR2) = *(no->PR2);

            *(no->P2) = *(no->P1);
            *(no->C1) = Cn;
            *(no->PR1) = PRn;

            *(no->P1) = -1;
        } else {
        //Se Cn for maior que C4 nao insere.
            return 0;
        }
    }

    //Conseguiu inserir a chave, logo aumenta numero de chaves do noh.
    *(no->nroChavesNo) = *(no->nroChavesNo) + 1;

    return 1;
}