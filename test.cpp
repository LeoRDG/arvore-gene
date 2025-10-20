#include "util.h"
#include <iostream>
#include <iomanip>

using namespace std;

void test_data(string data, bool expected) {
    Data dt = Data(data);
    //if (dt.valido() == expected) return;
    cout << " FAIL ";
    cout << left << setw(14) << data << " - ";
    if (dt.valido()) cout << "Data Valida  ";
    else cout << "Data Invalida";
    cout << right << setw(26) <<  dt.valor() << " ";
    cout << "\n";
}

int main (){
    
    // válidas
    test_data("01/01/2000", true);
    test_data("29/02/2004", true);  // bissexto
    test_data("28/02/1900", true);
    test_data("31/12/1999", true);
    test_data("30/04/0320", true);
    test_data("15/08/1945", true);

    // inválidas
    test_data("00/01/2020", false);
    test_data("00/11/1020", false);
    test_data("32/01/2020", false);
    test_data("29/02/1900", false);  // 1900 não é bissexto
    test_data("31/04/2020", false);  // abril tem 30 dias
    test_data("31/06/2021", false);  // junho tem 30 dias
    test_data("31/9/321",   false);  // setembro tem 30 dias
    test_data("31/11/1923", false);  // novembro tem 30 dias

    test_data("10/00/2020", false);
    test_data("15/13/2020", false);

    test_data("1/1/0000", false);
    test_data("1/02/0000", false);
    test_data("1/03/0000", false);
    test_data("21/01/10000", false);
    test_data("01/01/-0421", false);

    test_data("1/1/2020", true);
    test_data("2020/01/01", false);
    test_data("31-12-2020", true);
    test_data("abcd", false);
    return 0;
}
