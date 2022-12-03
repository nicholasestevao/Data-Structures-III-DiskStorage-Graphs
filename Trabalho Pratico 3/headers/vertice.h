#ifndef __VERTICE_CPP__
#define __VERTICE_CPP__

#include <iostream>
#include "aresta.h"

class Vertice
{   
    private:
        int *idConecta;
        char *nomePoPs;
        char *nomePais;
        char *siglaPais;
        Aresta *aresta;
        Vertice *proxVertice;

    public:
     Vertice();
     ~Vertice();
};

#endif