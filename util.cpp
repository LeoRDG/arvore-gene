#include "util.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>

using namespace std;

void ignore_tudo() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int ler_int(string msg) {
    int resposta;
    cout << msg;

    while( !(cin >> resposta) ) {
        cout << "INPUT INVALIDO\n";
        cout << msg;
        ignore_tudo();
    }

    ignore_tudo();
    return resposta;
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

string Data::str(){
    string resposta;
    stringstream str;
    str << setfill('0');
    str << setw(2) << dia << "/";
    str << setw(2) << mes << "/";
    str << setw(4) << ano;
    str >> resposta;
    return resposta;
}


Data pedir_data(){
    Data data = Data( ler_string("Digite a data de nascimento (dd/mm/aaaa): ") );
    while (!data.valido()) {
        cout << "DATA INVALIDA\n";
        data = Data( ler_string("Digite a data de nascimento (dd/mm/aaaa): ") );
    }
    return data;
}

char pedir_genero(){
    char gen = toupper( ler_char("Digite o genero (m,f): ") );
    while (true) {
        if (gen == 'M' || gen == 'F') return gen;
        cout << "GENERO INVALIDO\n";
        gen = toupper( ler_char("Digite o genero (m,f): ") );
    }
}

void pausar() {
    cout << "Pressione Enter para continuar";
    cin.get();
}

string to_lower_str(string str){
    string result;
    for (char c: str){
        result += tolower(c);
    }
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
    cout << "\033c";
}

void print(string str, char end){
    cout << str << end;
}
