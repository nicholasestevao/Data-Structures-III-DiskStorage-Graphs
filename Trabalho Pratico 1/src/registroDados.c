#include "../headers/registroDados.h"

void  alocaRegistrosDados(RegistroDados ** registros, int numReg){
    *registros = malloc(sizeof(RegistroDados)*numReg); 
    for(int i = 0; i < numReg; i++) {
         (*registros)[i].removido = malloc(sizeof(char) * 1);
         (*registros)[i].encadeamento = malloc(sizeof(int) * 1);
         (*registros)[i].idConecta = malloc(sizeof(int) * 1);
         (*registros)[i].siglaPais = malloc(sizeof(char) * 2);
         (*registros)[i].idPoPsConectado = malloc(sizeof(int) * 1);
         (*registros)[i].unidadeMedida = malloc(sizeof(char) * 1);
         (*registros)[i].velocidade = malloc(sizeof(int) * 1);
         (*registros)[i].nomePoPs = malloc(sizeof(char) * 45);
         (*registros)[i].nomePais = malloc(sizeof(char) * 45);
    }    
}

void desalocaRegistrosDados(RegistroDados ** registros, int numReg) {
    for(int i = 0; i < numReg; i++) {
        free( (*registros)[i].removido);
        free( (*registros)[i].encadeamento);
        free( (*registros)[i].idConecta);
        free( (*registros)[i].siglaPais);
        free( (*registros)[i].idPoPsConectado);
        free( (*registros)[i].unidadeMedida);
        free( (*registros)[i].velocidade);
        free( (*registros)[i].nomePoPs);
        free( (*registros)[i].nomePais);
    }    
    free(*registros);
}

void imprimeRegistroDadosTela(RegistroDados * registro) {
    printf("Identificador do ponto: %d\n", *(registro->idConecta));
    printf("Nome do ponto: %s\n", registro->nomePoPs);
    printf("Pais de localizacao: %s\n", registro->nomePais);
    printf("Sigla do pais: %s\n", registro->siglaPais);
    printf("Identificador do ponto conectado: %d\n", *(registro->idPoPsConectado));
    if(registro->unidadeMedida == "$") {
        printf("Velocidade de transmissao: %d bps\n", *(registro->velocidade));
    } else {
        printf("Velocidade de transmissao: %d %cbps\n", *(registro->velocidade), *(registro->unidadeMedida));
    }
}