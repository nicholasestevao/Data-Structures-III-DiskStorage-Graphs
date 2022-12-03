#ifndef __GRAFO_CPP_
#define __GRAFO_CPP__

#include <iostream>

typedef struct
{
    int idPopsConectado;
    double velocidade;
    Aresta *proxAresta;
} Aresta;


typedef struct
{
    int idConecta;
    char *nomePoPs;
    char *nomePais;
    char *siglaPais;
    Aresta *aresta;
    Vertice *proxVertice;
} Vertice;




#endif