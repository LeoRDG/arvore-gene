/**
 * Aqui serão implementadas as funcionalidades da Pessoa
 */

#include "Arvore.h"
#include "Opcao.h"
#include <iostream>

using namespace std;

Arvore::Arvore(){
    opcoes.push_back(Opcao{
        "Adicionar pessoa",
        [this] () {adicionar_pessoa();}
    });
    opcoes.push_back(Opcao{
        "Buscar pessoa",
        [this]() {encontrar_pessoa();}
    });
    opcoes.push_back(Opcao{
        "Exibir parentesco",
    });
    opcoes.push_back(Opcao{
        "Mostrar gerações",
        
    });
    opcoes.push_back(Opcao{
        "Exibir Ascendentes e Descendentes",

    });
    opcoes.push_back(Opcao{
        "Listar Arovre a partir de uma pessoa",

    });
    opcoes.push_back(Opcao{
        "Contar Descendentes de uma Pessoa",

    });
    opcoes.push_back(Opcao{
        "Editar Pessoa",

    });
    opcoes.push_back(Opcao{
        "Sair",
        [this]() {exit(0);}
    });
}

void Arvore::imprimir_opcoes(){
    for (int i=1; i<=opcoes.size(); i++) {
        Opcao opt = opcoes[i];
        (opt.func == nullptr) ? cout << "   " : cout << i << ". ";
        cout << opcoes[i].descricao << "\n";
    }
}

void Arvore::adicionar_pessoa(){
    cout << "Adicionando pessoa...";
}

Pessoa * Arvore::encontrar_pessoa(){
    return new Pessoa{};
}

bool Arvore::processar_resposta(int resposta){
    if (resposta >= opcoes.size() || resposta <= 0) return false;
    if (opcoes[resposta].func == nullptr) return false; 
    opcoes[resposta].func();
    return true;
}