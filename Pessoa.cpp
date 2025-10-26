/**
 * Aqui serão implementadas as funcionalidades da Pessoa
 */

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Pessoa.h"

using namespace std;

void Pessoa::mostrar(){
    cout << left << setw(L_NOME) << nome;
    cout << setw(L_GEN) << nascimento.str();
    cout << setw(L_GEN) << genero;

    cout << setw(L_PAIS);
    (pai==nullptr) ? cout << "" : cout << pai->nome;

    cout << setw(L_PAIS);
    (mae==nullptr) ? cout << "" : cout << mae->nome;

    cout << setw(8);
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
    geracao = max(geracao, pai->geracao+1);
    mae->filhos.push_back(this);
}

void Pessoa::imprimir_cabecario(){
    cout << left << setw(L_NOME) << "Nome";
    cout << setw(L_NASC) << "Nascimento";
    cout << setw(L_GEN) << "Genero";
    cout << setw(L_PAIS) << "Pai";
    cout << setw(L_PAIS) << "Mae";
    cout << setw(10) << "Geracao";
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
