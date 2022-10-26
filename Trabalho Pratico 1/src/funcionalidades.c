#include "../headers/funcionalidades.h"

/**
 * Tira as aspas duplas de uma string deixando somente
 * o conteudo entre elas.
 *
 * @param str String que será tirado as "".
 */
void tiraAspasDuplas(char *str)
{
    //Se tiver aspas no comeco da string
    if (str[0] == '"')
    {
        int i = 0;
        while (i + 1 < (strlen(str)) && str[i + 1] != '"')
        { //Enquanto o proximo ainda
            str[i] = str[i + 1];
            i++;
        }
        for (i; i < (strlen(str)); i++)
        {
            str[i] = '\0';
        }
    }
}

/**
 * Compara um campo do dado com o valor recebido.
 *
 * @param dados Ponteiro para registro de dados a ser comparado.
 * @param nome_campo String do nome do campo a ser comparado.
 * @param valor_campo String do valor a ser comparado
 *
 * @return Retorna 1 se o valor igual ao do campo do registro
 * e 0 se for diferente.
 */
int comparaDado(RegistroDados *dados, char *nome_campo, char *valor_campo)
{
    tiraAspasDuplas(valor_campo);

    if (!strcmp(nome_campo, "idConecta"))
    {   
        if (atoi(valor_campo) == *(dados->idConecta))
        {
            return 1;
        }
    }
    else if (!strcmp(nome_campo, "siglaPais"))
    {
        if (!strcasecmp(valor_campo, dados->siglaPais))
        {
            return 1;
        }
    }
    else if (!strcmp(nome_campo, "idPoPsConectado"))
    {
        if (atoi(valor_campo) == *(dados->idPoPsConectado))
        {
            return 1;
        }
    }
    else if (!strcmp(nome_campo, "unidadeMedida"))
    {   
        if (!strcasecmp(valor_campo, dados->unidadeMedida))
        {
            return 1;
        }
    }
    else if (!strcmp(nome_campo, "velocidade"))
    {
        if (atoi(valor_campo) == *(dados->velocidade))
        {
            return 1;
        }
    }
    else if (!strcmp(nome_campo, "nomePoPs"))
    {
        if (!strcasecmp(valor_campo, dados->nomePoPs))
        {
            return 1;
        }
    }
    else if (!strcmp(nome_campo, "nomePais"))
    {
        if (!strcasecmp(valor_campo, dados->nomePais))
        {
            return 1;
        }
    }

    return 0;
}

/**
 * Copia um inteiro (src) para uma string (dest).
 *
 * @param dest Inteiro destido para copia.
 * @param src  String fonte para copia.
 */
void copiaInt(int *dest, char *src)
{
    //Se a string fonte nao for nula e nem vazia
    if ((src != NULL) && (src[0] != '\0'))
    {
        //Copia da string fonte para destino
        *dest = atoi(src);
    }
    else
    {
        //Deixa destino nulo
        *dest = -1;
    }
}

/**
 * Copia uma string (src) de tamanho fixo para outra string (dest).
 *
 * @param dest String destido para copia.
 * @param src String fonte para copia.
 */
void copiaStrFix(char *dest, char *src)
{
    //Se a string fonte nao for nula e nem vazia
    if ((src != NULL) && (src[0] != '\0'))
    {
        //Copia da string fonte para string destino
        strcpy(dest, src);
    }
    else if (src[0] == '\0')
    {
        //Deixa destino nulo
        dest[0] = '\0';
    }
}

/**
 * Copia uma String (src) de tamanho variavel para outra string (dest).
 *
 * @param dest String destido para copia.
 * @param src String fonte para copia.
 */
void copiaStrVar(char *dest, char *src)
{
    //Se a string fonte nao for nula e nem vazia
    if ((src != NULL) && (src[0] != '\0'))
    {
        //Copia da string fonte para string destino
        if (src[strlen(src) - 1] == ' ')
        {
            src[strlen(src) - 1] = '\0';
        }

        strcpy(dest, src);
    }
    else
    {
        //Deixa destino nulo
        dest[0] = '\0';
    }
}

/**
 * Corta os dados de uma string (buf) do tipo:
 * "idConecta,nomePoPs,nomePais,siglaPais,
 * idPoPsConectado,unidadeMedida,velocidade"
 * seprando na virgula e retornando somente o valor
 * anterior a virgula (dado).
 *
 * @param buf String que contem os dados a serem cortados.
 * @param dado String que recebera o valor anterior a uma virgula.
 */
void cortaDados(char *buf, char *dado)
{
    //Garante dado vazio
    for (int i = 0; i < sizeof(dado); i++)
    {
        dado[i] = '\0';
    }

    //Verifica se o buffer recebido esta vazio
    if (buf == NULL)
    {
        return; //Encerra a funcao
    }

    //Cria buffer para copia do restante do buffer
    char buf_res[100];
    //Garate que buf_res vaizo
    for (int i = 0; i < 100; i++)
    {
        buf_res[i] = '\0';
    }

    //Enquanto caractere atual do buffer for diferente de '\0'
    int i = 0;
    while ((buf[i] != '\0') && (buf[i] != ','))
    {
        dado[i] = buf[i];
        i++;
    }
    dado[i] = '\0';
    i++;

    //Enquanto atual caractere do buffer for diferente de '\0'
    int j = 0;
    while (buf[i + j] != '\0')
    {
        buf_res[j] = buf[i + j];
        j++;
    }
    buf_res[j] = '\0';
    strcpy(buf, buf_res);

    //Enquanto o buffer nao chega no final
    while (j < 100)
    {
        buf[j] = '\0';
        j++;
    }
}

/**
 * Pega os dados de uma string (buf) do tipo:
 * "idConecta,nomePoPs,nomePais,siglaPais,
 * idPoPsConectado,unidadeMedida,velocidade"
 * e coloca nos devidos campos do resgistro de dados (dados).
 *
 * @param buf String que contem os dados a serem colocados no registro.
 * @param dados Registro de Dados onde os dados do bufer seram colocados.
 */
void pegaDados(char *buf, RegistroDados *dados)
{
    char dado[50];
    cortaDados(buf, dado);

    //Se o dado for nulo ou marcado removido
    if ((dado != NULL) && (dado[0] == '*'))
    {
        //Marca o dado como removido e retorna
        *(dados->removido) = '1';
        return;
    }
    else
    {
        //Marca como nao removido
        *(dados->removido) = '0';

        //Inicia o encadeamento com -1
        *(dados->encadeamento) = -1;

        //Copia os dados para o Registro de dados
        copiaInt((dados->idConecta), dado);

        cortaDados(buf, dado);
        copiaStrVar((dados->nomePoPs), dado);

        cortaDados(buf, dado);
        copiaStrVar((dados->nomePais), dado);

        cortaDados(buf, dado);
        copiaStrFix((dados->siglaPais), dado);
        cortaDados(buf, dado);
        copiaInt((dados->idPoPsConectado), dado);

        cortaDados(buf, dado);
        copiaStrFix((dados->unidadeMedida), dado);
        cortaDados(buf, dado);
        copiaInt((dados->velocidade), dado);
    }
}

/**
 * Busca em um arquivo binario toos os dados que possuem um valor especifico
 * para um campo especifico e os exibe na tela.
 *
 * @param nome_campo Campo que sera buscado.
 * @param valor_campo Valor que sera buscado.
 * @param arquivoBin Arquivo binario.
 *
 * @return Retorna 0 quando não encontrou nunhum dado
 * dado com o valor do campo procurado e 1 quando encontrou
 * pelo menos 1 dado com o valor do campo procurado.
 */
int buscaCampoImprime(char *nome_campo, char *valor_campo, RegistroCabecalho *cabecalho, FILE *arquivoBin)
{   
    //Inidcador de alocacao do cabecalho.
    int flag_cabecalho = 0;
    if(cabecalho == NULL) {
        //Se cabecalho for nulo aloca para poder usar na função.
        cabecalho = lerRegistroCabecalhoArquivoBin(arquivoBin);
        //Indica que o cabecalho foi alocado.
        flag_cabecalho = 1;
    }

    int flag_encontrados = 0;
    RegistroDados *dados;

    //Verifica todos os RRNs do arquivo
    for (int i = 0; i < *(cabecalho->proxRRN); i++)
    {
        dados = lerRegistroDadosArquivoBin_RRN(arquivoBin, i);
        if (dados != NULL)
        {
            //Se dado nao foi removido e o campo possui o dado buscado.
            if (comparaDado(dados, nome_campo, valor_campo))
            {
                flag_encontrados = 1;
                imprimeRegistroDadosTela(dados);
                printf("\n");
            }
            desalocaRegistrosDados(&dados, 1);
        }
    }

    if(flag_cabecalho == 1) {
        desalocaRegistrosCabecalho(cabecalho);
        cabecalho = NULL;
    }

    return flag_encontrados;
}

/**
 * Busca em um arquivo binario toos os dados que possuem um valor especifico
 * para um campo especifico e os remove logicamente desse arquivo.
 *
 * @param nome_campo Campo que sera buscado.
 * @param valor_campo Valor que sera buscado.
 * @param arquivoBin Arquivo binario.
 */
void buscaCampoRemove(char *nome_campo, char *valor_campo, RegistroCabecalho *cabecalho, FILE *arquivoBin)
{
    //Inidcador de alocacao do cabecalho.
    int flag_cabecalho = 0;
    if(cabecalho == NULL) {
        //Se cabecalho for nulo aloca para poder usar na função.
        cabecalho = lerRegistroCabecalhoArquivoBin(arquivoBin);
        //Indica que o cabecalho foi alocado.
        flag_cabecalho = 1;
    }
    
    RegistroDados *dados;

    //Verifica todos os RRNs do arquivo
    for (int i = 0; i < *(cabecalho->proxRRN); i++)
    {
        dados = lerRegistroDadosArquivoBin_RRN(arquivoBin, i);
        if (dados != NULL)
        {
            //Se dado nao foi removido e o campo possui o dado buscado.
            if (comparaDado(dados, nome_campo, valor_campo))
            {   
                removeRegistroDadosArquivoBin_RRN(arquivoBin, cabecalho, i);
            }
            desalocaRegistrosDados(&dados, 1);
        }
    }

    if(flag_cabecalho == 1) {
        escreverRegistroCabecalhoArquivoBin(arquivoBin, cabecalho);
        desalocaRegistrosCabecalho(cabecalho);
        cabecalho = NULL;
    }
}

void funcionalidade1CreateTable(char *nome_arquivo_bin, char *nome_arquivo_csv)
{
    FILE *arquivoCSV = abrirLeitura_csv(nome_arquivo_csv);
    if (arquivoCSV == NULL)
    { //Mensagem de erro ja eh exibida pela funcao abrirLeitura_csv()
        return;
    }
    FILE *arquivoBin = abrirEscrita_bin(nome_arquivo_bin);
    if (arquivoBin == NULL)
    {
        msg_erro_Arq_FalhaCriacao();
        return;
    }
    RegistroCabecalho *cabecalho;
    alocaRegistrosCabecalho(&cabecalho);
    RegistroDados *dados;
    alocaRegistrosDados(&dados, 1);

    char *buf = malloc(sizeof(char) * 100);

    //Pega a primeira linha do arquivo CSV e descarta
    fgets(buf, 100, arquivoCSV);
    for (int i = 0; i < 100; i++)
    {
        buf[i] = '\0';
    }

    //Pega linha a linha do arquivo CSV e insere no arquivo binario
    while (fgets(buf, 100, arquivoCSV) != NULL)
    {
        int i = strlen(buf);
        buf[i - 1] = '\0';
        pegaDados(buf, dados);
        inserirRegistroDadosArquivoBin(arquivoBin, cabecalho, dados);
    }

    escreverRegistroCabecalhoArquivoBin(arquivoBin, cabecalho);

    desalocaRegistrosCabecalho(cabecalho);
    desalocaRegistrosDados(&dados, 1);
    fecharArquivo_bin(arquivoBin);
    fclose(arquivoCSV);
    free(buf);
    binarioNaTela(nome_arquivo_bin);
}

void funcionalidade2Select(char *nome_arquivo)
{
    FILE *arquivoBin = abrirLeitura_bin(nome_arquivo);
    if (arquivoBin == NULL)
    {
        msg_erro_Arq_Inconsistente();
        return;
    }
    RegistroCabecalho *cabecalho = lerRegistroCabecalhoArquivoBin(arquivoBin);
    RegistroDados *dados;

    //Verifica todos os RRNs do arquivo
    for (int i = 0; i < *(cabecalho->proxRRN); i++)
    {
        dados = lerRegistroDadosArquivoBin_RRN(arquivoBin, i);

        if (dados != NULL)
        {
            imprimeRegistroDadosTela(dados);
            printf("\n");
            desalocaRegistrosDados(&dados, 1);
        }
    }
    if (*(cabecalho->proxRRN) == 0)
    {
        msg_erro_Reg_Inexistente();
        printf("\n\n");
    }
    printf("Numero de paginas de disco: %d\n\n", *(cabecalho->nroPagDisco));

    desalocaRegistrosCabecalho(cabecalho);
    fecharArquivo_bin(arquivoBin);
}

void funcionalidade3SelectWhere(char *nome_arquivo)
{
    //Numeros de buscas a serem realizadas
    int numBuscas;
    scanf("%d", &numBuscas);
    FILE *arquivoBin = abrirLeitura_bin(nome_arquivo);
    if (arquivoBin == NULL)
    {
        msg_erro_Arq_Inconsistente();
        return;
    }
    RegistroCabecalho *cabecalho = lerRegistroCabecalhoArquivoBin(arquivoBin);

    char *nome_campo = malloc(sizeof(char) * 50);
    char *valor_campo = malloc(sizeof(char) * 50);
    //Faz n buscas
    for (int i = 0; i < numBuscas; i++)
    {
        //Pega o nome do campo.
        scanf("%s", nome_campo);
        //Pega espaco entre o nome e o valor.
        fgetc(stdin);
        //Pega o valor do campo.
        fgets(valor_campo, 50, stdin);

        printf("Busca %d\n", i + 1);

        //Se nao encontrar nenhum arquivo quebra linha.
        if (buscaCampoImprime(nome_campo, valor_campo, cabecalho, arquivoBin) == 0)
        {
            msg_erro_Reg_Inexistente();
            printf("\n\n");
        }
        printf("Numero de paginas de disco: %d\n\n", *(cabecalho->nroPagDisco));
    }

    desalocaRegistrosCabecalho(cabecalho);
    free(nome_campo);
    free(valor_campo);
    fecharArquivo_bin(arquivoBin);
}

void funcionalidade4Remove(char *nome_arquivo)
{
    //Numeros de buscas a serem realizadas
    int numBuscas;
    scanf("%d", &numBuscas);
    FILE *arquivoBin = abrirEscrita_bin(nome_arquivo);
    if (arquivoBin == NULL)
    {
        msg_erro_Arq_Inconsistente();
        return;
    }
    RegistroCabecalho *cabecalho = lerRegistroCabecalhoArquivoBin(arquivoBin);
    char *nome_campo = malloc(sizeof(char) * 50);
    char *valor_campo = malloc(sizeof(char) * 50);

    //Faz n buscas
    for (int i = 0; i < numBuscas; i++)
    {
        //Pega o nome do campo.
        scanf("%s", nome_campo);
        //Pega espaco entre o nome e o valor.
        fgetc(stdin);
        //Pega o valor do campo.
        fgets(valor_campo, 50, stdin);

        buscaCampoRemove(nome_campo, valor_campo, cabecalho, arquivoBin);
    }

    //Escreve o registro de cabecalho atualizado no arquivo binario
    escreverRegistroCabecalhoArquivoBin(arquivoBin, cabecalho);

    desalocaRegistrosCabecalho(cabecalho);
    free(nome_campo);
    free(valor_campo);
    fecharArquivo_bin(arquivoBin);
    binarioNaTela(nome_arquivo);
}

void funcionalidade5Insert(char *nome_arquivo, int nro_reg)
{
    RegistroDados *registro;
    alocaRegistrosDados(&registro, 1);

    FILE *arquivo = abrirEscrita_bin(nome_arquivo);

    RegistroCabecalho *cabecalho = lerRegistroCabecalhoArquivoBin(arquivo);
    //Insere n registros
    for (int i = 0; i < nro_reg; i++)
    {
        lerRegistroDadosTeclado(registro);
        inserirRegistroDadosArquivoBin(arquivo, cabecalho, registro);
    }

    escreverRegistroCabecalhoArquivoBin(arquivo, cabecalho);
    fecharArquivo_bin(arquivo);
    desalocaRegistrosDados(&registro, 1);
    desalocaRegistrosCabecalho(cabecalho);

    binarioNaTela(nome_arquivo);
}

void funcionalidade6Compactacao(char *nome_arquivo)
{
    RegistroCabecalho *cabecalhoNovo;
    alocaRegistrosCabecalho(&cabecalhoNovo);
    FILE *arq_compactado = fopen("compactado.bin", "wb+");
    if (arq_compactado == NULL)
    {
        msg_erro_Arq_FalhaCriacao();
        return;
    }

    FILE *arq_original = abrirLeitura_bin(nome_arquivo);
    if (arq_original == NULL)
    {
        msg_erro_Arq_Inconsistente();
        return;
    }
    RegistroCabecalho *cabecalhoAntigo = lerRegistroCabecalhoArquivoBin(arq_original);

    for (int i = 0; i < *(cabecalhoAntigo->proxRRN); i++)
    {
        RegistroDados *dados = lerRegistroDadosArquivoBin_RRN(arq_original, i);
        if (dados != NULL)
        {
            //Registro nao removido
            inserirRegistroDadosArquivoBin(arq_compactado, cabecalhoNovo, dados);
            desalocaRegistrosDados(&dados, 1);
        }
    }
    *(cabecalhoNovo->qttCompacta) = *(cabecalhoAntigo->qttCompacta) + 1;
    escreverRegistroCabecalhoArquivoBin(arq_compactado, cabecalhoNovo);
    desalocaRegistrosCabecalho(cabecalhoNovo);
    desalocaRegistrosCabecalho(cabecalhoAntigo);

    fecharArquivo_bin(arq_compactado);
    fecharArquivo_bin(arq_original);
    remove(nome_arquivo);
    rename("compactado.bin", nome_arquivo);

    binarioNaTela(nome_arquivo);
}