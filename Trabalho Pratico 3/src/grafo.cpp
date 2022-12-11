#include "../headers/grafo.h"

Grafo::Grafo(char *nome_arquivo) {
    FILE *arq_bin = abrirLeitura_bin(nome_arquivo);
    if (arq_bin != NULL) {
        RegistroCabecalho *cabecalho = lerRegistroCabecalhoArquivoBin(arq_bin);

        //Arquivo de Indice
        funcionalidade7CreateIndex(nome_arquivo, (char*) "indice.bin");
        FILE* arquivoArvB = abrirLeitura_bin((char*)  "indice.bin");
        CabecalhoArvB *cabecalhoIndice = lecabecalhoArvB(arquivoArvB);
        NoArvB *raiz = leNoArvB_RRN(arquivoArvB, *(cabecalhoIndice->noRaiz));

        for (unsigned int i = 0; i < *(cabecalho->proxRRN); i++)
        {
            RegistroDados *dados_A = lerRegistroDadosArquivoBin_RRN(arq_bin, i);
            
            if (dados_A != NULL && *(dados_A->idPoPsConectado) != -1)
            {
                // Registro nao removido
                Vertice *vertice_A = this->findVertice(*(dados_A->idConecta));
                if(vertice_A == nullptr){
                    //vertice nao existe ainda
                    vertice_A = new Vertice(*(dados_A->idConecta), dados_A->nomePoPs, dados_A->nomePais, dados_A->siglaPais);
                    
                    this->insertVertice(vertice_A);
                }
                //vertice ja existe
                if(*(dados_A->idPoPsConectado) != -1) {
                    vertice_A->insertAresta(new Aresta(*(dados_A->idPoPsConectado), *(dados_A->velocidade), (dados_A->unidadeMedida)[0]));
                }
                

                // Inserindo no outro vertice (pois o grafo é nao direcionado)
                

                Vertice *vertice_B = this->findVertice(*(dados_A->idPoPsConectado));
                if(vertice_B == nullptr){
                    //vertice nao existe ainda
                    int RRN_vertice_B = -1;
                    buscaChaveArvoreB(arquivoArvB, raiz, *(dados_A->idPoPsConectado), &RRN_vertice_B);
                    if(RRN_vertice_B != -1){
                        RegistroDados *dados_B = lerRegistroDadosArquivoBin_RRN(arq_bin, RRN_vertice_B);
                        //printf(" Criou vertice b: %d para conectar com %d\n", *(dados_B->idConecta),*(dados_A->idConecta) );
                        vertice_B = new Vertice(*(dados_B->idConecta), dados_B->nomePoPs, dados_B->nomePais, dados_B->siglaPais);
                        this->insertVertice(vertice_B);
                        desalocaRegistrosDados(&dados_B, 1);
                    }             
                }else{
                        //printf("Foi no vertice b: %d para conectar com %d\n",  vertice_B->getIdConcecta(),*(dados_A->idConecta) );
                    } 
                //vertice ja existe
                vertice_B->insertAresta(new Aresta(*(dados_A->idConecta), *(dados_A->velocidade), (dados_A->unidadeMedida)[0]));
                
                desalocaRegistrosDados(&dados_A, 1);
            }
        }
        desalocaRegistrosCabecalho(cabecalho);
        fecharArquivo_bin(arq_bin);
    } else {
        throw invalid_argument("");
    } 
}

Grafo::~Grafo() {
    if(!vertices.empty()) {
        for(auto it = vertices.begin(); it != vertices.end(); ++it) {
            delete (*it);
        }
    }
}

int Grafo::findIndexVertice(int idConecta) const {
    int retorno = -1;
    if(!vertices.empty()) {
        Vertice buscado(idConecta);
        int indice = -1;
        for(auto it = vertices.begin(); it != vertices.end(); it++) {
            indice++;
            if((*(*it)) == buscado) {
                retorno = indice;
                break;
            }  
        }
    }
    return retorno;
}

int Grafo::findSmallestVerticeOpen(vector<pair<char, double>> &d, int &tam) const {
    int r = -1;
    double coust = INFINITY;
    for(int i = 0; i < tam; i++) {
        if ((d[i].first == 'O') && (coust > d[i].second)) {
            coust = d[i].second;
            r = i;
        }
    }
    return r;
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

double Grafo::fluxoMaxEntreVertices(int id_Partida, int id_Chegada) const {
    double r = -1;
    if((findIndexVertice(id_Partida) != -1) && (findIndexVertice(id_Chegada) != -1)) {
        int tam = vertices.size();
        vector<pair<char, double>> *d = new vector<pair<char, double>>(tam, pair<char, double>('O', INFINITY));
        int qnt_open = tam;
        vector<int> *p = new vector<int>(tam, -1);

        int actual_index = findIndexVertice(id_Partida);
        (*d)[actual_index] = pair<char, double>('O', 0);
        while (qnt_open > 0) {
            actual_index = findSmallestVerticeOpen((*d), tam);
            if(actual_index == -1) {
                //cout << "Actual_Index: " << actual_index << endl;
                //cout << "   Qauntidade abertos: " << qnt_open << endl;
                //imprimeTodosVerticesAbertos((*d), tam);
                break;
            }
            (*d)[actual_index].first = 'C';
            qnt_open--;
            Vertice *actual_vertice = getVertice(actual_index);
            int actual_index_id = actual_vertice->getIdConcecta();
            //cout << "======================" << endl;
            //cout << "Menor custo: " << (*d)[actual_index].second <<" - Indice: " << actual_index << " ID: " << actual_vertice->getIdConcecta() << endl;
            list<Aresta*> actual_arestas = actual_vertice->getArestas();
            for(auto it_ar = actual_arestas.begin(); it_ar != actual_arestas.end(); it_ar++) {
                int sub_index = findIndexVertice((*it_ar)->getIdPopsConectado());
                //cout << "   Sub_Index: " << sub_index << " ID: " << (*it_ar)->getIdPopsConectado() << " - Custo: " << (*d)[sub_index].second  << endl;
                if(((*d)[sub_index].second > (*it_ar)->getVelocidade())) {
                    double coust = (*it_ar)->getVelocidade(); 
                    if((actual_index_id != id_Partida) && ((*it_ar)->getVelocidade() > (*d)[actual_index].second)) {
                        coust = (*d)[actual_index].second;
                    }
                    //cout << "       (" << (*d)[actual_index].second << " || " << (*it_ar)->getVelocidade() << ") ? " << " -> " << coust << endl;
                    //cout << "*     " << (*d)[sub_index].second << " > " << (*it_ar)->getVelocidade() << endl;
                    //cout << "       Substituiu " << (*d)[sub_index].second;
                    (*d)[sub_index].second = coust;
                    //cout << " por " << (*d)[sub_index].second << endl;
                }
            }
        }
        actual_index = findIndexVertice(id_Chegada);
        if((*d)[actual_index].second != INFINITY) {
            r = (*d)[actual_index].second;
        }

        delete d;
        delete p;
    }
    return r;
}

Vertice* Grafo::getVertice(int index) const {
    Vertice *r = nullptr;
    auto it = vertices.begin();
    if(!vertices.empty()) {
        for(int i = 0; i < index; i++) {
            if(it != vertices.end()) {
                it++;
            }
        }
        r = (*it);
    }
    return r;
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
        for(; it != vertices.end(); ++it){
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

void Grafo::imprimeGrafo() const {
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

void Grafo::imprimeTodosVerticesAbertos(vector<pair<char, double>> &d, int &tam) const {
    for(int i = 0; i < tam; i++) {
        if((d[i]).first == 'O') {
            Vertice *v = getVertice(i);
            cout << "       Index: " << i << " (" << (d[i]).first << ", " << (d[i]).second << ") - ID: " << v->getIdConcecta()  << endl;
        }
    }
}

int Grafo::contaCiclos(){
    /*int ** visitados = (int **) malloc(sizeof(int *)*(this->getNumVertices()));
    for(int i = 0; i< this->getNumVertices(); i++){
        visitados[i] = (int *) malloc(sizeof(int)*2);
    }*/

    
    return 0;

}

double Grafo::menorDistanciaEntreVertices(int id_Partida, int id_Chegada) const {
    double r = -1;
    if((findIndexVertice(id_Partida) != -1) && (findIndexVertice(id_Chegada) != -1)) {
        int tam = vertices.size();
        vector<pair<char, double>> *d = new vector<pair<char, double>>(tam, pair<char, double>('O', INFINITY));
        int qnt_open = tam;
        vector<int> *p = new vector<int>(tam, -1);

        int actual_index = findIndexVertice(id_Partida);
        (*d)[actual_index] = pair<char, double>('O', 0);
        while (qnt_open > 0) {
            actual_index = findSmallestVerticeOpen((*d), tam);
            if(actual_index == -1) {
                //cout << "Actual_Index: " << actual_index << endl;
                //cout << "   Qauntidade abertos: " << qnt_open << endl;
                //imprimeTodosVerticesAbertos((*d), tam);
                break;
            }
            (*d)[actual_index].first = 'C';
            qnt_open--;
            Vertice *actual_vertice = getVertice(actual_index);
            //cout << "======================" << endl;
            //cout << "Menor custo: " << (*d)[actual_index].second <<" - Indice: " << actual_index << " ID: " << actual_vertice->getIdConcecta() << endl;
            list<Aresta*> actual_arestas = actual_vertice->getArestas();
            for(auto it_ar = actual_arestas.begin(); it_ar != actual_arestas.end(); it_ar++) {
                int sub_index = findIndexVertice((*it_ar)->getIdPopsConectado());
                double coust = (*d)[actual_index].second + (*it_ar)->getVelocidade();
                if((*d)[sub_index].second > coust) {
                    //cout << "*     " << (*d)[sub_index].second << " > " << coust<< endl;
                    //cout << "       Substituiu " << (*d)[sub_index].second;
                    (*d)[sub_index].second = coust;
                    //cout << " por " << (*d)[sub_index].second << endl;
                }
            }
        }
        actual_index = findIndexVertice(id_Chegada);
        if((*d)[actual_index].second != INFINITY) {
            r = (*d)[actual_index].second;
        }

        delete d;
        delete p;
    }
    return r;
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