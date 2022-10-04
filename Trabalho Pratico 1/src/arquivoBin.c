#include "../headers/arquivoBin.h"
#include <stdlib.h>

//Abre arquivo binario para leitura
//Nao atualiza o status
FILE * abrirLeitura_bin(char * nome_arquivo){
    FILE *arq = fopen(nome_arquivo, "rb");
    if(arq == NULL){
        msg_erro_Arq_Inexistente();
        return NULL;
    }
    return arq;
}

//Abre arquivo binario para escrita
//Atualiza o status do arquivo para (1) -> Inconsistente
FILE * abrirEscrita_bin(char * nome_arquivo){
    FILE *arq = fopen(nome_arquivo, "wb");
    fseek(arq, 0, SEEK_SET);
    char* status = malloc(sizeof(char)*1);
    status[0] = '0';
    fwrite(status,sizeof(char), 1, arq);
    return arq;
}

//Fecha arquivo binario atualizando status
//Necessario usar essa funcao apenas quando o arquivo foi aberto para escrita
void fecharArquivo_bin(FILE * arquivo_bin){
    char* status = malloc(sizeof(char)*1);
    status[0] = '1';
    fwrite(status, sizeof(char), 1, arquivo_bin);
    fclose(arquivo_bin);
}

//Le registro de dados do arquivo binario por RRN
RegistroDados * lerRegistroDadosArquivoBin_RRN(FILE * arquivoBin,int RRN){
    int byteoffset = 960 + 64*RRN;
    fseek(arquivoBin, byteoffset, SEEK_SET);
    char* removido = malloc(sizeof(char));
    fread(removido, sizeof(char), 1, arquivoBin);
    RegistroDados * registro;
    if(*removido == '0'){
        alocaRegistrosDados(&registro, 1);
        registro->removido = removido;
        fread(registro->encadeamento, sizeof(int), 1, arquivoBin);
        fread(registro->idConecta, sizeof(int), 1, arquivoBin);
        fread(registro->siglaPais, sizeof(char), 2, arquivoBin);
        fread(registro->idPoPsConectado, sizeof(int), 1, arquivoBin);
        fread(registro->unidadeMedida, sizeof(char), 1, arquivoBin);
        fread(registro->velocidade, sizeof(int), 1, arquivoBin);
        int indice = 0;
        char c = fgetc(arquivoBin);
        while(c != '|'){
            registro->nomePoPs[indice] = c;
            c = fgetc(arquivoBin);
            indice++;
        }
        registro->nomePoPs[indice] = '\0';
        indice = 0;
        c = fgetc(arquivoBin);
        while(c != '|'){
            registro->nomePais[indice] = c;
            c = fgetc(arquivoBin);
            indice++;
        }
        registro->nomePoPs[indice] = '\0';
        
    }else{
        //registro removido
        msg_erro_RRN_Invalido();
    }

    free(removido);
}


//Le registro de cabecalho do arquivo binario
RegistroCabecalho * lerRegistroCabecalhoArquivoBin(FILE * arquivoBin){
    RegistroCabecalho* registro;
    alocaRegistrosCabecalho(registro);
    fseek(arquivoBin, 0, SEEK_SET);
    fread(registro->status, sizeof(char), 1, arquivoBin);
    fread(registro->topo, sizeof(int), 1, arquivoBin);
    fread(registro->proxRRN, sizeof(int), 1, arquivoBin);
    fread(registro->nroRegRem, sizeof(int), 1, arquivoBin);
    fread(registro->nroPagDisco, sizeof(int), 1, arquivoBin);
    fread(registro->qttCompacta, sizeof(int), 1, arquivoBin);
}

//Insere registro de dados no arquivo binario
//Pode inserir registro ja como removidos (caso eles venham assim do arquivo CSV)
//Recebe registro de cabecalho atual (pois o registro de cabecalho so sera gravado no arquivo ao fim de todas as insersoes)
//Nao controla o numero de paginas de disco
void inserirRegistroDadosArquivoBin(FILE * arquivoBin, RegistroCabecalho * cabecalho, RegistroDados * dados){
    if(*(dados->removido) == 1){
        //Insercao de registro removido -> empilha  
        int topo = *(cabecalho->topo);
        *(cabecalho->topo) = *(cabecalho->proxRRN);
        *(cabecalho->proxRRN) = *(cabecalho->proxRRN) + 1;
        int byteoffset = 960 + 64*(*(cabecalho->proxRRN));
        fseek(arquivoBin, byteoffset, SEEK_SET);
        char* removido = malloc(sizeof(char));
        *removido = '1';
        int * encadeamento = malloc(sizeof(int));
        *encadeamento = topo;
        char * lixo = malloc(sizeof(char));
        *lixo = '$';
        fwrite(removido,sizeof(char),1, arquivoBin);
        fwrite(encadeamento,sizeof(int),1, arquivoBin);
        for(int i =0; i<59; i++){
            fwrite(lixo,sizeof(char),1, arquivoBin);
        }

        free(removido);
        free(encadeamento);
        free(lixo);
    }else{
        //Insercao normal (registro nao eh removido)
        if(*(cabecalho->topo) == -1){
            //nao tem registros removidos -> insere no proximo RRN
            int byteoffset = 960 + 64*(*(cabecalho->proxRRN));
            fseek(arquivoBin, byteoffset, SEEK_SET);
        }else{
            //Existem registros removidos -> desempilha
            int byteoffsetNovoTopo = 960 + 64*(*(cabecalho->topo)) + 1;
            fseek(arquivoBin,byteoffsetNovoTopo, SEEK_SET);
            int* novoTopo = malloc(sizeof(int));
            fread(novoTopo, sizeof(int), 1, arquivoBin);
            *(cabecalho->topo) = *novoTopo;
            *(cabecalho->nroRegRem) = *(cabecalho->nroRegRem) - 1;
            int byteoffset = byteoffsetNovoTopo - 1;
            fseek(arquivoBin,byteoffset, SEEK_SET);
            free(novoTopo);
        }

        char * pipe = malloc(sizeof(char));
        *pipe = '|';
        fwrite(dados->removido,sizeof(char), 1, arquivoBin);
        fwrite(dados->encadeamento,sizeof(int), 1, arquivoBin);
        fwrite(dados->idConecta,sizeof(int), 1, arquivoBin);
        fwrite(dados->siglaPais,sizeof(char), 2, arquivoBin);
        fwrite(dados->idPoPsConectado,sizeof(int), 1, arquivoBin);
        fwrite(dados->unidadeMedida,sizeof(char), 1, arquivoBin);
        fwrite(dados->velocidade,sizeof(int), 1, arquivoBin);
        fwrite(dados->nomePoPs,sizeof(char), strlen(dados->nomePoPs)-1, arquivoBin);
        fwrite(pipe,sizeof(char), 1, arquivoBin);
        fwrite(dados->nomePais,sizeof(char),  strlen(dados->nomePoPs)-1, arquivoBin);
        fwrite(pipe,sizeof(char), 1, arquivoBin);
        free(pipe);
    }
}


//Grava registro de cabecalho no arquivo binario
int escreverRegistroCabecalhoArquivoBin(FILE * arquivoBin, RegistroCabecalho * registroCabecalho){

}
