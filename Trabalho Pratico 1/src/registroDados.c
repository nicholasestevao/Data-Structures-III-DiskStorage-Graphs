#include "../headers/registroDados.h"

void  alocaRegistrosDados(RegistroDados ** registros, int numReg){

    for(int i = 0; i < numReg; i++) {
        (registros[i])->removido = malloc(sizeof(int) * 1);
        (registros[i])->encadeamento = malloc(sizeof(int) * 1);
        (registros[i])->idConecta = malloc(sizeof(int) * 1);
        (registros[i])->siglaPais = malloc(sizeof(char) * 2);
        (registros[i])->idPoPsConectado = malloc(sizeof(int) * 1);
        (registros[i])->unidadeMedida = malloc(sizeof(char) * 1);
        (registros[i])->velocidade = malloc(sizeof(int) * 1);
        (registros[i])->nomePoPs = malloc(sizeof(char) * 38);
        (registros[i])->nomePais = malloc(sizeof(char) * 38);
    }    
}

void desalocaRegistrosDados(RegistroDados ** registros, int numReg) {
    for(int i = 0; i < numReg; i++) {
        free((registros[i])->removido);
        free((registros[i])->encadeamento);
        free((registros[i])->idConecta);
        free((registros[i])->siglaPais);
        free((registros[i])->idPoPsConectado);
        free((registros[i])->unidadeMedida);
        free((registros[i])->velocidade);
        free((registros[i])->nomePoPs);
        free((registros[i])->nomePais);
    }    
}