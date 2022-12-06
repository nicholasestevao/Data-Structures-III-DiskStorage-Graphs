#include "../headers/aresta.h"

Aresta::Aresta(int idPoPsConectado) {
    this->idPoPsConectado = new int;
    *(this->idPoPsConectado) = idPoPsConectado;

    this->velocidade = nullptr;
}

Aresta::Aresta(int idPoPsConectado, double velocidade) {
    this->idPoPsConectado = new int;
    *(this->idPoPsConectado) = idPoPsConectado;

    this->velocidade = new double;
    *(this->velocidade) = velocidade;
}

Aresta::~Aresta() {
    delete idPoPsConectado;
    delete velocidade;
}

int Aresta::getIdPopsConectado() const {
    return *idPoPsConectado;
}

double Aresta::getVelocidade() const {
    return *velocidade;
}

bool Aresta::operator == (const Aresta &other) const {
    bool r = false;

    return r;
}
        

bool Aresta::operator > (const Aresta &other) const {
    bool r = false;

    return r;
}

bool Aresta::operator >= (const Aresta &other) const {
    bool r = false;

    return r;
}

bool Aresta::operator < (const Aresta &other) const {
    bool r = false;

    return r;
}

bool Aresta::operator <= (const Aresta &other) const {
    bool r = false;

    return r;
}