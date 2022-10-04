#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/funcoesFornecidas.h"
#include "../headers/arquivoBin.h"
#include "../headers/funcionalidades.h"


int main(int argC, char *argV[]){
    RegistroDados* reg;
    alocaRegistrosDados(&reg, 1);
    *(reg->removido) = '0';
    *(reg->encadeamento) = 8;
    *(reg->idConecta) = 50;
    *(reg->idPoPsConectado) = 7;
    *(reg->unidadeMedida) = 'M';
    *(reg->velocidade) = 115;
    (reg->siglaPais) = "br";
    (reg->nomePoPs) = "Nicholas";
    (reg->nomePais) = "Brasil";
    imprimeRegistroDadosTela(reg);

    RegistroCabecalho* cabecalho;
    alocaRegistrosCabecalho(&cabecalho);
    *(cabecalho->status) = '1';
    *(cabecalho->nroPagDisco) = 5;
    *(cabecalho->nroRegRem) = 6;
    *(cabecalho->proxRRN) = 7;
    *(cabecalho->qttCompacta) = 8;    
    *(cabecalho->topo) = -1;
    imprimeRegistroCabecalhoTela(cabecalho);
    FILE * arq = abrirEscrita_bin("binario.bin");
    escreverRegistroCabecalhoArquivoBin(arq, cabecalho);
    //inserirRegistroDadosArquivoBin(arq,cabecalho,reg);
    fecharArquivo_bin(arq);
    return 0;
   /*int opcao;
    char * nome_arquivo = malloc(sizeof(char)*20);
    
    scanf("%d %s", &opcao, nome_arquivo);
    
    //Create table (1) - Isaac e Nicholas
    //le do csv
    
    //Select (2) - Nicholas
    // mostra tudo (so le do binario)
    if(opcao == 2){
        funcionalidade2Select(nome_arquivo);
    }    

    //Select where (3) - Isaac
    //le comando da tela
    if(opcao == 3){
            //numeros de buscas a serem realizadas
            int numBuscas;
            scanf("%d", &numBuscas);
            printf("%d--%s--%d--", opcao, nome_arquivo,numBuscas);
            char * nome_campo = malloc(sizeof(char)*20);
            char * valor_campo = malloc(sizeof(char)*800);
             
            for(int i=0; i<numBuscas; i++){
                scanf("%s", nome_campo);
                fgetc(stdin);
                fgets(valor_campo, 799, stdin);
                valor_campo[strlen(valor_campo)-1] = '\0';
                


            }
    }


    //Remocao logica (4) - Isaac
    //le comando da tela

    //Insercao (5) - Nicholas
    //insere no binario
    //le da tela

    //Compactacao (6) - Isaac
    //cria outro binario
    
    return 0;*/
}   

