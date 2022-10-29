#include "../headers/noArvB.h"

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