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
void insereChaveOrdenadaNoArvB(noArvB *no, int Cn, int PRn){
    printf("inserindo ordenado na pagina\n");
    *(no->folha) = 0;
    *(no->nroChavesNo) +=1;
    if(Cn <= *(no->C1) || *(no->C1)==-1){
        printf("menor chave\n");
        if(Cn == *(no->C1)){
            return; //encontrada
        }
        *(no->P5) = *(no->P4);
        *(no->P4) = *(no->P3);
        *(no->P3) = *(no->P2);
        *(no->P2) = *(no->P1);
        *(no->P1) = -1;
        *(no->C4) = *(no->C3);
        *(no->C3) = *(no->C2);
        *(no->C2) = *(no->C1);
        *(no->C1) = Cn;
        *(no->PR4) = *(no->PR3);
        *(no->PR3) = *(no->PR2);
        *(no->PR2) = *(no->PR1);
        *(no->PR1) = PRn;
        imprimeNoTela(no);
    }else if(Cn <= *(no->C2) || *(no->C2)==-1){
        if(Cn == *(no->C2)){
            return; //encontrada
        }
        *(no->P5) = *(no->P4);
        *(no->P4) = *(no->P3);
        *(no->P3) = *(no->P2);
        *(no->P2) = -1;
        *(no->C4) = *(no->C3);
        *(no->C3) = *(no->C2);
        *(no->C2) = Cn;
        *(no->PR4) = *(no->PR3);
        *(no->PR3) = *(no->PR2);
        *(no->PR2) =  PRn;
    }else if(Cn <= *(no->C3) || *(no->C3)==-1){
        if(Cn == *(no->C3)){
            return; //encontrada
        }
        *(no->P5) = *(no->P4);
        *(no->P4) = *(no->P3);
        *(no->P3) = -1;
        *(no->C4) = *(no->C3);
        *(no->C3) =  Cn;
        *(no->PR4) = *(no->PR3);
        *(no->PR3) = PRn;
    }else{
        if(Cn == *(no->C4)){
            return; //encontrada
        }
        *(no->P5) = *(no->P4);
        *(no->P4) = -1;
        *(no->C4) = Cn;
        *(no->PR4) = PRn;
    }
}

void imprimeNoTela(noArvB * no){
    printf("%d %d %d\n", *(no->P1), *(no->C1), *(no->PR1));
    printf("%d %d %d\n", *(no->P2), *(no->C2), *(no->PR2));
    printf("%d %d %d\n", *(no->P3), *(no->C3), *(no->PR3));
    printf("%d %d %d %d\n", *(no->P4), *(no->C4), *(no->PR4), *(no->P5));
}