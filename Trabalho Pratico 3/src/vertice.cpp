#include "../headers/vertice.h"

Vertice::Vertice(int idConecta) {
    this->idConecta = new int;
    *(this->idConecta) = idConecta;

    this->nomePoPs = nullptr;
    this->nomePoPs = nullptr;
    this->siglaPais = nullptr;
    this->arestas = nullptr;
}

Vertice::Vertice(int idConecta, string nomePoPs, string nomePais, string siglaPais) {
    this->idConecta = new int;
    *(this->idConecta) = idConecta;

    this->nomePoPs = new string;
    *(this->nomePoPs) = nomePoPs;

    this->nomePoPs = new string;
    *(this->nomePais) = nomePais;

    this->siglaPais = new string;
    *(this->siglaPais) = siglaPais;

    this->arestas = new list<Aresta>;
}

Vertice::~Vertice() {
    delete idConecta;
    delete nomePoPs;
    delete nomePais;
    delete siglaPais;
    delete arestas;
}

Aresta* Vertice::findAresta(int idPoPsConectado) {
    Aresta buscado(idPoPsConectado);
    Aresta *resutldado = nullptr;
    auto it = arestas->begin();
    while (it != arestas->end())
    {
        if ((*it) == buscado) {
            resutldado = &(*it);
            break;
        } 
        it++;
    }
    return resutldado;
}

int Vertice::getIdConcecta() const {
    return *idConecta;
}

string Vertice::getNomePops() const {
    return *nomePoPs;
}

string Vertice::getNomePais() const {
    return *nomePais;
}

string Vertice::getSiglaPais() const {
    return *siglaPais;
}

list<Aresta> Vertice::getArestas() const {
    return *arestas;
}

void Vertice::insertAresta(Aresta aresta) {
    auto it = arestas->begin();
    while (it != arestas->end())
    {
        if((*it) == aresta) {
            break;
        } else if ((*it) > aresta) {
            this->arestas->insert(it, aresta);
            break;
        }
        it++;
    }

    if(it != arestas->end()) {
        arestas->push_back(aresta);
    }
}

bool Vertice::operator == (const Vertice &other) const {
    bool r = false;
    if(*(this->idConecta) == other.getIdConcecta()) {
        r = true;
    }
    return r;
}

bool Vertice::operator > (const Vertice &other) const {
    bool r = false;
    if(*(this->idConecta) > other.getIdConcecta()) {
        r = true;
    }
    return r;
}

bool Vertice::operator >= (const Vertice &other) const {
    bool r = false;
    if(*(this->idConecta) >= other.getIdConcecta()) {
        r = true;
    }
    return r;
}

bool Vertice::operator < (const Vertice &other) const {
    bool r = false;
    if(*(this->idConecta) < other.getIdConcecta()) {
        r = true;
    }
    return r;
}

bool Vertice::operator <= (const Vertice &other) const {
    bool r = false;
    if(*(this->idConecta) <= other.getIdConcecta()) {
        r = true;
    }
    return r;
}