#include "../include/Menu.h"
#include "../include/util.h"
#include <iostream>

using namespace std;

void Menu::imprimir(){
    print("----------------------- MENU -----------------------\n");
    // Para cada Opcao
    // é imprimido o nome da opcao associada a um numero (i + 1)
    for (int i=0; i<opcoes.size(); i++) {
        Opcao opt = opcoes[i];
        
        // Se a funcao for nula, (ainda nao foi implementada)
        // nao imprimir a opcao
        if (opt.func == nullptr) continue;
        
        cout << i+1 << ". ";
        print(opcoes[i].descricao);
    }
    print();
}


bool Menu::processar_resposta(int resposta){
    // Como o menu mostrado ao usuario tem um offset de 1 comparado ao vetor de opcoes
    // Deve ser subtraido 1 da resposta
    resposta -= 1;

    if (resposta >= opcoes.size() || resposta < 0) return false;
    if (opcoes[resposta].func == nullptr) return false; 

    // Chama a funcao da Opcao
    clear();
    opcoes[resposta].func();
    return true;
}