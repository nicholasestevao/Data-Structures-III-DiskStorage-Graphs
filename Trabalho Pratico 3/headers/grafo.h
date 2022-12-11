#ifndef __GRAFO_CPP__
#define __GRAFO_CPP__

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <list>
#include <utility>
#include <vector>

#include "arquivoBin.h"
#include "arvoreB.h"
#include "funcionalidades.h"
#include "vertice.h"

using std::invalid_argument;
using std::find;
using std::list;
using std::pair;
using std::vector;


//debug
using std::cout;
using std::cin;
using std::endl;

class Grafo {
    private:
        list<Vertice*> vertices;
        Vertice* getVertice(int index) const;
        int findIndexVertice(int idConecta) const;
        int findSmallestVerticeOpen (vector<pair<char, double>> &d, int &tam) const;
        void imprimeTodosVerticesAbertos(vector<pair<char, double>> &d, int &tam) const;
    public:    
        Grafo(char *nome_arquivo);
        ~Grafo();
        
        Vertice* findVertice(int idConecta) const;
        list<Vertice*> getVertices() const;

        double fluxoMaxEntreVertices(int id_Partida, int id_Chegada) const;
        void insertVertice(Vertice* vertice);
        void imprimeGrafo() const;
        int contaCiclos();
        double menorDistanciaEntreVertices(int id_Partida, int id_Chegada) const;  

};

#endif