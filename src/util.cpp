#include "../include/util.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
#include <limits>

using namespace std;

void ignore_tudo() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int ler_int(string msg, int max, int min) {
    int resposta;
    bool valido;

    // loop infinito que só acaba com um return quando o inteiro informado pelo usuario for valido
    while (true) {
        cout << msg;
        valido = (cin >> resposta) && (min <= resposta && resposta <= max);
        ignore_tudo();
        if (valido) return resposta;
        print("INPUT INVALIDO");
    }
}

string ler_string(string msg) {
    string resposta;
    cout << msg;
    getline(cin, resposta);
    return resposta;
}

char ler_char(string msg) {
    string resposta;

    while(true) {
        cout << msg;
        getline(cin, resposta);
        if (resposta.size() == 1) return resposta[0];
        cout << "INPUT INVALIDO\n";
    }
}

Data pedir_data(){
    while(true) {
        Data data = Data( ler_string("Digite a data de nascimento (dd/mm/aaaa): ") );
        if (data.valido()) return data;
        print("DATA INVALIDA");
    };
}

char pedir_genero(){
    while (true) {
        char gen = toupper( ler_char("Digite o genero (m,f): ") );
        if (gen == 'M' || gen == 'F') return gen;
        cout << "GENERO INVALIDO\n";
    }
}

void pausar() {
    print("Pressione <Enter> para continuar...");
    cin.get();
}

string to_lower_str(string str){
    string result;
    for (char c: str) result += tolower(c);
    return result;
}

bool contem(string str1, string str2, bool ignore_case){
    string menor = str1;
    string maior = str2;

    if ( str1.size() < str2.size() ) {
        menor = str1;
        maior = str2;
    } else {
        menor = str2;
        maior = str1;
    }

    if (ignore_case) {
        maior = to_lower_str(maior);
        menor = to_lower_str(menor);
    }

    int index = maior.find(menor);
    return (index >=0 and index < maior.size());
}

void clear(){
    cout << "\ec";
}

void print(string str, char end){
    cout << str << end;
}

void print_com_cor(string str, string cor) {
    // Verifica se a cor existe, .count() retorna 0 se nao existe
    cor = (bool) cores.count(cor) ? cores.at(cor) : cores.at("padrao");
    cout << cor << str << "\e[0m";
}

bool confirmar(string msg) {
    string resposta;
    print(msg);
    getline(cin, resposta);
    resposta = to_lower_str(resposta);
    if (resposta ==  "sim" || resposta == "s") return true;
    return false;
}
