/**
 * Aqui serão implementadas as funcionalidades da Pessoa
 */

#include "Arvore.h"
#include "util.h"
#include <iostream>

using namespace std;

Arvore::Arvore(){
    // As opcoes do menu sao criadas aqui usando a struct Opcao
    // Esse metodo foi escolhido para nao precisar usar switch/if para cada caso
    // tornando o código mais modular e fácil de manter.

    opcoes = {
        { "Adicionar pessoa",                     [this]() {adicionar_pessoa();} },
        { "Buscar pessoa",                        [this]() {encontrar_pessoa();} },
        { "Exibir parentesco",                    [this]() {cout << "funcao para exibir parentesco pessoa... " << endl;} },
        { "Mostrar gerações"                       },
        { "Exibir Ascendentes e Descendentes",     },
        { "Listar Arovre a partir de uma pessoa",  },
        { "Contar Descendentes de uma Pessoa",     },
        { "Editar Pessoa",                         },
        { "Sair",                                 [this]() {exit(0);} },
        { "Salvar" ,                              [this]() {salvar();} },
        { "Carregar" ,                            [this]() {carregar();} },

    };
}

void Arvore::imprimir_menu(){
    cout << "########## MENU ##########" << "\n";
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
    string nome;
    string nascimento;
    char sexo;
    char resposta;

    cout << "Digite o nome da pessoa que voce quer adicionar" << endl;
    cin.ignore();
    getline(cin, nome);
    cout << "Digite o sexo (f,m): ";
    cin >> sexo;
    cout << "Digite a data de nascimento (dd/mm/yyyy): " << endl;
    cin >> nascimento;

    Pessoa *pessoa = new Pessoa{nome, nascimento, sexo};
    familia.push_back(pessoa);

    // cout << "Gostaria de definir os pais dessa pessoa? (S)im/(N)ao";
    // cin >> resposta;

    // if (resposta == 's' || resposta == 'S') {
        
    // }

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
    // Como o menu mostrado ao usuario tem um offset de 1 comparado ao vetor de opcoes
    // Deve ser subtraido 1 da resposta
    resposta -= 1;

    if (resposta >= opcoes.size() || resposta < 0) return false;
    if (opcoes[resposta].func == nullptr) return false; 

    // Chama a funcao da Opcao
    opcoes[resposta].func();
    return true;
}