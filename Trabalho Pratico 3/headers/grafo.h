#ifndef __GRAFO_C__
#define __GRAFO_C__

#include <stdlib.h>

typedef struct
{
    int idPopsConectado;
    double velocidade;
    Aresta * proxAresta;
} Aresta;


typedef struct
{
    int idConecta;
    char * nomePoPs;
    char * nomePais;
    char * siglaPais;
    Aresta * aresta;
    Vertice * proxVertice;
} Vertice;




#endif