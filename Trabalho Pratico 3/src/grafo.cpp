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
    Vertice *resultado = nullptr;
    if(!vertices.empty()) {
        Vertice buscado(idConecta);
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

int Grafo::findVerticeIndex(int idConecta) const{
    Vertice *resultado = nullptr;
    int i = 0;
    if(!vertices.empty()) {
        Vertice buscado(idConecta);
        auto it = vertices.begin();
        while (it != vertices.end())
        {
            if ((*(*it)) == buscado) {
                resultado = (*it);
                break;
            } 
            it++;
            i++;
        }
    }
    return i;
}

int Grafo::totalArestas() const{
    Vertice *resultado = nullptr;
    int total = 0;
    if(!vertices.empty()) {
        auto it = vertices.begin();
        while (it != vertices.end())
        {
            total +=(*it)->getArestas().size();
            it++;
        }
    }
    return total;
}

list<Vertice*> Grafo::getVertices() const {
    return vertices;
}

void Grafo::insertVertice(Vertice* vertice) {
    auto it = vertices.begin();
    bool flagInseriu = false;
    if(!vertices.empty()) {
        for(it; it != vertices.end(); ++it){
            if((*(*it)) == *vertice) {
                break;
            } else if ((*(*it)) > *vertice) {
                vertices . insert(it, vertice);   
                flagInseriu = true;             
                break;
            }
        }
        if( !flagInseriu){
            vertices.insert(it, vertice); 
        }  
    } else {
        vertices.push_front(vertice);
    }
    
}

void Grafo::imprimeGrafo(){
    auto it = vertices.begin();
    while (it != vertices.end())
    {
        //std::cout << (*it)->getIdConcecta() << " " << (*it)->getNomePoPs() << " " << (*it)->getNomePais() << " " << (*it)->getSiglaPais() << std::endl;
        list<Aresta*> arestas = (*it)->getArestas();
        auto it_arestas = arestas.begin();
        while (it_arestas != arestas.end())
        {
            //std::cout << "        Aresta: " << (*it_arestas)->getIdPopsConectado() << " " << (*it_arestas)->getVelocidade() << " Gbps" << std::endl;
            printf("%d %s %s %s %d %.0fMbps\n", (*it)->getIdConcecta(), (*it)->getNomePoPs().c_str(),(*it)->getNomePais().c_str(), (*it)->getSiglaPais().c_str(), (*it_arestas)->getIdPopsConectado(), (*it_arestas)->getVelocidade());
            it_arestas++;
        }
        it++;
    }
}

int Grafo::contaCiclos(){
    /*int ** visitados = (int **) malloc(sizeof(int *)*(this->getNumVertices()));
    for(int i = 0; i< this->getNumVertices(); i++){
        visitados[i] = (int *) malloc(sizeof(int)*2);
    }*/

    
    return 0;

}


void Grafo::buscaProfundidade(Grafo * g, int *** arv_busca, int id_vertice_atual, int id_vertice_pai, int *tempo, int * num_arestas_retorno, int * num_arestas_arvore){
    // ind 0 -> idConecta
    // ind 1 -> cor do vertice
            /*
                -1 -> branco
                1 -> cinza
                2 -> preto
            
            */
    // ind 2 -> tempo de descoberta
    // ind 3 -> tempo de termino
    // ind 4 -> numero de arestas de retorno
    Vertice vertice_atual = *(g->findVertice(id_vertice_atual));
    list<Aresta*> arestas = vertice_atual.getArestas();
    if(!arestas.empty()) {
            //printf("Vertice atual : %d\n", vertice_atual.getIdConcecta());
            if((*arv_busca)[g->findVerticeIndex(vertice_atual.getIdConcecta())][1] == -1){
                // Encontrou vertice que ainda nao foi descoberto (branco)
                //printf("Encontrou vertice branco (%d)\n",vertice_atual.getIdConcecta());
                (*arv_busca)[g->findVerticeIndex(vertice_atual.getIdConcecta())][0] = vertice_atual.getIdConcecta();
                (*arv_busca)[g->findVerticeIndex(vertice_atual.getIdConcecta())][1] = 1; // cinza
                (*arv_busca)[g->findVerticeIndex(vertice_atual.getIdConcecta())][2] = *tempo;
            }  

            /*list<Aresta*> arestas2 = vertice_atual.getArestas();
            auto it_arestas = arestas2.begin();
            while (it_arestas != arestas2.end())
            {
                printf("%d ", (*it_arestas)->getIdPopsConectado());
                it_arestas++;
            }
            printf("\n");*/

            //Lista de vertices
            list<Vertice*> vertices = g->getVertices();
            auto it = arestas.begin();
            for(it; it != arestas.end(); ++it){
                int idPoPs = (*it)->getIdPopsConectado();
                if(idPoPs != id_vertice_pai){
                    (*tempo)++;
                    //int idVerticePoPs = idPoPs - menorIdConecta;
                    int idVerticePoPs = g->findVerticeIndex(idPoPs);
                    //printf("    Passou pela aresta %d <-> %d    (id na lista: %d)\n", vertice_atual.getIdConcecta(), idPoPs,idVerticePoPs);
                    // indo no vertice idPoPs verificar

                    if((*arv_busca)[idVerticePoPs][1] == 2){
                        //Encontrou vertice preto -> vai para proxima aresta
                        //printf("Encontrou vertice preto\n");
                        //break;
                    }else if((*arv_busca)[idVerticePoPs][1] == 1){
                        // Encontrou vertice cinza
                        (*num_arestas_retorno)++;
                        //printf("Encontrou vertice cinza (%d)\n",idPoPs);
                        //vai para proxima aresta
                        //break;
                    }else{
                        if((*arv_busca)[idVerticePoPs][1] == -1){
                            // Encontrou vertice que ainda nao foi descoberto (branco)
                            //printf("Encontrou vertice branco (%d)\n",idPoPs);
                            (*arv_busca)[idVerticePoPs][0] = idPoPs;
                            (*arv_busca)[idVerticePoPs][1] = 1; // cinza
                            (*arv_busca)[idVerticePoPs][2] = *tempo;
                        }   
                        g->buscaProfundidade(g,arv_busca, idPoPs, vertice_atual.getIdConcecta(), tempo, num_arestas_retorno, num_arestas_arvore);
                        //printf("Vertice atual voltou a ser: %d\n", vertice_atual.getIdConcecta());
                    }               
                }else{
                    //printf("    Ignorou aresta     %d <-> %d (vem do no pai)\n", vertice_atual.getIdConcecta(), idPoPs);                    
                }              
            }
            //printf("Testou todas as arestas do vertice %d\n", vertice_atual.getIdConcecta());
            (*arv_busca)[g->findVerticeIndex(vertice_atual.getIdConcecta())][1] = 2;   
            //printf("Vertice %d se tornou preto\n", vertice_atual.getIdConcecta());
            (*arv_busca)[g->findVerticeIndex(vertice_atual.getIdConcecta())][3] = *tempo; 

    }
}