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
        cout << cores.at("verde");
        valido = (cin >> resposta) && (min <= resposta && resposta <= max);
        ignore_tudo();
        cout << cores.at("padrao");
        if (valido) return resposta;
        print("INPUT INVALIDO");
    }
}

string ler_string(string msg) {
    string resposta;
    cout << msg;
    cout << cores.at("amarelo");
    getline(cin, resposta);
    cout << cores.at("padrao");
    return resposta;
}

string pedir_nome() {
    string nome;
    
    while (true) {
        nome = ler_string("Digite o nome da pessoa: ");
        
        // Remove espaços em branco no início e fim
        while (nome.front() == ' ') nome = nome.substr(1);
        while (nome.back() == ' ') nome = nome.substr(0, nome.size()-1);

        nome = minusculas(nome);

        // Verifica se os char sao apenas letras ou espaco
        bool valido = true;
        for (char c : nome) {
            valido = (isalpha(c) || c == ' ');
            if (!valido) break;
        }
        
        // Retorna o nome se for maior que 7 caracteres
        // contem pelo menos um espaco
        // contem apenas letras
        if (nome.size() > 7 && nome.find(' ') != string::npos && valido) {
            return nome;
        }
        
        print("Nome inválido. Digite um nome válido.", '\n', "vermelho");
    }
}

char ler_char(string msg) {
    string resposta;

    while (true) {
        cout << msg;
        cout << cores.at("rosa");
        getline(cin, resposta);
        cout << cores.at("padrao");
        if (resposta.size() == 1) return resposta[0];
        cout << "INPUT INVALIDO\n";
    }
}

Data pedir_data(){
    while (true) {
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

string minusculas(string str){
    string result;
    for (char c : str) result += tolower(c);
    return result;
}

bool contem(string str1, string str2){
    string menor = str1;
    string maior = str2;

    if ( str1.size() < str2.size() ) {
        menor = str1;
        maior = str2;
    } else {
        menor = str2;
        maior = str1;
    }

    maior = minusculas(maior);
    menor = minusculas(menor);

    int index = maior.find(menor);
    return (index >=0 and index < maior.size());
}

void limpar_tela(){
    cout << "\033c";
}

void print(string str, char end, string cor){
    // Se uma cor foi informada e não for vazia ou "padrao"
    if (!cor.empty() && cor != "padrao") {
        // Verifica se a cor existe no mapa, caso contrario usa padrão
        cor = cores.count(cor) ? cores.at(cor) : cores.at("padrao");
        cout << cor << str << cores.at("padrao") << end;
    } else {
        // Imprime sem cor
        cout << str << end;
    }
}

bool confirmar(string msg) {
    string resposta;
    print(msg);
    getline(cin, resposta);
    resposta = minusculas(resposta);
    if (resposta ==  "sim" || resposta == "s") return true;
    return false;
}

string limite_str(string str, int max){
    if (str.size() <= max) return str;
    return str.substr(0, max-2) + "..";
}
