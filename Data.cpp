#include "Data.h"
#include <sstream>
#include <iomanip>

using namespace std;

int Data::dias_no_mes[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

bool Data::bisexto(int ano){
    bool div4   = ano %   4 == 0;
    bool div100 = ano % 100 == 0;
    bool div400 = ano % 400 == 0;

    return (div4 && !div100) || div400;
}

Data::Data(string data){
    istringstream str(data);
    
    str >> dia;
    str.ignore();
    str >> mes;
    str.ignore();
    str >> ano;
}

int Data::valor() {
    // int qtd_bisextos = ano/4 - ano/100 + ano/400;
    // int dias = 365*ano + qtd_bisextos + dia;
    // for (int i=1; i<mes; i++) {
    //     dias+=dias_no_mes[i];
    // }
    // return dias;

    return ano*10000 + mes*100 + dia;
}

Data::Data(int ddia, int dmes, int dano){
    dia = ddia;
    mes = dmes;
    ano = dano;
}

Data Data::hoje(){
    time_t agora = time(nullptr);
    tm *dtm = localtime(&agora);
    return Data(dtm->tm_mday, dtm->tm_mon+1, dtm->tm_year+1900);
}

bool Data::valido(){
    bool vale = true;
    vale = vale && ( hoje().valor() > valor() );                // Se essa data maior que a data de hoje, ela é invalida
    vale = vale && ( 1 <= mes && mes <= 12 );                   // Validacao de mes
    vale = vale && ( ano >= ANO_MIN );                          // Limite minimo de ano
    int soma = bisexto(ano) && mes == 2;
    vale = vale && ( 1 <= dia && dia <= dias_no_mes[mes]+soma); // Verifica anos bisextos
    return vale;
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
