#ifndef __ARESTA_CPP__
#define __ARESTA_CPP__

#include <iostream>

class Aresta
{
    private:
        int *idPopsConectado;
        double *velocidade;
        Aresta *proxAresta;
    public:
        Aresta(/* args */);
        ~Aresta();
};

#endif