#ifndef __ARESTA_CPP__
#define __ARESTA_CPP__

#include <iostream>

class Aresta {
    private:
        int idPoPsConectado;
        double velocidade;

    public:
        Aresta(int idPoPsConectado);
        Aresta(int idPoPsConectado, double velocidade);

        int getIdPopsConectado() const;
        double getVelocidade() const;

        bool operator == (const Aresta &other) const;
        bool operator > (const Aresta &other) const;
        bool operator >= (const Aresta &other) const;
        bool operator < (const Aresta &other) const;
        bool operator <= (const Aresta &other) const;
};

#endif