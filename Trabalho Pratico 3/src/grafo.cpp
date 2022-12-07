#include "../headers/grafo.h"

Grafo::Grafo() {
    this->vertices = new list<Vertice>();
    this->numVertices = 0;
}

Grafo::~Grafo() {
    delete vertices;
}

Vertice* Grafo::findVertice(int idConecta) const{
    Vertice buscado(idConecta);
    Vertice *resultado = nullptr;
    auto it = vertices->begin();
    while (it != vertices->end())
    {
        if ((*it) == buscado) {
            resultado = &(*it);
            break;
        } 
        it++;
    }
    return resultado;
}

list<Vertice> Grafo::getVertices() const {
    return *vertices;
}

int Grafo::getNumVertices() const {
    return this->numVertices;
}

void Grafo::insertVertice(Vertice vertice) {
    //auto it = vertices->begin();
    printf("inserindo:\n");
    for(auto it = this->getVertices().begin(); it != this->getVertices().end(); ++it){
        printf("oi\n");
        printf("Vertice: %d %s %s %s\n", it->getIdConcecta(), it->getNomePops(), it->getNomePais(), it->getSiglaPais());
        if((*it) == vertice) {
            break;
        } else if ((*it) > vertice) {
            this->vertices->insert(it, vertice);
            (this->numVertices)++;
            break;
        }
    }
    /*while (it != vertices->end())
    {
        printf("Vertice: %d %s %s %s\n", it->getIdConcecta(), it->getNomePops(), it->getNomePais(), it->getSiglaPais());
        if((*it) == vertice) {
            break;
        } else if ((*it) > vertice) {
            this->vertices->insert(it, vertice);
            (this->numVertices)++;
            break;
        }
        it++;
    }*/
    printf("saiu");

    /*if(it != vertices->end()) {
        vertices->push_back(vertice);
    }*/
}

void Grafo::imprimeGrafo(){
    auto it = vertices->begin();
    while (it != vertices->end())
    {
        printf("Vertice: %d %s %s %s\n", it->getIdConcecta(), it->getNomePops(), it->getNomePais(), it->getSiglaPais());
        list<Aresta> arestas = it->getArestas();
        auto it_arestas = arestas.begin();
        while (it_arestas != arestas.end())
        {
            printf("        Aresta: %d %f\n", it_arestas->getIdPopsConectado(), it_arestas->getVelocidade());
            
            it_arestas++;
        }
        it++;
    }

}

int Grafo::contaCiclos(){
    int ** visitados = (int **) malloc(sizeof(int *)*(g->getNumVertices()));
    for(int i = 0; i< g->getNumVertices(); i++){
        visitados[i] = (int *) malloc(sizeof(int)*2);
    }

    
    return 0;
}