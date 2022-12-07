#ifndef __GRAFO_CPP__
#define __GRAFO_CPP__

#include <algorithm>
#include <iostream>
#include  <list>
#include "vertice.h"

using std::find;
using std::list;

class Grafo {
    private:
        list<Vertice*> vertices;
    public:
        Grafo();
        ~Grafo();
        
        Vertice* findVertice(int idConecta) const;
        list<Vertice*> getVertices() const;

        void insertVertice(Vertice* vertice);
        void imprimeGrafo();
};

#endif