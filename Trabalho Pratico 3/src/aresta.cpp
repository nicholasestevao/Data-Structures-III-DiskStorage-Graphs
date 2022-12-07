#include "../headers/aresta.h"

Aresta::Aresta(int idPoPsConectado) {
    this->idPoPsConectado = idPoPsConectado;
}

Aresta::Aresta(int idPoPsConectado, double velocidade) {
    this->idPoPsConectado = idPoPsConectado;

    this->velocidade = velocidade;
}

int Aresta::getIdPopsConectado() const {
    return idPoPsConectado;
}

double Aresta::getVelocidade() const {
    return velocidade;
}

bool Aresta::operator == (const Aresta &other) const {
    bool r = false;
    if(this->idPoPsConectado == other.getIdPopsConectado()) {
        r = true;
    }
    return r;
}
        

bool Aresta::operator > (const Aresta &other) const {
    bool r = false;
    if(this->idPoPsConectado > other.getIdPopsConectado()) {
        r = true;
    }
    return r;
}

bool Aresta::operator >= (const Aresta &other) const {
    bool r = false;
    if(this->idPoPsConectado >= other.getIdPopsConectado()) {
        r = true;
    }    
    return r;
}

bool Aresta::operator < (const Aresta &other) const {
    bool r = false;
    if(this->idPoPsConectado < other.getIdPopsConectado()) {
        r = true;
    }
    return r;
}

bool Aresta::operator <= (const Aresta &other) const {
    bool r = false;
    if(this->idPoPsConectado <= other.getIdPopsConectado()) {
        r = true;
    }
    return r;
}