#ifndef __ARESTA_CPP__
#define __ARESTA_CPP__

#include <iostream>
#include <string>

using std::string;

class Aresta {
    private:
        int idPoPsConectado;
        double velocidade;

    public:
        Aresta(int idPoPsConectado);
        Aresta(int idPoPsConectado, double velocidade, char unidadeMedida);

        int getIdPopsConectado() const;
        double getVelocidade() const;

        void setVelocidade_Unidade(double velocidade, char unidade); 

        bool operator == (const Aresta &other) const;
        bool operator > (const Aresta &other) const;
        bool operator >= (const Aresta &other) const;
        bool operator < (const Aresta &other) const;
        bool operator <= (const Aresta &other) const;

        /**
         * Converte a velocdade de conexão para Gb/s.
         * 
         * @param velocidade velocidade a ser convertida.
         * @param unidade da velocidade a ser convertida.
         * 
         * @return retorna a velocidade em Gp/s.
         */
        double converteVelocidadeMbps(double velocidade, char unidade);
};

#endif