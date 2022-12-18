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
    //Inicia o retorno com -1.
    double r = -1;
    //Se o vertice de partida ou o vertice de chegada existirem.
    if((findIndexVertice(id_Partida) != -1) && (findIndexVertice(id_Chegada) != -1)) {
        //Pega tamnaho do grafo (quantidade de vertices).
        int tam = vertices.size();
        //Cria um vetor de pares com a mesma quantidade de vertices do grafo.
        //Par - (Aberto, Velocidade Fluxo) -> todos abertos e com fluxo infinito
        vector<pair<char, double>> *d = new vector<pair<char, double>>(tam, pair<char, double>('O', INFINITY));
        //Quantidade de vertices abertos
        int qnt_open = tam;

        //Indice atual comeca do vertice de patida
        int actual_index = findIndexVertice(id_Partida);
        //Garante abertura do vertice de partida e colca fluxo 0.
        (*d)[actual_index] = pair<char, double>('O', 0);

        //Enaquanto tiver vertices abertos.
        while (qnt_open > 0) {

            //Pega um vertice aberto com o menor fluxo.
            actual_index = findSmallestVerticeOpen((*d), tam);
            //Se nao tiver um menor acaba rotina.
            if(actual_index == -1) {
                break;
            }

            //Fecha o veritce que acabou de acessar.
            (*d)[actual_index].first = 'C';

            //Diminui a quantidade de vertices abertos.
            qnt_open--;

            //Recupera esse vertice.
            Vertice *actual_vertice = getVertice(actual_index);

            //Recupera seu id.
            int actual_index_id = actual_vertice->getIdConcecta();

            //Recupera todas suas arestas.
            list<Aresta*> actual_arestas = actual_vertice->getArestas();

            //Percorre todas as arestas atualizando o fluxo na sua posição equivalete do vetor de pares.
            for(auto it_ar = actual_arestas.begin(); it_ar != actual_arestas.end(); it_ar++) {
                //Pega o indice do vertice de ligacao da aresta.
                int sub_index = findIndexVertice((*it_ar)->getIdPopsConectado());
                //Se o fluxo atual eh maior que a velocidade dessa aresta .
                if(((*d)[sub_index].second > (*it_ar)->getVelocidade())) {
                    //O fluxo passa ser a velocidade da aresta.
                    double flux = (*it_ar)->getVelocidade(); 
                    //Se o indice atual for diferente do vertice de partida e
                    // a velociade atual for maior que o fluxo do vertice atual.
                    if((actual_index_id != id_Partida) && ((*it_ar)->getVelocidade() > (*d)[actual_index].second)) {
                        //O fluxo passa ser o menor (no caso a do vertice atual).
                        flux = (*d)[actual_index].second;
                    }
                    //Atualiza fluxo do sub indice para o definido anteriormente.
                    (*d)[sub_index].second = flux;
                }
            }
        }
        //Pega o indice do Vertice de chegada.
        actual_index = findIndexVertice(id_Chegada);
        //Verifica se ele foi acessado ao menos 1 vez.
        if((*d)[actual_index].second != INFINITY) {
            //Atualiza retorno para o fluxo maximo do vertice de partida ao de chegada
            r = (*d)[actual_index].second;
        }

        //Deleta o vetor de pares.
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
    //Inicia o retorno com -1.
    double r = -1;
    //Se o vertice de partida ou o vertice de chegada existirem.
    if((findIndexVertice(id_Partida) != -1) && (findIndexVertice(id_Chegada) != -1)) {
        //Pega tamnaho do grafo (quantidade de vertices).
        int tam = vertices.size();
        //Cria um vetor de pares com a mesma quantidade de vertices do grafo.
        //Par - (Aberto, distancia) -> todos abertos e com distancia infinita
        vector<pair<char, double>> *d = new vector<pair<char, double>>(tam, pair<char, double>('O', INFINITY));
        //Quantidade de vertices abertos
        int qnt_open = tam;

        //Indice atual comeca do vertice de patida
        int actual_index = findIndexVertice(id_Partida);
        //Garante abertura do vertice de partida e colca distancia 0.
        (*d)[actual_index] = pair<char, double>('O', 0);

        //Enaquanto tiver vertices abertos.
        while (qnt_open > 0) {

            //Pega um vertice aberto com o menor distancia.
            actual_index = findSmallestVerticeOpen((*d), tam);
            //Se nao tiver um menor acaba rotina.
            if(actual_index == -1) {
                break;
            }

            //Fecha o veritce que acabou de acessar.
            (*d)[actual_index].first = 'C';

            //Diminui a quantidade de vertices abertos.
            qnt_open--;

            //Recupera esse vertice.
            Vertice *actual_vertice = getVertice(actual_index);

            //Recupera todas suas arestas.
            list<Aresta*> actual_arestas = actual_vertice->getArestas();

            //Percorre todas as arestas atualizando a distancia na sua posição equivalete do vetor de pares.
            for(auto it_ar = actual_arestas.begin(); it_ar != actual_arestas.end(); it_ar++) {
                //Pega o indice do vertice de ligacao da aresta.
                int sub_index = findIndexVertice((*it_ar)->getIdPopsConectado());
                //O custo eh soma do custo atual com a distancia do vertice.
                double coust = (*d)[actual_index].second + (*it_ar)->getVelocidade();
                //Se o custo for menor que a distancia do vertice de partida a esse vertice. 
                if((*d)[sub_index].second > coust) {
                    //Atualiza a distancia do vertice de partida a esse vertice para a menor.
                    (*d)[sub_index].second = coust;
                    //Atualiza o vetor de antecessores. 
                    (*antecessores)[sub_index] = actual_index;
                }
            }
        }
        //Pega o indice do vertice de chegada.
        actual_index = findIndexVertice(id_Chegada);
        //Se ele foi acessado pelo menos 1 vez.
        if((*d)[actual_index].second != INFINITY) {
            //O retorno recebe a menor distancia entre o vertice de partida e de chegada. 
            r = (*d)[actual_index].second;
        }

        //Deleta o vetor de pares.
        delete d;
    }
    
    return r;
 }