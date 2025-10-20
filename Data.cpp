#include "Data.h"
#include <sstream>

using namespace std;

int Data::qtd_dias[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};

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
    //return (ano * 10000) + (mes * 100) + (dia);
    int qtd_bisextos = ano/4 - ano/100 + ano/400;
    int dias = 365*ano + qtd_bisextos + dia;
    for (int i=1; i<mes; i++) {
        dias+=qtd_dias[i];
    }
    return dias;
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
    vale = vale && ( hoje().valor() > valor() ); // Se essa data maior que a data de hoje, ela é invalida
    vale = vale && ( 1 <= mes && mes <= 12 );    // Validacao de mes
    vale = vale && ( ano >= ANO_MIN ); // Só será considerado validos, anos a partir do ano minimo, para evitar erros como 12/12/25 quando o usuario quer o ano 2025 e recebe 0025
    int soma = bisexto(ano) && mes == 2;
    vale = vale && ( 1 <= dia && dia <= qtd_dias[mes]+soma);
    return vale;
}
