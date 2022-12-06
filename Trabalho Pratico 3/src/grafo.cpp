#include "grafo.h"

Grafo::Grafo() {
    this->vertices = new list<Vertice>;
}

Grafo::~Grafo() {
    delete vertices;
}

Vertice* Grafo::findVertice(int idConecta) const{
    Vertice buscado(idConecta);
    Vertice *resutldado = nullptr;
    auto it = vertices->begin();
    while (it != vertices->end())
    {
        if ((*it) == buscado) {
            resutldado = &(*it);
            break;
        } 
        it++;
    }
    return resutldado;
}

list<Vertice> Grafo::getVerices() const {
    return *vertices;
}

void Grafo::insertVertice(Vertice vertice) {
    auto it = vertices->begin();
    while (it != vertices->end())
    {
        if((*it) == vertice) {
            break;
        } else if ((*it) > vertice) {
            this->vertices->insert(it, vertice);
            break;
        }
        it++;
    }

    if(it != vertices->end()) {
        vertices->push_back(vertice);
    }
}