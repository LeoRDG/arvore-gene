/**
 * Aqui serão implementadas as funcionalidades da Pessoa
 */

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <tuple>
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

void Pessoa::exibir(){
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

    for (Pessoa* p : {pai, mae}) {
        if (p == nullptr) stream << ",";
        else {
            stream << setw(4) << p->nascimento.ano 
            << setw(2) << p->nascimento.mes 
            << setw(2) << p->nascimento.dia
            << minusculas(p->nome) << ",";
        }
    }

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

    string nome = vetor_dados[3];
    char genero = vetor_dados[4][0];

    int dia = stoi(vetor_dados[2]);
    int mes = stoi(vetor_dados[1]);
    int ano = stoi(vetor_dados[0]);
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

void Pessoa::exibir_ascendentes() {
    if (pai == nullptr && mae == nullptr) {
        cout << "Não há ascendentes cadastrados para: " << this->nome << "\n";
        return;
    }
    else{
        if (pai != nullptr) {
            cout << "Pai de "<< this->nome << ": " << pai->nome << "\n";
            pai->exibir_ascendentes();
        }

        if (mae != nullptr) {
            cout << "Mae de " <<this->nome << ": " << mae->nome << "\n";
            mae->exibir_ascendentes();
        }
    }
}

void Pessoa::exibir_descendentes() {
    if (filhos.empty()) {
        cout << "Não há descendentes cadastrados para: " << this->nome << "\n";
        return;
    }

    for (Pessoa* filho : filhos) {
        cout << "Filho de " << this->nome<< " :" << " "<< filho->nome << "\n";
        filho->exibir_descendentes();
    }
}

void Pessoa::exibir_asc_desc(){
    exibir_ascendentes();
    exibir_descendentes();
}

void Pessoa::exibir_info(){
    cout << "Nome: " << nome << "\n";
    cout << "Nascimento: " << nascimento.str() << "\n";
    cout << "Genero: " << genero << "\n";
    cout << "Descendentes: " << contar_descendentes() << "\n"; 
    cout << "____________________________________________\n";
}

void Pessoa::exibir_menu(){
    if (menu.opcoes.empty()) criar_opcoes();
    menu.imprimir();
}

void Pessoa::criar_opcoes(){
    menu = {{
        {"Mostrar",                           [this]() {exibir();}},
        {"Exibir Ascendentes",                [this]() {exibir_ascendentes();}},
        {"Exibir Descendentes",               [this]() {exibir_descendentes();}},
        {"Exibir Ascendentes e descendentes", [this]() {exibir_asc_desc();}},
        {"Remover da Árvore",                 [this]() {print_com_cor("Funcionalidade nao implementada", "vermelho");}},
        {"Exibir Árvore",                     [this]() {exibir_arvore(0);}},
    }};
}

void Pessoa::exibir_arvore(int nivel){
    for (int i = 0; i < nivel; i++) print_com_cor("-", "cinza");
    print(nome);
    for (Pessoa* filho : filhos) filho->exibir_arvore(nivel+1);
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