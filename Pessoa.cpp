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
    cout << setw(L_NASC) << nascimento.str();
    cout << setw(L_GEN) << genero << "\n";
}

void Pessoa::imprimir_cabecario(){
    cout << left << setw(L_NOME) << "Nome";
    cout << setw(L_NASC) << "Nascimento";
    cout << setw(L_GEN) << "Genero" << "\n";
}

string Pessoa::chave(){
    // Junta o nome e o nascimento, removendo espaços e barras
    // e deixando tudo minusculo
    string result;
    for ( char c: to_lower_str(nome) + nascimento.str() ) {
        if (c != ' ' && c != '/') result += c; 
    }
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
    // Usa uma stream de string para separar os dados por virgula
    // e coloca-los em um vetor de strings
    vector<string> v_dados;
    istringstream str(dados);
    string dado;

    while ( getline(str, dado, ',') ){
        v_dados.push_back(dado);
    }

    string nome = v_dados[0];
    char genero = v_dados[1][0];
    Data nascimeneto = Data(v_dados[2]);
    return new Pessoa{nome, nascimeneto, genero};
}
