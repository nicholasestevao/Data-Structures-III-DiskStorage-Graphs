#include "../headers/arquivoBin.h"
#include <stdlib.h>

// Abre arquivo binario para leitura
// Nao atualiza o status
FILE *abrirLeitura_bin(char *nome_arquivo)
{
    FILE *arq = fopen(nome_arquivo, "rb");
    if (arq == NULL)
    {
        msg_erro_Arq_Inexistente();
        return NULL;
    }
    char *status = malloc(sizeof(char));
    fread(status, sizeof(char), 1, arq);
    if (*status == '0')
    {
        fclose(arq);
        return NULL;
    }
    else
    { // Voltar para o inicio do arquivo
        fseek(arq, 0, SEEK_SET);
    }
    free(status);
    return arq;
}

// Abre arquivo binario para escrita
// Atualiza o status do arquivo para (1) -> Inconsistente
FILE *abrirEscrita_bin(char *nome_arquivo)
{
    FILE *arq = fopen(nome_arquivo, "rb+");
    if (arq == NULL)
    {
        arq = fopen(nome_arquivo, "wb+");
    }
    fseek(arq, 0, SEEK_SET);
    char *status = malloc(sizeof(char) * 1);
    *status = '0';
    fwrite(status, sizeof(char), 1, arq);
    free(status);
    return arq;
}

// Fecha arquivo binario atualizando status
// Necessario usar essa funcao apenas quando o arquivo foi aberto para escrita
void fecharArquivo_bin(FILE *arquivo_bin)
{
    char *status = malloc(sizeof(char) * 1);
    *status = '1';
    fseek(arquivo_bin, 0, SEEK_SET);
    fwrite(status, sizeof(char), 1, arquivo_bin);
    fclose(arquivo_bin);
    free(status);
}

int leCopiaRegistroArquivo_RRN(RegistroDados *dados, FILE *arquivoBin, int RRN) { 
    int byteoffset = 960 + 64 * RRN;
    fseek(arquivoBin, byteoffset, SEEK_SET);
    fread(dados->removido, sizeof(char), 1, arquivoBin);

    if (*(dados->removido) == '0')
    {
        fread(dados->encadeamento, sizeof(int), 1, arquivoBin);
        fread(dados->idConecta, sizeof(int), 1, arquivoBin);
        fread(dados->siglaPais, sizeof(char), 2, arquivoBin);
        (dados->siglaPais)[2] = '\0';
        fread(dados->idPoPsConectado, sizeof(int), 1, arquivoBin);
        fread(dados->unidadeMedida, sizeof(char), 1, arquivoBin);
        (dados->unidadeMedida)[1] = '\0';
        fread(dados->velocidade, sizeof(int), 1, arquivoBin);

        int indice = 0;
        char *c = malloc(sizeof(char));
        fread(c, sizeof(char), 1, arquivoBin);
        while (*c != '|')
        {
            (dados->nomePoPs)[indice] = *c;
            fread(c, sizeof(char), 1, arquivoBin);
            indice++;
        }
        dados->nomePoPs[indice] = '\0';
        indice = 0;
        fread(c, sizeof(char), 1, arquivoBin);
        while (*c != '|')
        {
            (dados->nomePais)[indice] = *c;
            fread(c, sizeof(char), 1, arquivoBin);
            indice++;
        }
        dados->nomePais[indice] = '\0';
        free(c);
    }
    else
    {
        // msg_erro_RRN_Invalido();
        return 0;
    }
    return 1;
}

// Le registro de dados do arquivo binario por RRN
RegistroDados *lerRegistroDadosArquivoBin_RRN(FILE *arquivoBin, int RRN)
{
    int byteoffset = 960 + 64 * RRN;
    fseek(arquivoBin, byteoffset, SEEK_SET);
    RegistroDados *registro;
    alocaRegistrosDados(&registro, 1);
    fread(registro->removido, sizeof(char), 1, arquivoBin);

    if (*(registro->removido) == '0')
    {
        fread(registro->encadeamento, sizeof(int), 1, arquivoBin);
        fread(registro->idConecta, sizeof(int), 1, arquivoBin);
        fread(registro->siglaPais, sizeof(char), 2, arquivoBin);
        (registro->siglaPais)[2] = '\0';
        fread(registro->idPoPsConectado, sizeof(int), 1, arquivoBin);
        fread(registro->unidadeMedida, sizeof(char), 1, arquivoBin);
        (registro->unidadeMedida)[1] = '\0';
        fread(registro->velocidade, sizeof(int), 1, arquivoBin);

        int indice = 0;
        char *c = malloc(sizeof(char));
        fread(c, sizeof(char), 1, arquivoBin);
        while (*c != '|')
        {
            (registro->nomePoPs)[indice] = *c;
            fread(c, sizeof(char), 1, arquivoBin);
            indice++;
        }
        registro->nomePoPs[indice] = '\0';
        indice = 0;
        fread(c, sizeof(char), 1, arquivoBin);
        while (*c != '|')
        {
            (registro->nomePais)[indice] = *c;
            fread(c, sizeof(char), 1, arquivoBin);
            indice++;
        }
        registro->nomePais[indice] = '\0';
        free(c);
    }
    else
    {
        // registro removido
        desalocaRegistrosDados(&registro, 1);
        // msg_erro_RRN_Invalido();
        return NULL;
    }
    return registro;
}

// Le registro de cabecalho do arquivo binario
RegistroCabecalho *lerRegistroCabecalhoArquivoBin(FILE *arquivoBin)
{
    RegistroCabecalho *registro;
    alocaRegistrosCabecalho(&registro);
    fseek(arquivoBin, 0, SEEK_SET);
    // printf("ftell: %d", ftell(arquivoBin));
    fread(registro->status, sizeof(char), 1, arquivoBin);
    fread(registro->topo, sizeof(int), 1, arquivoBin);
    fread(registro->proxRRN, sizeof(int), 1, arquivoBin);
    fread(registro->nroRegRem, sizeof(int), 1, arquivoBin);
    fread(registro->nroPagDisco, sizeof(int), 1, arquivoBin);
    fread(registro->qttCompacta, sizeof(int), 1, arquivoBin);
    // imprimeRegistroCabecalhoTela(registro);
    return registro;
}

// Insere registro de dados no arquivo binario
// Pode inserir registro ja como removidos (caso eles venham assim do arquivo CSV)
// Recebe registro de cabecalho atual (pois o registro de cabecalho so sera gravado no arquivo ao fim de todas as insersoes)
// Nao controla o numero de paginas de disco
void inserirRegistroDadosArquivoBin(FILE *arquivoBin, RegistroCabecalho *cabecalho, RegistroDados *dados)
{
    // printf("ftell-98: %ld \n", ftell(arquivoBin));
    long byteoffset = 0;
    int flagNovaPag = 0;
    int tamLixo = 0;

    if (*(dados->removido) == '1')
    { // Insercao de registro removido -> empilha
        // Pega o topo atual a atualiza o topo para o prox RRN
        int topo = *(cabecalho->topo);
        *(cabecalho->topo) = *(cabecalho->proxRRN);

        // Calcula byteoffset de onde o registro sera inserido
        byteoffset = 960 + 64 * (*(cabecalho->proxRRN));
        fseek(arquivoBin, byteoffset, SEEK_SET);

        // Atualiza proximo RRN disponivel (pois insercao de registro removido eh feita no final)
        *(cabecalho->proxRRN) = *(cabecalho->proxRRN) + 1;

        // Atualiza nro de registros removidos
        *(cabecalho->nroRegRem) = *(cabecalho->nroRegRem) + 1;
        // imprimeRegistroCabecalhoTela(cabecalho);
        // Aloca variaveis locais
        char *removido = malloc(sizeof(char));
        *removido = '1';
        int *encadeamento = malloc(sizeof(int));
        *encadeamento = topo;

        // Grava campos de controle do registro removido e completa com lixo
        char *lixo = malloc(sizeof(char) * 59);
        for (int i = 0; i < 59; i++)
        {
            lixo[i] = '$';
        }
        fwrite(removido, sizeof(char), 1, arquivoBin);
        fwrite(encadeamento, sizeof(int), 1, arquivoBin);
        fwrite(lixo, sizeof(char), 59, arquivoBin);

        // Libera variaveis locais
        free(removido);
        free(encadeamento);
        free(lixo);

        // Verifica se eh o byteoffset do inicio de uma pagina de disco
        if (byteoffset % 960 == 0)
        {
            tamLixo = 64 * 14;
            // Atualiza quantidade de pag de disco
            *(cabecalho->nroPagDisco) = *(cabecalho->nroPagDisco) + 1;
            lixo = malloc(sizeof(char) * 960);
            for (int i = 0; i < 960; i++)
            {
                lixo[i] = '$';
            }
            fwrite(lixo, sizeof(char), tamLixo, arquivoBin);
            free(lixo);
        }
    }
    else
    { // Insercao normal (registro nao eh removido)
        // inicia byoffset em zero
        byteoffset = 0;
        if (*(cabecalho->topo) == -1)
        { // nao tem registros removidos -> insere no proximo RRN
            byteoffset = 960 + 64 * (*(cabecalho->proxRRN));
            fseek(arquivoBin, byteoffset, SEEK_SET);
            *(cabecalho->proxRRN) += 1;
            // printf("ftell-165: %ld \n", ftell(arquivoBin));

            // Preeenche resto do registro com lixo
            tamLixo = 64 - (20 + strlen(dados->nomePais) + strlen(dados->nomePoPs) + 2);
            // Verifica se eh o byteoffset do inicio de uma pagina de disco
            if (byteoffset % 960 == 0)
            {
                // ("Insercao primeiro registro da pagina de disco");
                flagNovaPag = 1;
            }
        }
        else
        { // Existem registros removidos -> desempilha
            long byteoffsetNovoTopo = 960 + 64 * (*(cabecalho->topo)) + 1;

            int novoTopo;
            fseek(arquivoBin, byteoffsetNovoTopo, SEEK_SET);
            fread(&novoTopo, sizeof(char), 4, arquivoBin);

            *(cabecalho->topo) = novoTopo;
            *(cabecalho->nroRegRem) = *(cabecalho->nroRegRem) - 1;

            fseek(arquivoBin, byteoffsetNovoTopo - 1, SEEK_SET);
        }
        char *lixo = malloc(sizeof(char) * 64);
        for (int i = 0; i < 64; i++)
        {
            lixo[i] = '$';
        }

        char *pipe = malloc(sizeof(char));
        *pipe = '|';

        fwrite(dados->removido, sizeof(char), 1, arquivoBin);
        fwrite(dados->encadeamento, sizeof(int), 1, arquivoBin);
        fwrite(dados->idConecta, sizeof(int), 1, arquivoBin);
        if ((dados->siglaPais)[0] != '\0')
        {
            fwrite(dados->siglaPais, sizeof(char), 2, arquivoBin);
        }
        else
        { // Se a sigla do pais for nula escreve lixo
            fwrite(lixo, sizeof(char), 2, arquivoBin);
        }

        fwrite(dados->idPoPsConectado, sizeof(int), 1, arquivoBin);
        if (*(dados->unidadeMedida) != '\0')
        {
            fwrite(dados->unidadeMedida, sizeof(char), 1, arquivoBin);
        }
        else
        { // Se a unidade for nula escreve lixo
            fwrite(lixo, sizeof(char), 1, arquivoBin);
        }

        fwrite(dados->velocidade, sizeof(int), 1, arquivoBin);
        fwrite(dados->nomePoPs, sizeof(char), strlen(dados->nomePoPs), arquivoBin);
        fwrite(pipe, sizeof(char), 1, arquivoBin);
        fwrite(dados->nomePais, sizeof(char), strlen(dados->nomePais), arquivoBin);
        fwrite(pipe, sizeof(char), 1, arquivoBin);
        free(pipe);
        fwrite(lixo, sizeof(char), tamLixo, arquivoBin);
        if (flagNovaPag)
        { // Atualiza quantidade de pag de disco
            *(cabecalho->nroPagDisco) = *(cabecalho->nroPagDisco) + 1;
        }
        free(lixo);
    }
}

// Grava registro de cabecalho no arquivo binario
void escreverRegistroCabecalhoArquivoBin(FILE *arquivoBin, RegistroCabecalho *cabecalho)
{
    fseek(arquivoBin, 0, SEEK_SET);
    fwrite(cabecalho->status, sizeof(char), 1, arquivoBin);
    fwrite(cabecalho->topo, sizeof(int), 1, arquivoBin);
    fwrite(cabecalho->proxRRN, sizeof(int), 1, arquivoBin);
    fwrite(cabecalho->nroRegRem, sizeof(int), 1, arquivoBin);
    fwrite(cabecalho->nroPagDisco, sizeof(int), 1, arquivoBin);
    fwrite(cabecalho->qttCompacta, sizeof(int), 1, arquivoBin);
    char *lixo = malloc(sizeof(char) * 960);
    for (int i = 0; i < 960; i++)
    {
        lixo[i] = '$';
    }
    fwrite(lixo, sizeof(char), 960 - 21, arquivoBin);
    free(lixo);
}

// Remove logicamente um registro do arquivo binario por RRN
// e atualiza a pilha de registros removidos.
void removeRegistroDadosArquivoBin_RRN(FILE *arquivoBin, RegistroCabecalho *registroCabecalho, const int RRN)
{
    // Byteoffset do RRN a ser removio
    int byteoffset = 960 + 64 * RRN;
    fseek(arquivoBin, byteoffset, SEEK_SET);

    // Lixo a ser gravado no arquivo binario
    char *lixo = malloc(sizeof(char) * 59);
    for (int i = 0; i < 59; i++)
    {
        lixo[i] = '$';
    }
    // Marca como removido no arquivo binario
    fwrite("1", sizeof(char), 1, arquivoBin);
    // Escreve o proximo RRN da lista
    fwrite(registroCabecalho->topo, sizeof(int), 1, arquivoBin);
    // Coloca lixo no resto do Registro
    fwrite(lixo, sizeof(char), 59, arquivoBin);

    // Atualiza topo da lista
    *(registroCabecalho->topo) = RRN;
    // Aumenta numero de regitros removidos
    *(registroCabecalho->nroRegRem) = *(registroCabecalho->nroRegRem) + 1;

    // Libera memoria alocada
    free(lixo);
}