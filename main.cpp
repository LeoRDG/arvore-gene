/**
 * Aqui rodará o programa principal
 * 
 * Contém o loop principal da CLI para gerenciar pessoas
 * e relações da árvore, imprimir e salvar os dados em arquivos
 */

#include <iostream>
#include <vector>
#include <functional>
#include "Arvore.h"
#include "Pessoa.h"

using namespace std;

void print(string str){
    cout << str << "\n";
}

struct Menu{
    vector<string> opcoes = {
        "1 - Adicionar pessoa",
        "2 - Buscar pessoa",
        "3 - Exibir parentesco",
        "4 - Mostrar gerações",
        "5 - Exibir Ascendentes e Descendentes",
        "6 - Listar Arovre a partir de uma pessoa",
        "7 - Contar Descendentes de uma Pessoa",
        "8 - Editar Pessoa",
        "9 - Sair",
    };

    void imprimir(){
        for (string opc : opcoes) print(opc);
    }
};

void processar_resposta(int resposta){
    switch (resposta) {
        case 1:
            break;
    }
}



int main()
{
    Menu menu = Menu{};
    menu.imprimir();

    return 0;
}
