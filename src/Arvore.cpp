/**
 * Aqui serão implementadas as funcionalidades da Pessoa
 */

#include "../include/Arvore.h"
#include "../include/util.h"
#include <iostream>
#include <fstream>
#include "../include/Pessoa.h"
#include <unordered_map>

using namespace std;

Arvore::Arvore(string nm){
    nome = nm;
}

void Arvore::adicionar_pessoa(){
    string nome = ler_string("Digite o nome da pessoa que voce quer adicionar:\n");
    char genero =  pedir_genero();
    Data nascimento = pedir_data();

    Pessoa *pessoa = new Pessoa{nome, nascimento, genero};

    familia.insert({pessoa->chave(), pessoa});

    if (!confirmar("Gostaria de definir os pais dessa pessoa?")) return;
    definir_pais(pessoa);
}

void Arvore::buscar_pessoas(){
    string nome = ler_string("Digite o nome da pessoa que deseja achar, deixe em branco para mostrar todas as pessoas: ");
    clear();
    print("Pesquisando por '" + nome + "'");
    print("________________________________________________");

    // Procura por pessoas com nomes parecidos e se achar, coloca elas em um vetor
    vector<Pessoa*> encontradas = query(nome);

    // Se pessoas foram encontradas, mostrar elas
    if ( encontradas.empty() ) {
        print("Nenhuma pessoa encontrada");
        return;
    }
    
    mostrar_pessoas(encontradas);
    int num = ler_int("Qual pessoa voce estava procurando? ", encontradas.size(), 1);
    
    Pessoa*p = encontradas[num-1];
    p->mostrar_info();
    p->mostrar_menu();
    p->menu.esperar_resposta();
}

void Arvore::definir_pais(Pessoa*pessoa){
    clear();
    print("Definindo os pais de '" + pessoa->nome + "'");
    vector<Pessoa*> possiveis_pais = query("", pessoa->nascimento.valor(), 'M');
    mostrar_pessoas(possiveis_pais);
    int resposta = ler_int("Escolha uma dessas pessoas para ser o pai: ", possiveis_pais.size(), 1) -1;
    pessoa->set_pai(possiveis_pais[resposta]);

    clear();
    print("Definindo os pais de '" + pessoa->nome + "'");
    vector<Pessoa*> possiveis_maes = query("", pessoa->nascimento.valor(), 'F');
    mostrar_pessoas(possiveis_maes);
    resposta = ler_int("Escolha uma dessas pessoas para ser a mae: ", possiveis_maes.size(), 1) -1;
    pessoa->set_mae(possiveis_maes[resposta]);
}

void Arvore::mostrar_pessoas(vector<Pessoa*> pessoas){
    printf("%zu/%zu Pessoas encontradas\n", pessoas.size(), familia.size());
    print("________________________________________________");
    cout << "ID. ";
    Pessoa::imprimir_cabecario();

    for (int i=0; i<pessoas.size(); i++) {
        printf("% 3d ", i+1);
        pessoas[i]->mostrar();
    }
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
    unordered_map<string, Pessoa*> pessoas; // map temporario para guardar a pessoa usando sua chave

    // Primeiro loop para criar todas as pessoas
    while ( getline(arquivo, linha) ) {
        Pessoa *pessoa = Pessoa::deserialize(linha);
        familia.insert({pessoa->chave(), pessoa});
        pessoas.insert({pessoa->chave(), pessoa});
    }

    // Segundo loop para definir os pais das pessoass
    for (auto p : pessoas){
        Pessoa *pessoa = p.second;
        if (pessoa->chave_pai != "null") pessoa->set_pai(pessoas[pessoa->chave_pai]);
        if (pessoa->chave_mae != "null") pessoa->set_mae(pessoas[pessoa->chave_mae]);
    }

    arquivo.close();
}

vector<Pessoa*> Arvore::query(string nome, int dt_valor, char genero, int geracao){
    vector<Pessoa*> encontradas;
    for (auto p : familia) {
        Pessoa * pessoa = p.second;
        if ( !contem(pessoa->nome, nome) ) continue;
        if ( pessoa->nascimento.valor() >= dt_valor ) continue;
        if ( genero != '\0' && pessoa->genero != genero ) continue;
        if ( geracao != -1 && pessoa->geracao != geracao ) continue;
        encontradas.push_back(pessoa);
    }
    return encontradas;
}

void Arvore::info_simples(){
    print(Data::hoje().str());
    print("Nome da Arvore : " + nome);
    print("Quantidade de pessoas:", ' ');
    print_com_cor(to_string(familia.size()), "verde");
    print();
}

void Arvore::exibir_geracao() {
    if (familia.empty()) {
        print("Nenhuma pessoa cadastrada.");
        return;
    }

    int geracao = ler_int("Digite a geracao que está procurando: ");
    vector<Pessoa*> encontradas = query("", INT_MAX, '\0', geracao);

    mostrar_pessoas(encontradas);
}

void Arvore::criar_menu() {
    // As opcoes do menu sao criadas aqui usando a struct Opcao
    // Esse metodo foi escolhido para nao precisar usar switch/if para cada caso
    // tornando o código mais modular e fácil de manter.
    
    menu = { {
        { "Adicionar pessoa",                     [this]() {adicionar_pessoa();} },
        { "Buscar pessoa",                        [this]() {buscar_pessoas();} },
        { "Mostrar gerações",                     [this]() {exibir_geracao();}},  //VAMO GREMIO
        { "Exibir parentesco entre 2 pessoas",    [this]() {cout << "funcao para exibir parentesco pessoa... " << endl;} },
        { "Sair",                                 [this]() {exit(0);} },
        //{ "Salvar" ,                              [this]() {salvar();} },
        //{ "Carregar" ,                            [this]() {carregar();} },
    } };
}

void Arvore::imprimir_menu() {
    if (menu.opcoes.empty()) criar_menu();
    menu.imprimir();
}
