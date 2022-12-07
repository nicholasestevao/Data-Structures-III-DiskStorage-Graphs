#include <iostream>
#include "../headers/arquivoBin.h"
#include "../headers/funcionalidades.h"
#include "../headers/funcoesFornecidas.h"

int main(int argC, char *argV[]){
    int opcao;
    char *nome_arquivo = new char[20];
    
    cin >> opcao >> nome_arquivo;

    switch (opcao)
    {
        case 1:
            //Create table (1) - Isaac e Nicholas
            funcionalidade1CreateTable(nome_arquivo);
            break;
    
        case 2:
            //Select (2) - Nicholas
            funcionalidade2Select(nome_arquivo);
            break;
        
        case 3:
            //Select where (3) - Isaac
            funcionalidade3SelectWhere(nome_arquivo);
            break;
        
        case 4:
            //Remocao logica (4) - Isaac
            funcionalidade4Remove(nome_arquivo);
            break;
        
        case 5:
            //Insercao (5) - Nicholas
            funcionalidade5Insert(nome_arquivo);
            break;

        case 6:
            //Compactacao (6) - Nicholas
            funcionalidade6Compactacao(nome_arquivo);
            break;

        case 7:
            //CreateIndex (7) - Nicholas
            funcionalidade7CreateIndex(nome_arquivo);
            break;
            
        case 8:
            //Select Where (8) - Isaac
            funcionalidade8SelectWhere(nome_arquivo);
            break;
            
        case 9:
            //se
            funcionalidade9InsertArvB(nome_arquivo);
            break;

        case 10:
            funcionalidade10Juncao(nome_arquivo);
            break;
        case 11:
            funcionalidade11CriarGrafo(nome_arquivo);
            break;    
    }

    delete[] nome_arquivo;
    return 0;
}   

