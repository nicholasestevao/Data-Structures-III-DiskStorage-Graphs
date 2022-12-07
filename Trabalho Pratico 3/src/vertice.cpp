#include "../headers/vertice.h"

Vertice::Vertice(int idConecta) {
    this->idConecta = idConecta;
}

Vertice::Vertice(int idConecta, string nomePoPs, string nomePais, string siglaPais) {
    this->idConecta = idConecta;

    this->nomePoPs = nomePoPs;

    this->nomePais = nomePais;

    this->siglaPais = siglaPais;
}

Vertice::~Vertice() {
    if(!arestas.empty()) {
        for(auto it = arestas.begin(); it != arestas.end(); ++it) {
            delete (*it);
        }
    }
}

Aresta* Vertice::findAresta(int idPoPsConectado) {
    Aresta *resutldado = nullptr;
    if(!arestas.empty()) {
        Aresta buscado(idPoPsConectado);
        auto it = arestas.begin();
        while (it != arestas.end())
        {
            if ((*(*it)) == buscado) {
                resutldado = (*it);
                break;
            } 
            it++;
        }
    }
    return resutldado;
}

int Vertice::getIdConcecta() const {
    return idConecta;
}

string Vertice::getNomePoPs() const {
    return nomePoPs;
}

string Vertice::getNomePais() const {
    return nomePais;
}

string Vertice::getSiglaPais() const {
    return siglaPais;
}

list<Aresta*> Vertice::getArestas() const {
    return arestas;
}

void Vertice::insertAresta(Aresta *aresta) {
    if(!arestas.empty()) {
            for(auto it = arestas.begin(); it != arestas.end(); ++it){
                if((*(*it)) == *aresta) {
                    break;
                } else if ((*(*it)) > *aresta) {
                    arestas.insert(it, aresta);
                    break;
                }
            }
    } else {
        arestas.push_front(aresta);
    }
}

bool Vertice::operator == (const Vertice &other) const {
    bool r = false;
    if(this->idConecta == other.getIdConcecta()) {
        r = true;
    }
    return r;
}

bool Vertice::operator > (const Vertice &other) const {
    bool r = false;
    if(this->idConecta > other.getIdConcecta()) {
        r = true;
    }
    return r;
}

bool Vertice::operator >= (const Vertice &other) const {
    bool r = false;
    if(this->idConecta >= other.getIdConcecta()) {
        r = true;
    }
    return r;
}

bool Vertice::operator < (const Vertice &other) const {
    bool r = false;
    if(this->idConecta < other.getIdConcecta()) {
        r = true;
    }
    return r;
}

bool Vertice::operator <= (const Vertice &other) const {
    bool r = false;
    if(this->idConecta <= other.getIdConcecta()) {
        r = true;
    }
    return r;
}