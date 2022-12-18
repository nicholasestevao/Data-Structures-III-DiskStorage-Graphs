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
                Vertice *vertice_A = findVertice(*(dados_A->idConecta));
                if(vertice_A == nullptr){
                    //vertice nao existe ainda
                    vertice_A = new Vertice(*(dados_A->idConecta), dados_A->nomePoPs, dados_A->nomePais, dados_A->siglaPais);
                    
                    insertVertice(vertice_A);
                }
                //vertice ja existe
                if(*(dados_A->idPoPsConectado) != -1) {
                    Aresta *a = vertice_A->findAresta(*(dados_A->idPoPsConectado));
                    
                    if(a == nullptr){
                        //Aresta ainda nao existe
                        if(*(dados_A->velocidade) >0){
                            vertice_A->insertAresta(new Aresta(*(dados_A->idPoPsConectado), *(dados_A->velocidade), (dados_A->unidadeMedida)[0]));
                           //Inseriu aresta pois a velocidade nao eh nula
                        }else{
                            //Nao inseriu pois a velocidade eh nula
                        }                        
                    }else{
                        //Aresta ja existe
                        if(a->getVelocidade() == 0){
                            a->setVelocidade_Unidade(*(dados_A->velocidade), *(dados_A->unidadeMedida));
                        }else if(*(dados_A->velocidade) != 0 && a->converteVelocidadeMbps(*(dados_A->velocidade), *(dados_A->unidadeMedida)) != a->getVelocidade()){
                            //Velocidade nao nula e diferente da anterior
                            vertice_A->insertAresta(new Aresta(*(dados_A->idPoPsConectado), *(dados_A->velocidade), (dados_A->unidadeMedida)[0]));
                        }
                    }
                }

                // Inserindo no outro vertice (pois o grafo é nao direcionado)
                Vertice *vertice_B = findVertice(*(dados_A->idPoPsConectado));
                if(vertice_B == nullptr){
                    //vertice nao existe ainda
                    int RRN_vertice_B = -1;
                    buscaChaveArvoreB(arquivoArvB, raiz, *(dados_A->idPoPsConectado), &RRN_vertice_B);
                    if(RRN_vertice_B != -1){
                        RegistroDados *dados_B = lerRegistroDadosArquivoBin_RRN(arq_bin, RRN_vertice_B);
                        //Criou vertice
                        vertice_B = new Vertice(*(dados_B->idConecta), dados_B->nomePoPs, dados_B->nomePais, dados_B->siglaPais);
                        insertVertice(vertice_B);
                        desalocaRegistrosDados(&dados_B, 1);
                    }   
                }
                //vertice ja existe
                if(*(dados_A->velocidade) != 0 ){
                    vertice_B->insertAresta(new Aresta(*(dados_A->idConecta), *(dados_A->velocidade), (dados_A->unidadeMedida)[0]));
                }                
                
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

void Grafo::buscaProfundidade(int *** arv_busca, int id_vertice_atual, int id_vertice_pai, int *tempo, int * num_arestas_retorno){
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
    Vertice vertice_atual = *(findVertice(id_vertice_atual));
    list<Aresta*> arestas = vertice_atual.getArestas();
    if(!arestas.empty()) {
            if((*arv_busca)[findIndexVertice(vertice_atual.getIdConcecta())][1] == -1){
                // Encontrou vertice que ainda nao foi descoberto (branco)
                (*arv_busca)[findIndexVertice(vertice_atual.getIdConcecta())][0] = vertice_atual.getIdConcecta();
                (*arv_busca)[findIndexVertice(vertice_atual.getIdConcecta())][1] = 1; // cinza
                (*arv_busca)[findIndexVertice(vertice_atual.getIdConcecta())][2] = *tempo;
            }

            //Lista de vertices
            list<Vertice*> vertices = getVertices();
            auto it = arestas.begin();
            for(; it != arestas.end(); ++it){
                int idPoPs = (*it)->getIdPopsConectado();
                
                if(idPoPs != id_vertice_pai){
                    (*tempo)++;
                    int idVerticePoPs = findIndexVertice(idPoPs);
                    // indo no vertice idPoPs verificar

                    if((*arv_busca)[idVerticePoPs][1] == 2){
                        //Encontrou vertice preto -> vai para proxima aresta
                    }else if((*arv_busca)[idVerticePoPs][1] == 1){
                        // Encontrou vertice cinza
                        (*num_arestas_retorno)++;
                        //vai para proxima aresta
                    }else{
                        if((*arv_busca)[idVerticePoPs][1] == -1){
                            // Encontrou vertice que ainda nao foi descoberto (branco)
                            (*arv_busca)[idVerticePoPs][0] = idPoPs;
                            (*arv_busca)[idVerticePoPs][1] = 1; // cinza
                            (*arv_busca)[idVerticePoPs][2] = *tempo;
                        }   
                        buscaProfundidade(arv_busca, idPoPs, vertice_atual.getIdConcecta(), tempo, num_arestas_retorno);
                        // Vertice atual voltou a ser o anterior
                    }               
                }else{
                    //Ignorou aresta que conecta vertice com seu pai
                }
            }
            //Testou todas as arestas do vertice 
            (*arv_busca)[findIndexVertice(vertice_atual.getIdConcecta())][1] = 2;   
            //Vertice  se tornou preto
            (*arv_busca)[findIndexVertice(vertice_atual.getIdConcecta())][3] = *tempo; 
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

        int actual_index = findIndexVertice(id_Partida);
        (*d)[actual_index] = pair<char, double>('O', 0);
        while (qnt_open > 0) {
            actual_index = findSmallestVerticeOpen((*d), tam);
            if(actual_index == -1) {
                break;
            }
            (*d)[actual_index].first = 'C';
            qnt_open--;
            Vertice *actual_vertice = getVertice(actual_index);
            int actual_index_id = actual_vertice->getIdConcecta();
            list<Aresta*> actual_arestas = actual_vertice->getArestas();
            for(auto it_ar = actual_arestas.begin(); it_ar != actual_arestas.end(); it_ar++) {
                int sub_index = findIndexVertice((*it_ar)->getIdPopsConectado());
                if(((*d)[sub_index].second > (*it_ar)->getVelocidade())) {
                    double coust = (*it_ar)->getVelocidade(); 
                    if((actual_index_id != id_Partida) && ((*it_ar)->getVelocidade() > (*d)[actual_index].second)) {
                        coust = (*d)[actual_index].second;
                    }
                    (*d)[sub_index].second = coust;
                }
            }
        }
        actual_index = findIndexVertice(id_Chegada);
        if((*d)[actual_index].second != INFINITY) {
            r = (*d)[actual_index].second;
        }

        delete d;
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
        list<Aresta*> arestas = (*it)->getArestas();
        auto it_arestas = arestas.begin();
        while (it_arestas != arestas.end())
        {
            cout << (*it)->getIdConcecta() << " " << (*it)->getNomePoPs().c_str() << " " << (*it)->getNomePais().c_str(); 
            cout << " " << (*it)->getSiglaPais().c_str() << " " << (*it_arestas)->getIdPopsConectado(); 
            cout << " " << (*it_arestas)->getVelocidade() << "Mbps" << endl;
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

double Grafo::menorDistanciaEntreVertices(int id_Partida, int id_Chegada, vector<int> *antecessores) const {
    double r = -1;
    if((findIndexVertice(id_Partida) != -1) && (findIndexVertice(id_Chegada) != -1)) {
        int tam = vertices.size();
        vector<pair<char, double>> *d = new vector<pair<char, double>>(tam, pair<char, double>('O', INFINITY));
        int qnt_open = tam;

        int actual_index = findIndexVertice(id_Partida);
        (*d)[actual_index] = pair<char, double>('O', 0);
        while (qnt_open > 0) {
            actual_index = findSmallestVerticeOpen((*d), tam);
            if(actual_index == -1) {
                break;
            }
            (*d)[actual_index].first = 'C';
            qnt_open--;
            Vertice *actual_vertice = getVertice(actual_index);
            list<Aresta*> actual_arestas = actual_vertice->getArestas();
            for(auto it_ar = actual_arestas.begin(); it_ar != actual_arestas.end(); it_ar++) {
                int sub_index = findIndexVertice((*it_ar)->getIdPopsConectado());
                double coust = (*d)[actual_index].second + (*it_ar)->getVelocidade();
                if((*d)[sub_index].second > coust) {
                    (*d)[sub_index].second = coust;
                    (*antecessores)[sub_index] = actual_index;
                }
            }
        }
        actual_index = findIndexVertice(id_Chegada);
        if((*d)[actual_index].second != INFINITY) {
            r = (*d)[actual_index].second;
        }
        delete d;
    }
    
    return r;
 }


