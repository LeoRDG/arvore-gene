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
    // Para cada Opcao
    // é imprimido o nome da opcao associada a um numero (i + 1)
    for (int i=0; i<opcoes.size(); i++) {
        Opcao opt = opcoes[i];
        
        // Se a funcao for nula, (ainda nao foi implementada)
        // nao imprimir a opcao
        if (opt.func == nullptr) continue;
        
        cout << i+1 << ". ";
        cout << opcoes[i].descricao << "\n";
    }
}

void Arvore::adicionar_pessoa(){
    cout << "Adicionando pessoa...";
}

Pessoa * Arvore::encontrar_pessoa(){
    string nome;
    cout << "Digite o nome da pessoa: ";
    cin.ignore();
    getline(cin, nome);

    for (Pessoa* p : familia) {
        if (p->nome == nome) {
            p->mostrar();
            return p;
        }
    }
    return new Pessoa{};
}

bool Arvore::processar_resposta(int resposta){
    if (resposta >= opcoes.size() || resposta <= 0) return false;
    if (opcoes[resposta].func == nullptr) return false; 
    opcoes[resposta].func();
    return true;
}