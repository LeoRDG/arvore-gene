/**
 * Aqui serão implementadas as funcionalidades da Pessoa
 */

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <tuple>
#include <map>
#include <utility>
#include <vector>
#include "../include/Pessoa.h"

using namespace std;

void Pessoa::exibir_cabecario(){
    cout << left << setw(L_NOME) << "Nome";
    cout << setw(L_NASC) << "Nascimento";
    cout << setw(L_GEN) << "Genero";
    cout << setw(L_PAIS) << "Pai";
    cout << setw(L_PAIS) << "Mae";
    cout << setw(L_GEN) << "Geracao";
    cout << "\n";
}

void Pessoa::exibir_linha(){
    cout << left << setw(L_NOME) << limite_str(nome, L_NOME-1);
    cout << setw(L_NASC) << nascimento.str();
    cout << setw(L_GEN) << genero;

    for (auto p : {pai, mae}) {
        cout << setw(L_PAIS);
        (p == nullptr) ? cout << "" : cout << limite_str(p->primeiro_nome(), L_PAIS-1);
    }

    cout << setw(L_GER);
    (geracao == GERACAO_INICIAL) ? cout << "???" : cout << geracao;
    
    cout << "\n";
}

string Pessoa::primeiro_nome(){
    int espaco = nome.find(' ');
    if (espaco >= nome.size() || espaco < 0) return nome; // Se nao encontrar espaco retorna o nome completo
    return nome.substr(0, espaco);
}

void Pessoa::definir_pai(Pessoa* pai){
    this->pai = pai;
    pai->filhos.push_back(this);
    definir_geracao();
}

void Pessoa::definir_mae(Pessoa* mae){
    this->mae = mae;
    mae->filhos.push_back(this);
    definir_geracao();
}

string Pessoa::chave(){
    // Junta o nome e o valor do nascimento e deixando tudo minusculo
    return to_string(nascimento.valor()) + minusculas(nome);
}

string Pessoa::serializar(){
    stringstream stream;
    string resultado;

    stream << setfill('0') << setw(4) << nascimento.ano << ","
    << setw(2) << nascimento.mes << ","
    << setw(2) << nascimento.dia << ","
    << nome << ","
    << genero << ',';

    (pai == nullptr) ? stream << " ," : stream << pai->chave() << ",";
    (mae == nullptr) ? stream << " "  : stream << mae->chave();

    getline(stream, resultado);

    return resultado;
}

tuple<Pessoa*, string, string> Pessoa::deserializar(string dados){
    // Funcao Estatica
    // Usa uma stream de string para separar os dados por virgula
    // e coloca-los em um vetor de strings

    // [ano,mes,dia,nome,genero,pai,mae]
    vector<string> vetor_dados;
    istringstream str(dados);
    string dado;

    while ( getline(str, dado, ',') ){
        vetor_dados.push_back(dado);
    }

    // Se o vetor nao tiver o matanho certo, retornar nullptr
    if (vetor_dados.size() != 7) return {nullptr, "", ""};

    // Se ocorrer um erro ao converter a string para int, retornar nullptr
    int dia, mes, ano;
    try {
        dia = stoi(vetor_dados[2]);
        mes = stoi(vetor_dados[1]);
        ano = stoi(vetor_dados[0]);
    } catch (invalid_argument) {
         return {nullptr, "", ""};
    }

    string nome = vetor_dados[3];
    char genero = vetor_dados[4][0];

    Data nascimento = Data(dia, mes, ano);

    Pessoa* pessoa = new Pessoa{nome, nascimento, genero};

    return {pessoa, vetor_dados[5], vetor_dados[6]};
}

void Pessoa::definir_geracao() {
    // Pega o valor maior entre a geracao do pai e da mae
    int g_pai = (pai == nullptr) ? GERACAO_INICIAL : pai->geracao;
    int g_mae = (mae == nullptr) ? GERACAO_INICIAL : mae->geracao;
    int nivel = max(g_pai, g_mae);

    if (geracao >= nivel+1) return; // Só define a geracao se o nivel do pai ou da mae for maior que a geracao atual

    geracao = nivel+1; // Define a geracao dessa pessoa

    // Define a geracao dos filhos
    for (auto* f : filhos) {
        f->definir_geracao();
    }
}

void Pessoa::exibir_ascendentes(int nivel) {

    if (pai == nullptr && mae == nullptr) {
        for (int i=0; i <nivel; i++) cout << "  ";
        print("Não há ascendentes cadastrados para: " + this->nome, '\n', "vermelho");
        return;
    }
    else{
        if (pai != nullptr) {
            pai->exibir_ascendentes(nivel+1);
            for (int i=0; i <nivel; i++) cout << "  ";
            print("Pai de " + this->nome + ": ", '\0', "cinza");
            print(pai->nome);
            // cout << "Pai de "<< this->nome << ": " << pai->nome << "\n";
        }
        
        if (mae != nullptr) {
            mae->exibir_ascendentes(nivel+1);
            for (int i=0; i <nivel; i++) cout << "  ";
            print("Mae de " + this->nome + ": ", '\0', "cinza");
            print(mae->nome);
            // cout << "Mae de " <<this->nome << ": " << mae->nome << "\n";
        }
    }
}

void Pessoa::exibir_descendentes(int nivel) {
    if (filhos.empty()) {
        for (int i=0; i <nivel; i++) cout << "  ";
        print("Não há descendentes cadastrados para: " + this->nome, '\n', "vermelho");
        return;
    }

    for (Pessoa* filho : filhos) {
        for (int i=0; i <nivel; i++) cout << "  ";
        print("Filho de " + nome + ": ", '\0', "cinza");
        print(filho->nome);
        // cout << "Filho de " << this->nome<< " :" << " "<< filho->nome << "\n";
        filho->exibir_descendentes(nivel + 1);
    }
}

void Pessoa::exibir_asc_desc(){
    exibir_ascendentes(1);
    print(nome, '\n', "amarelo");
    exibir_descendentes(1);
}

void Pessoa::exibir_info(){
    cout << "Nome: " << nome << "\n";
    cout << "Nascimento: " << nascimento.str() << "\n";
    cout << "Genero: " << genero << "\n";
    cout << "Descendentes: " << contar_descendentes() << "\n"; 
    cout << "____________________________________________\n";
}

void Pessoa::exibir_menu(){
    if (menu.opcoes.empty()) criar_menu();
    menu.imprimir();
}

void Pessoa::criar_menu(){
    menu = {{
        {"Exibir Ascendentes",                [this]() {
            exibir_ascendentes(1);
            print(nome, '\n', "amarelo");
        }},
        {"Exibir Descendentes",               [this]() {
            print(nome, '\n', "amarelo");
            exibir_descendentes(1);
        }},
        {"Exibir Ascendentes e descendentes", [this]() {exibir_asc_desc();}},
        {"Remover da Árvore",                 [this]() {print("Funcionalidade nao implementada", '\n', "vermelho");}},
        {"Exibir Árvore",                     [this]() {exibir_arvore(0);}},
    }};
}

void Pessoa::exibir_arvore(int nivel){
    // Se essa pessoa nao tem filhos, exibir somente o nome e retorna
    if (filhos.empty()) {
        print(to_string(nivel), ' ', "cinza");
        for (int i = 0; i < nivel; i++) print("--", '\0', "cinza");
        print(nome, '\n', "vermelho");
        return;
    }

    map<pair<Pessoa*, Pessoa*>, vector<Pessoa*>> casais;     ///< Map com um pair de pessoas (casal) e um vetor de pessoas (filhos) 
    // Agrupa filhos por casal
    for (Pessoa* filho : filhos) {
        pair<Pessoa*, Pessoa*> casal = {filho->pai, filho->mae};
        casais[casal].push_back(filho); 
    }

    // Para cada par de casais exibir pai + mae e depois filhos
    for (auto par : casais){
        auto casal_pai = par.first.first;
        auto casal_mae = par.first.second;
        auto filhos_casal = par.second;

        print(to_string(nivel), ' ', "cinza");
        for (int i = 0; i < nivel; i++) print("--", '\0', "cinza");

        // Exibe o casal
        if (casal_pai && casal_mae) {
            print(casal_pai->nome, ' ');
            print("+", ' ', "amarelo");
            print(casal_mae->nome);
        }
        else if (casal_pai) {
            print(casal_pai->nome, ' ');
            print("+", ' ', "amarelo");
            print("???", '\n', "cinza");
        }
        else if (casal_mae){
            print("???", ' ', "cinza");
            print("+", ' ', "amarelo");
            print(casal_mae->nome);
        } 
        else {
            print("??? + ???", '\n', "cinza");
        }

        // Exibe os filhos desse casal (recursivamente)
        for (auto f: filhos_casal) {
            f->exibir_arvore(nivel + 1);
        }
    }
}

int Pessoa::contar_descendentes(){
    if (filhos.empty()) return 0;
    int contagem = filhos.size();
    for (Pessoa* f : filhos) {
        contagem += f->contar_descendentes();
    }
    return contagem;
}

vector<Pessoa*> Pessoa::conexoes(){
    vector<Pessoa*> resultado = filhos;
    if (pai != nullptr) resultado.push_back(pai);
    if (mae != nullptr) resultado.push_back(mae);
    return resultado;
}