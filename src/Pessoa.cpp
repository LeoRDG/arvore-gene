/**
 * Aqui serão implementadas as funcionalidades da Pessoa
 */

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "../include/Pessoa.h"

using namespace std;

void Pessoa::mostrar(){
    cout << left << setw(L_NOME) << nome;
    cout << setw(L_NASC) << nascimento.str();
    cout << setw(L_GEN) << genero;

    cout << setw(L_PAIS);
    (pai==nullptr) ? cout << "" : cout << pai->primeiro_nome();

    cout << setw(L_PAIS);
    (mae==nullptr) ? cout << "" : cout << mae->primeiro_nome();

    cout << setw(L_GER);
    (geracao == -1) ? cout << "???" : cout << geracao;
    
    cout << "\n";
}

string Pessoa::primeiro_nome(){
    int espaco = nome.find(' ');
    if (espaco >= nome.size() || espaco < 0) return nome; // Se nao encontrar espaco retorna o nome completo
    return nome.substr(0, espaco);
}

void Pessoa::set_pai(Pessoa*ppai){
    pai = ppai;
    pai->filhos.push_back(this);
    if (geracao < 0) definir_geracao();
}

void Pessoa::set_mae(Pessoa*mmae){
    mae = mmae;
    mae->filhos.push_back(this);
    if (geracao < 0) definir_geracao();
}

void Pessoa::imprimir_cabecario(){
    cout << left << setw(L_NOME) << "Nome";
    cout << setw(L_NASC) << "Nascimento";
    cout << setw(L_GEN) << "Genero";
    cout << setw(L_PAIS) << "Pai";
    cout << setw(L_PAIS) << "Mae";
    cout << setw(L_GEN) << "Geracao";
    cout << "\n";
}

string Pessoa::chave(){
    // Junta o nome e o valor do nascimento e deixando tudo minusculo
    return to_string(nascimento.valor()) + to_lower_str(nome);
}

string Pessoa::serialize(){
    stringstream stream;
    string result;

    stream << setfill('0') << setw(4) << nascimento.ano << ","
    << setw(2) << nascimento.mes << ","
    << setw(2) << nascimento.dia << ","
    << nome << ","
    << genero << ',';

    for (Pessoa*p : {pai, mae}) {
        if (p == nullptr) stream << ",";
        else {
            stream << setw(4) << p->nascimento.ano 
            << setw(2) << p->nascimento.mes 
            << setw(2) << p->nascimento.dia
            << to_lower_str(p->nome) << ",";
        }
    }

    getline(stream, result);

    return result;
}

Pessoa * Pessoa::deserialize(string dados){
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

    string nome = vetor_dados[3];
    char genero = vetor_dados[4][0];

    int dia = stoi(vetor_dados[2]);
    int mes = stoi(vetor_dados[1]);
    int ano = stoi(vetor_dados[0]);
    Data nascimento = Data(dia, mes, ano);

    Pessoa*pessoa = new Pessoa{nome, nascimento, genero};

    pessoa->chave_pai = vetor_dados[5];
    pessoa->chave_mae = vetor_dados[6];

    return pessoa;
}

void Pessoa::definir_geracao() {
    // Pega o valor maior entre a geracao do pai e da mae
    int g_pai = (pai == nullptr) ? -1 : pai->geracao;
    int g_mae = (mae == nullptr) ? -1 : mae->geracao;
    int nivel = max(g_pai, g_mae);

    geracao = nivel+1; // Define a geracao dessa pessoa

    // Define a geracao dos filhos
    for (auto* f : filhos) {
        f->definir_geracao();
    }
}

void Pessoa::exibir_ascendentes() {
    if (pai == nullptr && mae == nullptr) {
        cout << " " << "Não há ascendentes cadastrados" << "\n";
        return;
    }
    else{
        if (pai != nullptr) {
            cout << "Pai :" << pai->nome << "\n";
            pai->exibir_ascendentes();
        }

        if (mae != nullptr) {
            cout << "Mae :" << mae->nome << "\n";
            mae->exibir_ascendentes();
        }
    }
}

void Pessoa::exibir_descendentes() {
    if (filhos.empty()) {
        cout << " "<< "Não há descendentes cadastrados" << "\n";
        return;
    }

    for (Pessoa* filho: filhos) {
        cout << "Filho :" << filho->nome << "\n";
        filho->exibir_descendentes();
    }
}

void Pessoa::exibir_asc_desc(){
    
}

void Pessoa::mostrar_info(){
    clear();
    cout << "Nome: " << nome << "\n";
    cout << "Nascimento: " << nascimento.str() << "\n";
    cout << "Genero: " << genero << "\n";
    cout << "____________________________________________\n";
}


void Pessoa::mostrar_menu(){
    if (menu.opcoes.empty()) criar_opcoes();
    menu.imprimir();
}


void Pessoa::criar_opcoes(){
    menu = {{
        {"Mostrar",             [this]() {mostrar();}},
        {"Exibir Ascendentes",  [this]() {exibir_ascendentes();}},
        {"Exibir Descendentes", [this]() {exibir_descendentes();}},
        {"Remover da Árvore",   [this]() {print("Removendo " + nome);}},
        {"Exibir Árvore",       [this]() {exibir_arvore(0);}},
    }};
}

void Pessoa::exibir_arvore(int s){
    for (int i = 0; i < s*2; i++) cout << "-";
    cout << nome << endl;
    for (Pessoa* filho : filhos) filho->exibir_arvore(s+1);
}

vector<Pessoa*> Pessoa::conexoes(){
    vector <Pessoa*> resultado = filhos;
    if (pai != nullptr) resultado.push_back(pai);
    if (mae != nullptr) resultado.push_back(mae);
    return resultado;
}