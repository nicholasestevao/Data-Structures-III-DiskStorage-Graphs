#include "../headers/mensagens.h"

void config_mensagens() {
    char *ret = setlocale(LC_ALL, "Portuguese_Brazil");
    printf("%s", ret);
}

void msg_erro_Arq_FalhaCriacao()
{
    printf("Falha no processamento do arquivo.");
}

void msg_erro_Arq_Inconsistente()
{
    printf("Falha no processamento do arquivo.");
}

void msg_erro_falha_funcionalidade()
{
    printf("Falha na execução da funcionalidade.");
}

void msg_erro_Arq_Inexistente()
{
    printf("Falha no processamento do arquivo.");
}

void msg_erro_RRN_Invalido()
{
    printf("Nao foi possivel ler o arquivo.");
}

void msg_erro_Reg_Inexistente()
{
    printf("Registro inexistente.");
}
