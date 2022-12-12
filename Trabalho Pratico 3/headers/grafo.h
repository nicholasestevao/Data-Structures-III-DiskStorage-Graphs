#ifndef __GRAFO_CPP__
#define __GRAFO_CPP__

#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <list>
#include <utility>
#include <vector>

#include "arquivoBin.h"
#include "arvoreB.h"
#include "funcionalidades.h"
#include "vertice.h"

using std::invalid_argument;
using std::find;
using std::list;
using std::pair;
using std::vector;


//debug
using std::cout;
using std::endl;

/**
 * Classe grafo.
 */
class Grafo {
    private:
        /**
         * Lista encadeada de ponteiro de Vertices.
         */
        list<Vertice*> vertices;

        /**
         * Encontra o menor vertice aberto no vetor de par(status, distancia), 
         * buscando pela menor distancia entre os pares com status aberto('O').
         * 
         * @param d Vetor de par(status, distancia).
         * @param tam Tamanho desse vetor.
         * 
         * @return Retorna o indice(posicao relativa), do menor vertice aberto,
         * no vetor de par. Caso nao haja um menor vertice aberto retorna -1.
         */
        int findSmallestVerticeOpen (vector<pair<char, double>> &d, int &tam) const;

        /**
         *  Imprime na tela todos os vertices abertos no vetor de par(status, distancia).
         * 
         * @param d Vetor de par(status, distancia).
         * @param tam Tamanho desse vetor.
         */
        void imprimeTodosVerticesAbertos(vector<pair<char, double>> &d, int &tam) const;

    public:
        /**
         * Constroi o grafo a partir de um aqruivo binario de dados
         * (criado pela funcionalidade 1), recuperando os dados todos
         * os dados não removidos por RRN e os inserindo no grafo.
         * 
         * @param nome_aqruivo Nome do aqruivo binario.
         */    
        Grafo(char *nome_arquivo);

        /**
         * Destroi o grafo. Percorrendo todos os vertices e os destruindo. 
         */
        ~Grafo();
        
        /**
         * 
         * 
         * @param arv_busca
         * @param id_vertice_atual
         * @param id_vertice_pai
         * @param tempo
         * @param num_arestas_retorno
         * @param num_arestas_arvore
         */
        void buscaProfundidade(int *** arv_busca, int id_vertice_atual, int id_vertice_pai, int * tempo, int * num_arestas_retorno, int * num_arestas_arvore);
        
        /**
         * Encontra o indice(posicao relativa) de um vertice na lista
         * encadeada bucando pelo idConecta.
         * 
         * @param idConecta ID do Vertice buscado.
         * 
         * @return Retorna o indice(posicao relatica), do vertice buscado, 
         * na lista encadeada. Caso nao encontre retorna -1.
         */
        int findIndexVertice(int idConecta) const;

        /**
         * Encontra um vertice buscando pelo seu id.
         * 
         * @param idConecta ID do vertice buscado.
         * 
         * @return Retorna o vertice buscado caso ele exista. E caso 
         * nao exista retorna null_ptr.
         */
        Vertice* findVertice(int idConecta) const;
        
        /**
         * Recupera vertice pela posicao relativa na lista encadeada.
         * 
         * @param index Posicao do vertice. 
         * 
         * @return Retorna ponteiro para o vertice caso o index possua 
         * uma posicao valida. Caso o index possua uma posicao invalida 
         * retorna null_ptr.
         */
        Vertice* getVertice(int index) const;

        /**
         * Pega todos os vertices inseridos no grafo.
         * 
         * @return Retorna uma lista de ponteiro de Vertice com todos 
         * os vertices inseridos no grado ate o momento da execucao desse 
         * metodo.
         */
        list<Vertice*> getVertices() const;
        
        /**
         * Calcula o fluxo maximo entre dois vertices (vertice de partida 
         * e vertice de chagada). O fluxo maximo eh dado pela menor velocidade
         * de conexao no caminho entre dois vertices. 
         * 
         * @param id_Partida ID do vertice de partida.
         * @param id_Chegada ID do vertice de chegada.
         * 
         * @return Retorna o fluxo maximo entre o verice de partida e de chegada.
         * caso nao exista uma conexao entre esses dois vertices retorna -1.
         */
        double fluxoMaxEntreVertices(int id_Partida, int id_Chegada) const;
        
        /**
         * Insere um vertice no grafo.
         * 
         * @param vertice Vertice a ser inserido.
         */
        void insertVertice(Vertice* vertice);
        
        /**
         * Imprime na tela o grafo inteiro.
         */
        void imprimeGrafo() const;
        
        /**
         * Calcula a menor distancia entre dois vertices (vertice de partida 
         * e vertice de chagada). A menor distancia se da pelo menor soma de
         * velocidades de um caminho entre dois vertices.
         * 
         * @param id_Partida ID do vertice de partida.
         * @param id_Chegada ID do vertice de chegada.
         * 
         * @return Retorna a menor distancia entre o verice de partida e de chegada.
         * caso nao exista uma conexao entre esses dois vertices retorna -1.
         */
        double menorDistanciaEntreVertices(int id_Partida, int id_Chegada) const;

};

#endif