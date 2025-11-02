#include "../include/Data.h"
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

Data::Data(int dia, int mes, int ano){
    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
}

Data Data::hoje(){
    time_t agora = time(nullptr);
    tm *dtm = localtime(&agora);
    return Data(dtm->tm_mday, dtm->tm_mon+1, dtm->tm_year+1900);
}

bool Data::valido(){
    // Calcula quantos dias o mês tem (considera ano bissexto para fevereiro)
    int dias = dias_no_mes[mes];
    if (mes == 2 && bisexto(ano)) dias = 29;

    if (dia < 1 || dia > dias)    return false;  // Dia deve estar dentro do range válido para o mês
    if (ano < ANO_MIN)            return false;  // Ano deve ser maior ou igual ao mínimo permitido
    if (mes < 1 || mes > 12)      return false;  // Mês deve estar entre 1 e 12
    if (valor() > hoje().valor()) return false;  // Data não pode ser no futuro

    return true;
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
