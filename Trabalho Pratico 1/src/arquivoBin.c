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
    *status = '0';
    fwrite(status,sizeof(char), 1, arq);
    free(status);
    return arq;
}

//Fecha arquivo binario atualizando status
//Necessario usar essa funcao apenas quando o arquivo foi aberto para escrita
void fecharArquivo_bin(FILE * arquivo_bin){
    char* status = malloc(sizeof(char)*1);
    *status = '1';
    fseek(arquivo_bin, 0, SEEK_SET);
    fwrite(status, sizeof(char), 1, arquivo_bin);
    fclose(arquivo_bin);
    free(status);
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
    alocaRegistrosCabecalho(&registro);
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
    printf("ftell-98: %ld \n", ftell(arquivoBin));
    long byteoffset = 0;
    if(*(dados->removido) == '1'){
        printf("Insercao de registro removido -> empilha\n");
        //Insercao de registro removido -> empilha  

        //Pega o topo atual a atualiza o topo para o prox RRN
        int topo = *(cabecalho->topo);
        *(cabecalho->topo) = *(cabecalho->proxRRN);

        //Calcula byteoffset de onde o registro sera inserido
        byteoffset = 960 + 64*(*(cabecalho->proxRRN));
        fseek(arquivoBin, byteoffset, SEEK_SET);

        //Atualiza proximo RRN disponivel (pois insercao de registro removido eh feita no final)
        *(cabecalho->proxRRN) = *(cabecalho->proxRRN) + 1;
         
        //Atualiza nro de registros removidos
        *(cabecalho->nroRegRem) = *(cabecalho->nroRegRem) + 1;

        //Aloca variaveis locais
        char* removido = malloc(sizeof(char));
        *removido = '1';
        int * encadeamento = malloc(sizeof(int));
        *encadeamento = topo;
        char * lixo = malloc(sizeof(char));
        *lixo = '$';

        //Grava campos de controle do registro removido e completa com lixo
        fwrite(removido,sizeof(char),1, arquivoBin);
        fwrite(encadeamento,sizeof(int),1, arquivoBin);
        for(int i =0; i<59; i++){
            fwrite(lixo,sizeof(char),1, arquivoBin);
        }

        //Libera variaveis locais
        free(removido);
        free(encadeamento);
        free(lixo);
    }else{
        int tamLixo = 0;
        printf("Insercao normal (registro nao eh removido)\n");
        byteoffset = 0;
        //Insercao normal (registro nao eh removido)
        if(*(cabecalho->topo) == -1){
            printf("Nao tem registros removidos -> insere no proximo RRN\n");
            //nao tem registros removidos -> insere no proximo RRN
            byteoffset = 960 + 64*(*(cabecalho->proxRRN));
            fseek(arquivoBin, byteoffset, SEEK_SET);
            printf("ftell-133: %ld \n", ftell(arquivoBin));
        }else{
            printf("Existem registros removidos -> desempilha\n");
            //Existem registros removidos -> desempilha
            long byteoffsetNovoTopo = 960 + 64*(*(cabecalho->topo)) + 1;

            //Forma de manter o mesmo valor de encadeamento caso o registro tenha sido removido previamente (revisar)
            //*(dados->encadeamento) = *(cabecalho->topo);

            fseek(arquivoBin,byteoffsetNovoTopo, SEEK_SET);
            printf("ftell-139: %ld \n", ftell(arquivoBin));

            //int* novoTopo = malloc(sizeof(int));
            fread(cabecalho->topo, sizeof(int), 1, arquivoBin);
            printf("topo: %d\n", *(cabecalho->topo));

            //*(cabecalho->topo) = *novoTopo;
            *(cabecalho->nroRegRem) = *(cabecalho->nroRegRem) - 1;

            fseek(arquivoBin,-1, SEEK_CUR);
            printf("ftell-146: %ld \n", ftell(arquivoBin));
            //free(novoTopo);
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
        fwrite(dados->nomePoPs,sizeof(char), strlen(dados->nomePoPs), arquivoBin);
        fwrite(pipe,sizeof(char), 1, arquivoBin);
        fwrite(dados->nomePais,sizeof(char),  strlen(dados->nomePais), arquivoBin);
        fwrite(pipe,sizeof(char), 1, arquivoBin);
        free(pipe);
    }
    int tamLixo;
    //Verifica se eh o byteoffset do inicio de uma pagina de disco
    if(byteoffset%960 == 0){
        tamLixo = 20 + strlen(dados->nomePoPs) + strlen(dados->nomePais) + 2; //tam campos fixos + tam campos variaiveis + tam pipes
        tamLixo += 64*14;   
        //Atualiza quantidade de pag de disco
        *(cabecalho->nroPagDisco) = *(cabecalho->nroPagDisco) + 1; 
    }
    char * lixo = malloc(sizeof(char)*960);
    for(int i=0; i<960; i++){
        lixo[i] = '$';
    }
    printf("tam lixo %d\n", tamLixo);
    fwrite(lixo,sizeof(char), tamLixo, arquivoBin);
    free(lixo);
}

//Grava registro de cabecalho no arquivo binario
int escreverRegistroCabecalhoArquivoBin(FILE * arquivoBin, RegistroCabecalho * cabecalho){
    fseek(arquivoBin, 0, SEEK_SET);
    fwrite(cabecalho->status, sizeof(char), 1, arquivoBin);
    fwrite(cabecalho->topo, sizeof(int), 1, arquivoBin);
    fwrite(cabecalho->proxRRN, sizeof(int), 1, arquivoBin);
    fwrite(cabecalho->nroRegRem, sizeof(int), 1, arquivoBin);
    fwrite(cabecalho->nroPagDisco, sizeof(int), 1, arquivoBin);
    fwrite(cabecalho->qttCompacta, sizeof(int), 1, arquivoBin);    
    char * lixo = malloc(sizeof(char)*960);
    for(int i=0; i<960; i++){
        lixo[i] = '$';
    }
    fwrite(lixo,sizeof(char), 960-21, arquivoBin);
    free(lixo);
}