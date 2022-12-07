#include "../headers/aresta.h"

Aresta::Aresta(int idPoPsConectado) {
    this->idPoPsConectado = idPoPsConectado;
}

Aresta::Aresta(int idPoPsConectado, double velocidade, char unidadeMedida) {
    this->idPoPsConectado = idPoPsConectado;
    this->velocidade = this->converteVelocidadeGbps(velocidade, unidadeMedida);
}

double Aresta::converteVelocidadeGbps(double velocidade, char unidade) {
    double r = velocidade;
    switch (unidade)
    {   
        //unidade nula
        case ' ':
            r *= 0.000000000931322574615478515625;
            break;
    
        case 'K':
            r *= 0.00000095367431640625;
            break;

        case 'M':
            r *= 0.0009765625;
            break;
        
        case 'G':
            break;

        case 'T':
            r *= 1024;
            break;
    }
    return r;
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