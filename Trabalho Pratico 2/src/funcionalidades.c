#include "../headers/funcionalidades.h"

/**
 * Tira as aspas duplas de uma string deixando somente
 * o conteudo entre elas.
 *
 * @param str String que será tirado as "".
 */
void tiraAspasDuplas(char *str)
{
    // Se tiver aspas no comeco da string
    if (str[0] == '"')
    {
        int i = 0;
        while (i + 1 < (strlen(str)) && str[i + 1] != '"')
        { // Enquanto o proximo ainda
            str[i] = str[i + 1];
            i++;
        }
        for (int j = i; j < (strlen(str)); j++)
        {
            str[j] = '\0';
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
    // Se a string fonte nao for nula e nem vazia
    if ((src != NULL) && (src[0] != '\0'))
    {
        // Copia da string fonte para destino
        *dest = atoi(src);
    }
    else
    {
        // Deixa destino nulo
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
    // Se a string fonte nao for nula e nem vazia
    if ((src != NULL) && (src[0] != '\0'))
    {
        // Copia da string fonte para string destino
        strcpy(dest, src);
    }
    else if (src[0] == '\0')
    {
        // Deixa destino nulo
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
    // Se a string fonte nao for nula e nem vazia
    if ((src != NULL) && (src[0] != '\0'))
    {
        // Copia da string fonte para string destino
        if (src[strlen(src) - 1] == ' ')
        {
            src[strlen(src) - 1] = '\0';
        }

        strcpy(dest, src);
    }
    else
    {
        // Deixa destino nulo
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
    // Garante dado vazio
    for (int i = 0; i < sizeof(dado); i++)
    {
        dado[i] = '\0';
    }

    // Verifica se o buffer recebido esta vazio
    if (buf == NULL)
    {
        return; // Encerra a funcao
    }

    // Cria buffer para copia do restante do buffer
    char buf_res[100];
    // Garate que buf_res vaizo
    for (int i = 0; i < 100; i++)
    {
        buf_res[i] = '\0';
    }

    // Enquanto caractere atual do buffer for diferente de '\0'
    int i = 0;
    while ((buf[i] != '\0') && (buf[i] != ','))
    {
        dado[i] = buf[i];
        i++;
    }
    dado[i] = '\0';
    i++;

    // Enquanto atual caractere do buffer for diferente de '\0'
    int j = 0;
    while (buf[i + j] != '\0')
    {
        buf_res[j] = buf[i + j];
        j++;
    }
    buf_res[j] = '\0';
    strcpy(buf, buf_res);

    // Enquanto o buffer nao chega no final
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

    // Se o dado for nulo ou marcado removido
    if ((dado[0] == '*'))
    {
        // Marca o dado como removido e retorna
        *(dados->removido) = '1';
        return;
    }
    else
    {
        // Marca como nao removido
        *(dados->removido) = '0';

        // Inicia o encadeamento com -1
        *(dados->encadeamento) = -1;

        // Copia os dados para o Registro de dados
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
 * @param cabecalho Cabecalho do arquivo binario de dados.
 * @param arquivoBin Arquivo binario de dados.
 *
 * @return Retorna 0 quando não encontrou nunhum dado
 * dado com o valor do campo procurado ou a quantidade 
 * de dados com o valor do campo procurado.
 */
int buscaCampoImprimeArquivoDados(char *nome_campo, char *valor_campo, RegistroCabecalho *cabecalho, FILE *arquivoBin)
{   
    //Inidcador de alocacao do cabecalho.
    int flag_cabecalho = 0;
    if (cabecalho == NULL)
    {
        // Se cabecalho for nulo aloca para poder usar na função.
        cabecalho = lerRegistroCabecalhoArquivoBin(arquivoBin);
        // Indica que o cabecalho foi alocado.
        flag_cabecalho = 1;
    }

    int flag_encontrados = 0;
    RegistroDados *dados;

    // Verifica todos os RRNs do arquivo
    for (int i = 0; i < *(cabecalho->proxRRN); i++)
    {
        dados = lerRegistroDadosArquivoBin_RRN(arquivoBin, i);
        if (dados != NULL)
        {
            // Se dado nao foi removido e o campo possui o dado buscado.
            if (comparaDado(dados, nome_campo, valor_campo))
            {
                flag_encontrados++;
                imprimeRegistroDadosTela(dados);
                printf("\n");
            }
            desalocaRegistrosDados(&dados, 1);
        }
    }

    if (flag_cabecalho == 1)
    {
        desalocaRegistrosCabecalho(cabecalho);
        cabecalho = NULL;
    }

    return flag_encontrados;
}

/**
 * Busca em um arquivo binario toos os dados que possuem um valor especifico
 * para um campo especifico e os exibe na tela.
 *
 * @param nome_campo Campo que sera buscado.
 * @param valor_campo Valor que sera buscado.
 * @param cabecalhoArvB Cabecalho do arquivo binario da arvore B.
 * @param arquivoArvB Arquivo binario de indices (Arvore B).
 *
 * @return Retorna 0 quando não encontrou nunhum dado
 * dado com o valor do campo procurado ou a quantidade 
 * de dados com o valor do campo procurado.
 */
int buscaCampoImprimeArquivoIndex(char *nome_campo, char *valor_campo, cabecalhoArvB *cabecalhoArvB, FILE *arquivoArvB)
{   
    //Inidcador de alocacao do cabecalho.
    int flag_cabecalho = 0;

    if(cabecalhoArvB == NULL) {
        //Se cabecalho for nulo aloca para poder usar na função.
        cabecalhoArvB = lecabecalhoArvB(arquivoArvB);
        //Indica que o cabecalho foi alocado.
        flag_cabecalho = 1;
    }

    int flag_encontrados = 0;
    

    if(flag_cabecalho == 1) {
        desalocaCabecalhoArvB(cabecalhoArvB);
        cabecalhoArvB = NULL;
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
void buscaCampoRemoveArquivoDados(char *nome_campo, char *valor_campo, RegistroCabecalho *cabecalho, FILE *arquivoBin)
{
    // Inidcador de alocacao do cabecalho.
    int flag_cabecalho = 0;
    if (cabecalho == NULL)
    {
        // Se cabecalho for nulo aloca para poder usar na função.
        cabecalho = lerRegistroCabecalhoArquivoBin(arquivoBin);
        // Indica que o cabecalho foi alocado.
        flag_cabecalho = 1;
    }

    RegistroDados *dados;

    // Verifica todos os RRNs do arquivo
    for (int i = 0; i < *(cabecalho->proxRRN); i++)
    {
        dados = lerRegistroDadosArquivoBin_RRN(arquivoBin, i);
        if (dados != NULL)
        {
            // Se dado nao foi removido e o campo possui o dado buscado.
            if (comparaDado(dados, nome_campo, valor_campo))
            {
                removeRegistroDadosArquivoBin_RRN(arquivoBin, cabecalho, i);
            }
            desalocaRegistrosDados(&dados, 1);
        }
    }

    if (flag_cabecalho == 1)
    {
        escreverRegistroCabecalhoArquivoBin(arquivoBin, cabecalho);
        desalocaRegistrosCabecalho(cabecalho);
        cabecalho = NULL;
    }
}

void funcionalidade1CreateTable(char *nome_arquivo_csv)
{
    // Recebe nome do arquivo bin
    char *nome_arquivo_bin = malloc(sizeof(char) * 20);
    scanf("%s", nome_arquivo_bin);

    FILE *arquivoCSV = abrirLeitura_csv(nome_arquivo_csv);
    if (arquivoCSV == NULL)
    {
        free(nome_arquivo_bin);
        msg_erro_Arq_Inconsistente();
        return;
    }
    FILE *arquivoBin = abrirEscrita_bin(nome_arquivo_bin);
    if (arquivoBin == NULL)
    {
        msg_erro_Arq_FalhaCriacao();
        fclose(arquivoCSV);
        free(nome_arquivo_bin);
        return;
    }
    RegistroCabecalho *cabecalho;
    alocaRegistrosCabecalho(&cabecalho);
    RegistroDados *dados;
    alocaRegistrosDados(&dados, 1);

    char *buf = malloc(sizeof(char) * 100);

    // Pega a primeira linha do arquivo CSV e descarta
    fgets(buf, 100, arquivoCSV);
    for (int i = 0; i < 100; i++)
    {
        buf[i] = '\0';
    }

    // Pega linha a linha do arquivo CSV e insere no arquivo binario
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
    free(nome_arquivo_bin);
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

    // Verifica todos os RRNs do arquivo
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

    //Se nao tiver nenhum dado no arquivo de dados;
    if (*(cabecalho->proxRRN) == 0) {
        msg_erro_Reg_Inexistente();
        printf("\n\n");
    }
    printf("Numero de paginas de disco: %d\n\n", *(cabecalho->nroPagDisco));

    desalocaRegistrosCabecalho(cabecalho);
    fecharArquivo_bin(arquivoBin);
}

void funcionalidade3SelectWhere(char *nome_arquivo)
{
    // Numeros de buscas a serem realizadas
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
    // Faz n buscas
    for (int i = 0; i < numBuscas; i++)
    {
        // Pega o nome do campo.
        scanf("%s", nome_campo);
        // Pega espaco entre o nome e o valor.
        fgetc(stdin);
        // Pega o valor do campo.
        fgets(valor_campo, 50, stdin);

        printf("Busca %d\n", i + 1);

        //Se nao encontrar nenhum arquivo imprime mensagem de erro e quebra linha.
        if (buscaCampoImprimeArquivoDados(nome_campo, valor_campo, cabecalho, arquivoBin) == 0)
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
    // Numeros de buscas a serem realizadas
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

    // Faz n buscas
    for (int i = 0; i < numBuscas; i++)
    {
        // Pega o nome do campo.
        scanf("%s", nome_campo);
        // Pega espaco entre o nome e o valor.
        fgetc(stdin);
        // Pega o valor do campo.
        fgets(valor_campo, 50, stdin);

        buscaCampoRemoveArquivoDados(nome_campo, valor_campo, cabecalho, arquivoBin);
    }

    // Escreve o registro de cabecalho atualizado no arquivo binario
    escreverRegistroCabecalhoArquivoBin(arquivoBin, cabecalho);

    desalocaRegistrosCabecalho(cabecalho);
    free(nome_campo);
    free(valor_campo);
    fecharArquivo_bin(arquivoBin);
    binarioNaTela(nome_arquivo);
}

void funcionalidade5Insert(char *nome_arquivo)
{
    // Recebe quantidade de registros a serem inseridos
    int nro_reg;
    scanf("%d", &nro_reg);

    RegistroDados *registro;
    alocaRegistrosDados(&registro, 1);

    FILE *arquivo = abrirEscrita_bin(nome_arquivo);
    if (arquivo == NULL)
    {
        msg_erro_Arq_Inconsistente();
        desalocaRegistrosDados(&registro, 1);
        return;
    }

    RegistroCabecalho *cabecalho = lerRegistroCabecalhoArquivoBin(arquivo);
    // Insere n registros
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
    FILE *arq_compactado = abrirEscrita_bin("compactado.bin");
    if (arq_compactado == NULL)
    {
        msg_erro_Arq_FalhaCriacao();
        desalocaRegistrosCabecalho(cabecalhoNovo);
        return;
    }

    FILE *arq_original = abrirLeitura_bin(nome_arquivo);
    if (arq_original == NULL)
    {
        msg_erro_Arq_Inconsistente();
        desalocaRegistrosCabecalho(cabecalhoNovo);
        fecharArquivo_bin(arq_compactado);
        return;
    }
    RegistroCabecalho *cabecalhoAntigo = lerRegistroCabecalhoArquivoBin(arq_original);

    for (int i = 0; i < *(cabecalhoAntigo->proxRRN); i++)
    {
        RegistroDados *dados = lerRegistroDadosArquivoBin_RRN(arq_original, i);
        if (dados != NULL)
        {
            // Registro nao removido
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

void funcionalidade7CreateIndex(char *nome_arquivo)
{
    char *nome_arq_indice = malloc(sizeof(char) * 50);
    scanf("%s", nome_arq_indice);
    FILE *arq_dados = abrirLeitura_bin(nome_arquivo);
    FILE *arq_indice = abrirEscrita_bin(nome_arq_indice);
    if(arq_dados == NULL || arq_indice == NULL){
        msg_erro_Arq_Inexistente();
        printf("\n\n");
        if(arq_indice != NULL){
            fecharArquivo_bin(arq_indice);
        }
        if(arq_dados != NULL){
            fecharArquivo_bin(arq_dados);
        }
        free(nome_arq_indice);
        return;
    }

    //Le cabecalho do arquivo binario.
    RegistroCabecalho *cabecalhoCsv = lerRegistroCabecalhoArquivoBin(arq_dados);

    cabecalhoArvB *cabecalho;
    alocaCabecalhoArvB(&cabecalho);

    noArvB *raiz;
    alocaNoArvB(&raiz, 1);

    //Percorre arquivo de dados inteiro.
    for (int i = 0; i < *(cabecalhoCsv->proxRRN); i++)
    {   
        //Le dado do arquivo de dados por RRN.
        RegistroDados *reg = lerRegistroDadosArquivoBin_RRN(arq_dados, i);
        if (reg != NULL)
        {
            // imprimeRegistroDadosTela(reg);
            insercaoArvoreB(arq_indice, *(reg->idConecta), i, raiz, cabecalho);
            desalocaRegistrosDados(&reg, 1);
        }
    }

    //Desaloca memoria e fecha arquivos utilizados.
    desalocaNoArvB(&raiz, 1);
    escreveCabecalhoArqIndice(arq_indice, cabecalho);
    desalocaCabecalhoArvB(cabecalho);
    desalocaRegistrosCabecalho(cabecalhoCsv);

    fecharArquivo_bin(arq_indice);
    fclose(arq_dados);
    binarioNaTela(nome_arq_indice);
    free(nome_arq_indice);
}

void funcionalidade8SelectWhere(char *nome_arquivo) {
    //Numeros de buscas a serem realizadas
    int numBuscas;
    char *nome_arquivoArvB = malloc(sizeof(char)*20);
    scanf("%s %d", nome_arquivoArvB, &numBuscas);

    //Abre o arquivo de indice para leitura.
    FILE *arquivoArvB = abrirLeitura_bin(nome_arquivo);
    if (arquivoArvB == NULL)
    {
        msg_erro_Arq_Inconsistente();
        free(nome_arquivoArvB);
        return;
    }

    //Abre o arquivo de dados para leitura.
    FILE *arquivoBin = abrirLeitura_bin(nome_arquivo);
    if (arquivoBin == NULL)
    {
        msg_erro_Arq_Inconsistente();
        fecharArquivo_bin(arquivoArvB);
        free(nome_arquivo);
        return;
    }
    
    //Le o cabecalho do arquivo de indice.
    cabecalhoArvB *cabecalhoArvB = lecabecalhoArvB(arquivoArvB);

    //Le o cabecalho do arquivo de dados.
    RegistroCabecalho *cabecalhoArqvBin = lerRegistroCabecalhoArquivoBin(arquivoBin);

    //Le o no raiz da arvore B no arquivo de indice.
    noArvB *raiz = leNoArvB_RRN(arquivoArvB, *(cabecalhoArvB->noRaiz));

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

        //Variavel para a contagem de numero de paginas de dados acessadas.
        long nroPagDiscoAcessadas = 0;

        if(!strcmp(nome_campo, "idConecta")) {

            int RRN_dado = -1;

            //Busca a chave no arquivo de indice e soma a quantidade de paginas de disco acessadas.
            nroPagDiscoAcessadas += buscaChaveArvoreB(arquivoArvB, raiz, atoi(valor_campo), &RRN_dado);
            
            //Se foi encontrado o dado buscado no arquivo de incdice.
            if (RRN_dado != -1) {
                //Le o dado pelo RRN da chave encontrada.
                RegistroDados *dado = lerRegistroDadosArquivoBin_RRN(arquivoBin, RRN_dado);

                imprimeRegistroDadosTela(dado);
                printf("\n");

                desalocaRegistrosDados(&dado, 1);

                //Soma 3 paginas de disco acessadas, pois leu o cabecalho do indice, 
                //cabecalho do arquivo de dados e o dado em si no arquivo de dados.
                nroPagDiscoAcessadas += 3;
            } else  {
                //Se nao encontrar nenhum arquivo imprime mensagem de erro e quebra linha.
                msg_erro_Reg_Inexistente();
                printf("\n\n");
                //Soma 1 pagina de disco acessada, pois leu o cabecalho do indice.
                nroPagDiscoAcessadas += 1;
            }
        } else {
            //Se nao encontrar nenhum arquivo imprime mensagem de erro e quebra linha.
            if (buscaCampoImprimeArquivoDados(nome_campo, valor_campo, cabecalhoArqvBin, arquivoBin) == 0) {
                msg_erro_Reg_Inexistente();
                printf("\n\n");
            }
            //Numero de paginas de disco acessadas e a quantidade de paginas de 
            //disco existentes no arquivo de dados pois a busca eh feita por busca exaustiva.
            nroPagDiscoAcessadas = *(cabecalhoArqvBin->nroPagDisco);
        }

        printf("Numero de paginas de disco: %ld\n\n", nroPagDiscoAcessadas);
    }

    //Desaloca memoria e fecha os arruivos utilizados.
    desalocaNoArvB(&raiz, 1);
    desalocaCabecalhoArvB(cabecalhoArvB);
    desalocaRegistrosCabecalho(cabecalhoArqvBin);
    free(nome_arquivoArvB);
    free(nome_campo);
    free(valor_campo);
    fecharArquivo_bin(arquivoBin);
    fecharArquivo_bin(arquivoArvB);
}

void funcionalidade9InsertArvB(char *nome_arquivo)
{
    char *nome_arq_indice = malloc(sizeof(char) * 50);
    scanf("%s", nome_arq_indice);

    //Abre o arquivo de indice para leitura.
    FILE *arq_indice = abrirEscrita_bin(nome_arq_indice);
    FILE *arquivo = abrirEscrita_bin(nome_arquivo);

    if(arquivo == NULL || arq_indice == NULL){ // Erro arquivo inconsistente
        msg_erro_Arq_Inexistente();
        printf("\n\n");
        if(arq_indice != NULL){
            fecharArquivo_bin(arq_indice);
        }
        if(arquivo != NULL){
            fecharArquivo_bin(arquivo);
        }
        free(nome_arq_indice);
        return;
    }

    // Recebe quantidade de registros a serem inseridos
    int nro_reg;
    scanf("%d", &nro_reg);

    RegistroDados *registro;
    alocaRegistrosDados(&registro, 1);    

    //Le o arquivo de cabecalho do arquivo de dados.
    RegistroCabecalho *cabecalho = lerRegistroCabecalhoArquivoBin(arquivo);

    //Le o arquivo de cabecalho do arquivo de indice.
    cabecalhoArvB *cabecalhoArvB = lecabecalhoArvB(arq_indice);

    //Le o no raiz da arvore B no arquivo de indice.
    noArvB *raiz = leNoArvB_RRN(arq_indice, *(cabecalhoArvB->noRaiz));

    //Insere n registros
    for (int i = 0; i < nro_reg; i++)
    {
        //Le do teclado o registro a ser inserido.
        lerRegistroDadosTeclado(registro);
        int RRN_res_busca = -1;
        buscaChaveArvoreB(arq_indice,raiz, *(registro->idConecta), &RRN_res_busca); // Busca para impedir inserção duplicada
        if(RRN_res_busca == -1){
            int rrn_reg = inserirRegistroDadosArquivoBin(arquivo, cabecalho, registro);
            insercaoArvoreB(arq_indice, *(registro->idConecta), rrn_reg, raiz, cabecalhoArvB);
        }else{

        }
        
    }
    //Atualiza o cabecalho do arquivo de dados.
    escreverRegistroCabecalhoArquivoBin(arquivo, cabecalho);

    //Atualiza o cabecalho do arquivo de indice.
    escreveCabecalhoArqIndice(arq_indice, cabecalhoArvB);

    //Fecha arquivos.
    fecharArquivo_bin(arquivo);
    fecharArquivo_bin(arq_indice);

    binarioNaTela(nome_arquivo);
    binarioNaTela(nome_arq_indice);

    //Desaloca memoria utilizada.
    free(nome_arq_indice);
    desalocaCabecalhoArvB(cabecalhoArvB);
    if (raiz != NULL)
    {
        desalocaNoArvB(&raiz, 1);
    }
    desalocaRegistrosCabecalho(cabecalho);
    desalocaRegistrosDados(&registro, 1);
}

void funcionalidade10Juncao(char *nome_arquivo1) {
    //Aloca memoria para nomes de arquivos e campos da junacao
    char *nome_arquivo2 = malloc(sizeof(char)*20);
    char *campo_arq1 = malloc(sizeof(char)*25);
    char *campo_arq2 = malloc(sizeof(char)*25);
    char *nome_indice_aqr2 = malloc(sizeof(char)*20);

    scanf("%s %s %s %s", nome_arquivo2, campo_arq1, campo_arq2, nome_indice_aqr2);

    //Verifica se a juncao esta sendo feita com o idPoPsConectado e idConecta, arquivo 1 e arquivo 2 respectivamente.
    if(strcmp(campo_arq1, "idPoPsConectado") && strcmp(campo_arq2, "idConecta")) {
        return;
    }

    //Abre arquivo binario de dados 1.
    FILE *arquivoBin1 = abrirLeitura_bin(nome_arquivo1);
    if (arquivoBin1 == NULL)
    {
        msg_erro_Arq_Inconsistente();
        return;
    }

    //Abre arquivo binario de dados 2.
    FILE *arquivoBin2 = abrirLeitura_bin(nome_arquivo2);
    if (arquivoBin2 == NULL)
    {
        msg_erro_Arq_Inconsistente();
        return;
    }

    //Abre arquivo binario de indice do arquivo binario de dados 2.
    FILE *arquivoArvB_arq2 = abrirLeitura_bin(nome_indice_aqr2);
    if (arquivoArvB_arq2 == NULL)
    {
        msg_erro_Arq_Inconsistente();
        return;
    }
    
    //Le cabecalho do arquivo de indice.
    cabecalhoArvB *cabecalhoArvB = lecabecalhoArvB(arquivoArvB_arq2);

    //Le cabecalho do arquivo de dados.
    RegistroCabecalho *cabecalhoArqvBin = lerRegistroCabecalhoArquivoBin(arquivoBin1);

    //Le o no raiz da arvore B no arquivo de indice.
    noArvB *raiz = leNoArvB_RRN(arquivoArvB_arq2, *(cabecalhoArvB->noRaiz));

    //Quantidade de dados encontrados no arquivo de indice.
    long nroDadosEncontrados = 0;

    //Verifica todos os RRNs do arquivo
    for (int i = 0; i < *(cabecalhoArqvBin->proxRRN); i++)
    {
        //Le um dado do arquivo de dados por RRN.
        RegistroDados *dado1 = lerRegistroDadosArquivoBin_RRN(arquivoBin1, i);
        RegistroDados *dado2;
        if (dado1 != NULL)
        {   
            int RRN_buscado = -1;

            //Se o idPoPsConectado do dado do registro de dados 1 não for nulo.
            if(*(dado1->idPoPsConectado) != -1) {
                buscaChaveArvoreB(arquivoArvB_arq2, raiz, *(dado1->idPoPsConectado), &RRN_buscado);
            }
            //Se foi encontrado o dado buscado no arquivo de incdice.
            if (RRN_buscado != -1)
            {   
                //Aumenta numero de dados encontrados.
                nroDadosEncontrados++; 

                //Le o dado do arquivo de dados pelo RRN da chave encontrada no arquivo de indice.
                dado2 = lerRegistroDadosArquivoBin_RRN(arquivoBin2, RRN_buscado);

                //Imprime na formataçao de juncao
                imprimeJuncaoRegistrosDados(dado1, dado2);
                printf("\n");

                desalocaRegistrosDados(&dado2, 1);
            }
        }

        desalocaRegistrosDados(&dado1, 1);
    }

    //Se nao foi encontrado nenhum dado.
    if(nroDadosEncontrados == 0) {
        msg_erro_Reg_Inexistente();
        printf("\n\n");
    }

    //Desaloca memoria e fecha os arruivos utilizados.
    desalocaCabecalhoArvB(cabecalhoArvB);
    desalocaNoArvB(&raiz, 1);
    desalocaRegistrosCabecalho(cabecalhoArqvBin);
    free(campo_arq1);
    free(campo_arq2);
    free(nome_arquivo2);
    free(nome_indice_aqr2);
    fecharArquivo_bin(arquivoBin1);
    fecharArquivo_bin(arquivoBin2);
    fecharArquivo_bin(arquivoArvB_arq2);
}