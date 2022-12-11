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
        int findVerticeIndex(int idConecta) const;
        list<Vertice*> getVertices() const;

        void insertVertice(Vertice* vertice);
        void imprimeGrafo();
        int contaCiclos();
        int totalArestas() const;
        void buscaProfundidade(Grafo * g, int *** arv_busca, int id_vertice_atual, int id_vertice_pai, int * tempo, int * num_arestas_retorno, int * num_arestas_arvore);
};

#endif