#include "../headers/registroDados.h"

//Aloca memoria para todos os ponteiros do RegistroDados.
void alocaRegistrosDados(RegistroDados **registros, int numReg)
{
    *registros = malloc(sizeof(RegistroDados) * numReg);
    for (int i = 0; i < numReg; i++)
    {
        (*registros)[i].removido = malloc(sizeof(char) * 1);
        (*registros)[i].encadeamento = malloc(sizeof(int) * 1);
        (*registros)[i].idConecta = malloc(sizeof(int) * 1);
        (*registros)[i].siglaPais = malloc(sizeof(char) * 3);
        (*registros)[i].idPoPsConectado = malloc(sizeof(int) * 1);
        (*registros)[i].unidadeMedida = malloc(sizeof(char) * 2);
        (*registros)[i].velocidade = malloc(sizeof(int) * 1);
        (*registros)[i].nomePoPs = malloc(sizeof(char) * 45);
        (*registros)[i].nomePais = malloc(sizeof(char) * 45);

        *((*registros)[i].removido) = '0';
        *((*registros)[i].encadeamento) = -1;
    }
}

//Desaloca memoria para todos os ponteiros do RegistroDados.
void desalocaRegistrosDados(RegistroDados **registros, int numReg)
{
    for (int i = 0; i < numReg; i++)
    {
        free((*registros)[i].removido);
        free((*registros)[i].encadeamento);
        free((*registros)[i].idConecta);
        free((*registros)[i].siglaPais);
        free((*registros)[i].idPoPsConectado);
        free((*registros)[i].unidadeMedida);
        free((*registros)[i].velocidade);
        free((*registros)[i].nomePoPs);
        free((*registros)[i].nomePais);
    }
    free(*registros);
}

//Exibe na tela um RegistroDados.
void imprimeRegistroDadosTela(RegistroDados *registro)
{
    if (*(registro->idConecta) != -1)
    {
        printf("Identificador do ponto: %d\n", *(registro->idConecta));
    }
    if ((registro->nomePoPs)[0] != '\0')
    {
        printf("Nome do ponto: %s\n", registro->nomePoPs);
    }
    if ((registro->nomePais)[0] != '\0')
    {
        printf("Pais de localizacao: %s\n", registro->nomePais);
    }
    if ((registro->siglaPais)[0] != '$' && (registro->siglaPais)[0] != '\0')
    {
        printf("Sigla do pais: %s\n", registro->siglaPais);
    }
    if (*(registro->idPoPsConectado) != -1)
    {
        printf("Identificador do ponto conectado: %d\n", *(registro->idPoPsConectado));
    }
    if (*(registro->velocidade) != -1)
    {
        if ((registro->unidadeMedida)[0] == '$')
        {
            printf("Velocidade de transmissao: %d bps\n", *(registro->velocidade));
        }
        else
        {
            printf("Velocidade de transmissao: %d %cbps\n", *(registro->velocidade), *(registro->unidadeMedida));
        }
    }
}

//Recebe um RegistroDados do teclado e coloca na RAM.
void lerRegistroDadosTeclado(RegistroDados *registro)
{
    char *id_conecta = malloc(sizeof(char) * 10);
    char *nomePoPs = malloc(sizeof(char) * 50);
    char *nomePais = malloc(sizeof(char) * 50);
    char *siglaPais = malloc(sizeof(char) * 3);
    char *id_pops_conectado = malloc(sizeof(char) * 10);
    char *unidade = malloc(sizeof(char) * 10);
    char *velocidade = malloc(sizeof(char) * 10);

    scanf("%s", id_conecta);
    scan_quote_string(nomePoPs);
    scan_quote_string(nomePais);
    scan_quote_string(siglaPais);
    scanf("%s", id_pops_conectado);
    scan_quote_string(unidade);
    scanf("%s", velocidade);

    char *nulo = malloc(sizeof(char) * 10);
    strcpy(nulo, "NULO");
    if (strcmp(id_conecta, nulo) != 0)
    {
        // campo nao eh nulo
        *(registro->idConecta) = atoi(id_conecta);
    }
    else
    {
        *(registro->idConecta) = -1;
    }

    if (strcmp(nomePoPs, nulo) != 0)
    {
        // campo nao eh nulo
        strcpy(registro->nomePoPs, nomePoPs);
    }
    else
    {
        (registro->nomePoPs)[0] = '\0';
    }

    if (strcmp(nomePais, nulo) != 0)
    {
        // campo nao eh nulo
        strcpy(registro->nomePais, nomePais);
    }
    else
    {
        (registro->nomePais)[0] = '\0';
    }

    if (strcmp(siglaPais, nulo) != 0)
    {
        // campo nao eh nulo
        strcpy(registro->siglaPais, siglaPais);
    }
    else
    {
        (registro->siglaPais)[0] = '\0';
    }

    if (strcmp(id_pops_conectado, nulo) != 0)
    {
        // campo nao eh nulo
        *(registro->idPoPsConectado) = atoi(id_pops_conectado);
    }
    else
    {
        *(registro->idPoPsConectado) = -1;
    }

    if (strcmp(unidade, nulo) != 0)
    {
        // campo nao eh nulo
        *(registro->unidadeMedida) = unidade[0];
    }
    else
    {
        *(registro->unidadeMedida) = '\0';
    }

    if (strcmp(velocidade, nulo) != 0)
    {
        // campo nao eh nulo
        *(registro->velocidade) = atoi(velocidade);
    }
    else
    {
        *(registro->velocidade) = -1;
    }

    free(id_conecta);
    free(nomePoPs);
    free(nomePais);
    free(siglaPais);
    free(id_pops_conectado);
    free(unidade);
    free(velocidade);
    free(nulo);
}