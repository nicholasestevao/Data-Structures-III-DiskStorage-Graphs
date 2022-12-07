#include "../headers/grafo.h"

Grafo::Grafo() {
}

Grafo::~Grafo() {
    if(!vertices.empty()) {
        for(auto it = vertices.begin(); it != vertices.end(); ++it) {
            delete (*it);
        }
    }
}

Vertice* Grafo::findVertice(int idConecta) const{
    Vertice buscado(idConecta);
    Vertice *resultado = nullptr;
    if(!vertices.empty()) {
        auto it = vertices.begin();
        while (it != vertices.end())
        {
            if ((*(*it)) == buscado) {
                resultado = (*it);
                break;
            } 
            it++;
        }
    }
    return resultado;
}

list<Vertice*> Grafo::getVertices() const {
    return vertices;
}

void Grafo::insertVertice(Vertice* vertice) {
    //auto it = vertices->begin();
    if(!vertices.empty()) {
        for(auto it = vertices.begin(); it != vertices.end(); ++it){
            if((*(*it)) == *vertice) {
                break;
            } else if ((*(*it)) > *vertice) {
                vertices . insert(it, vertice);
                break;
            }
        }
    } else {
        vertices.push_back(vertice);
    }
}

void Grafo::imprimeGrafo(){
    auto it = vertices.begin();
    while (it != vertices.end())
    {
        std::cout << (*it)->getIdConcecta() << " " << (*it)->getNomePoPs() << " " << (*it)->getNomePais() << " " << (*it)->getSiglaPais() << std::endl;
        list<Aresta*> arestas = (*it)->getArestas();
        auto it_arestas = arestas.begin();
        while (it_arestas != arestas.end())
        {
            std::cout << "        Aresta: " << (*it_arestas)->getIdPopsConectado() << " " << (*it_arestas)->getVelocidade() << " Gbps" << std::endl;
            
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