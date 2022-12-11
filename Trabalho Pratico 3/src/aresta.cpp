#include "../headers/aresta.h"

Aresta::Aresta(int idPoPsConectado) {
    this->idPoPsConectado = idPoPsConectado;
}

Aresta::Aresta(int idPoPsConectado, double velocidade, char unidadeMedida) {
    this->idPoPsConectado = idPoPsConectado;
    if(velocidade != -1) {
        this->velocidade = this->converteVelocidadeGbps(velocidade, unidadeMedida);
    } else {
        this->velocidade = 0;
    }
}

double Aresta::converteVelocidadeGbps(double velocidade, char unidade) {
    double r = velocidade;
    switch (unidade)
    {   
        //unidade nula
        case ' ':
            r *= 0.00000095367431640625;
            break;
    
        case 'K':
            r *= 0.0009765625 ;
            break;

        case 'M':
            break;
        
        case 'G':
            r *= 1024;
            break;

        case 'T':
            r *= 1048576;
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