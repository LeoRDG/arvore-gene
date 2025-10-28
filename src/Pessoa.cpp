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
    geracao = max(geracao, pai->geracao+1);
    pai->filhos.push_back(this);
}

void Pessoa::set_mae(Pessoa*mmae){
    mae = mmae;
    geracao = max(geracao, mae->geracao+1);
    mae->filhos.push_back(this);
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
    // Junta o nome e o valor do nascimento, removendo espaços e barras
    // e deixando tudo minusculo
    string result;
    for ( char c: to_lower_str(nome)) {
        if (c != ' ') result += c; 
    }
    result += to_string(nascimento.valor());
    return result;
}

string Pessoa::serialize(){
    string result;

    result += nome + ",";
    result += genero ;
    result += ',';
    result += nascimento.str() + ",";
    result += (pai == nullptr) ? "null," : pai->chave() + ",";
    result += (mae == nullptr) ? "null" : mae->chave();

    return result;
}

Pessoa * Pessoa::deserialize(string dados){
    // Funcao Estatica
    // Usa uma stream de string para separar os dados por virgula
    // e coloca-los em um vetor de strings
    vector<string> vetor_dados;
    istringstream str(dados);
    string dado;

    while ( getline(str, dado, ',') ){
        vetor_dados.push_back(dado);
    }

    string nome = vetor_dados[0];
    char genero = vetor_dados[1][0];
    Data nascimeneto = Data(vetor_dados[2]);

    Pessoa*pessoa = new Pessoa{nome, nascimeneto, genero};
    pessoa->chave_pai=vetor_dados[3];
    pessoa->chave_mae=vetor_dados[4];

    return pessoa;
}

void Pessoa::definir_geracao(int nivel) {
    if (geracao != -1 && geracao <= nivel) {
        return;
    }
        geracao = nivel;

        for (auto* f : filhos) {
            if (f) f->definir_geracao(nivel +1);
        }
}

void Pessoa::exibir_ascendentes() {
    if (pai == nullptr && mae == nullptr) {
        cout << "Não há ascendentes cadastrados" << "\n";
    }

    else if (pai != nullptr) {
        cout << "Pai :" << pai->nome << "\n";

        pai->exibir_ascendentes();
    }

    else if (mae != nullptr) {
        cout << "Mae :" << mae->nome << "\n";

        mae->exibir_ascendentes();
    }

}

void Pessoa::exibir_descendentes() {
    if (filhos.empty()) {
        cout << "Não há descendentes cadastrados" << "\n";
        return;
    }

    for (Pessoa* filho: filhos) {
        cout << "Filho :" << filho->nome << "\n";
        filho->exibir_descendentes();
    }
}

void Pessoa::info(){
    clear();
    cout << "Nome: " << nome << "\n";
    cout << "Nascimento: " << nascimento.str() << "\n";
    cout << "Genero: " << genero << "\n";
    cout << "____________________________________________\n";
}


void Pessoa::criar_opcoes(){

}
