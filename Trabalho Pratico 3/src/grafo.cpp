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
                vertice_A->insertAresta(new Aresta(*(dados_A->idPoPsConectado), *(dados_A->velocidade), (dados_A->unidadeMedida)[0]));
                

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
            //cout << "Menor custo - Indice: " << actual_index << " ID: " << actual_vertice->getIdConcecta() << endl;
            list<Aresta*> actual_arestas = actual_vertice->getArestas();
            for(auto it_ar = actual_arestas.begin(); it_ar != actual_arestas.end(); it_ar++) {
                int sub_index = findIndexVertice((*it_ar)->getIdPopsConectado());
                //cout << "   Sub_Index: " << sub_index << " ID: " << (*it_ar)->getIdPopsConectado() << endl;
                double coust = (*d)[actual_index].second + (*it_ar)->getVelocidade();
                if(((*d)[sub_index].second > coust)) {
                    //cout << "*     " << (*d)[sub_index].second << " > " << coust << endl;
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