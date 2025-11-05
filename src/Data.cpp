#include "../include/Data.h"
#include <sstream>
#include <iomanip>

using namespace std;

int Data::dias_no_mes[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

Data::Data(string data){
    istringstream str(data);
    
    str >> dia;
    str.ignore();
    str >> mes;
    str.ignore();
    str >> ano;
}

Data::Data(int dia, int mes, int ano){
    this->dia = dia;
    this->mes = mes;
    this->ano = ano;
}

Data Data::hoje(){
    // tm_mon vai de 0-11, precisa somar 1
    // tm_year conta anos desde 1900, precisa somar 1900
    time_t agora = time(nullptr);
    tm *dtm = localtime(&agora);
    return Data(dtm->tm_mday, dtm->tm_mon+1, dtm->tm_year+1900);
}

bool Data::bisexto(int ano){
    bool div4   = ano %   4 == 0;
    bool div100 = ano % 100 == 0;
    bool div400 = ano % 400 == 0;

    return (div4 && !div100) || div400;
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

int Data::valor() {
    // Converte data para inteiro no formato AAAAMMDD
    // Exemplo: 15/03/1990 -> 19900315
    return ano*10000 + mes*100 + dia;
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
