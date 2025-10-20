/**
 * Aqui serão implementadas as funcionalidades da Pessoa
 */

#include "Arvore.h"
#include "util.h"
#include <iostream>
#include <fstream>
#include "Pessoa.h"

using namespace std;

Arvore::Arvore(string nm){
    // As opcoes do menu sao criadas aqui usando a struct Opcao
    // Esse metodo foi escolhido para nao precisar usar switch/if para cada caso
    // tornando o código mais modular e fácil de manter.
    nome = nm;

    opcoes = {
        { "Adicionar pessoa",                     [this]() {adicionar_pessoa();} },
        { "Buscar pessoa",                        [this]() {buscar_pessoas();} },
        { "Exibir parentesco",                    [this]() {cout << "funcao para exibir parentesco pessoa... " << endl;} },
        { "Mostrar gerações"                       },
        { "Exibir Ascendentes e Descendentes",     },
        { "Listar Arovre a partir de uma pessoa",  },
        { "Contar Descendentes de uma Pessoa",     },
        { "Editar Pessoa",                         },
        { "Sair",                                 [this]() {exit(0);} },
        //{ "Salvar" ,                              [this]() {salvar();} },
        //{ "Carregar" ,                            [this]() {carregar();} },

    };
}

void Arvore::imprimir_menu(){
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

void Arvore::adicionar_pessoa(){
    string nome = ler_string("Digite o nome da pessoa que voce quer adicionar:\n");
    char genero =  pedir_genero();
    Data nascimento = pedir_data();

    Pessoa *pessoa = new Pessoa{nome, nascimento, genero};

    familia.insert({pessoa->chave(), pessoa});

    if (!confirmar("Gostaria de definir os pais dessa pessoa?")) return;

}

void Arvore::buscar_pessoas(){
    string nome = ler_string("Digite o nome da pessoa que deseja achar, deixe em branco para mostrar todas as pessoas: ");
    clear();
    print("Pesquisando por '" + nome + "'");
    print("________________________________________________");

    // Procura por pessoas com nomes parecidos e se achar, coloca elas em um vetor
    vector<Pessoa*> encontradas;
    for (auto p : familia) {
        Pessoa *pessoa = p.second;
        if ( contem( nome, pessoa->nome ) ) encontradas.push_back(pessoa);
    }

    // Se pessoas foram encontradas, mostrar elas
    if ( encontradas.size() <=0 ) print("Nenhuma pessoa encontrada");
    else {
        printf("%zu/%zu Pessoas encontradas\n", encontradas.size(), familia.size());
        print("________________________________________________");
        cout << "ID. ";
        Pessoa::imprimir_cabecario();
        for (int i=0; i<encontradas.size(); i++) {
            printf("% 3d ", i);
            encontradas[i]->mostrar();
        }
    }
}

bool Arvore::processar_resposta(int resposta){
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

void Arvore::salvar(){
    ofstream arquivo(nome + ".csv");

    for (auto p : familia) {
        Pessoa *pessoa = p.second;
        arquivo << pessoa->serialize() << "\n";
    }

    arquivo.close();
}

void Arvore::carregar(){
    ifstream arquivo(nome + ".csv");
    string linha;

    while ( getline(arquivo, linha) ) {
        Pessoa *pessoa = Pessoa::deserialize(linha);
        familia.insert({pessoa->chave(), pessoa});
    }

    arquivo.close();
}

//vector<Pessoa*> Arvore::query(){}

void Arvore::info_simples(){
    print(Data::hoje().str());
    print("Nome da Arvore : " + nome);
    print("Quantidade de pessoas : " + to_string(familia.size()));
}