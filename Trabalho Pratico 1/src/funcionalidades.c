#include "../headers/funcionalidades.h"

void funcionalidade2Select(char* nome_arquivo){
    FILE * arquivoBin = abrirLeitura_bin(nome_arquivo);
    RegistroCabecalho * cabecalho = lerRegistroCabecalhoArquivoBin(arquivoBin);
    RegistroDados * dados;
    for(int i = 0; i<*(cabecalho->proxRRN); i++){
        dados = lerRegistroDadosArquivoBin_RRN(arquivoBin,i);
        imprimeRegistroDadosTela(dados);
        desalocaRegistrosDados(&dados,1);
    }
    printf("Numero de paginas de disco: %d\n", cabecalho->nroPagDisco);
    desalocaRegistrosCabecalho(cabecalho);
    fclose(arquivoBin);
}