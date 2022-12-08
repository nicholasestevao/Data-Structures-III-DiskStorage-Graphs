#ifndef __VERTICE_CPP__
#define __VERTICE_CPP__

#include <algorithm>
#include <iostream>
#include  <list>
#include "aresta.h"

using std::find;
using std::list;
using std::string;

class Vertice {   
    private:
        int idConecta;
        string nomePoPs;
        string nomePais;
        string siglaPais;
        list<Aresta*> arestas;

    public:
        Vertice(int idConecta);
        Vertice(int idConecta, string nomePoPs, string nomePais, string siglaPais);
        ~Vertice();
        
        Aresta* findAresta(int idPoPsConectado);

        int getIdConcecta() const;
        string getNomePoPs() const;
        string getNomePais() const;
        string getSiglaPais() const;
        void setNomePoPs(string nomePoPs);
        void setNomePais(string nomePais);
        void setSiglaPais(string siglaPais);
        list<Aresta*> getArestas() const;

        void insertAresta(Aresta *aresta);

        bool operator == (const Vertice &other) const;
        bool operator > (const Vertice &other) const;
        bool operator >= (const Vertice &other) const;
        bool operator < (const Vertice &other) const;
        bool operator <= (const Vertice &other) const;
};

#endif