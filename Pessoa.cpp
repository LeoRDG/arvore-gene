/**
 * Aqui serão implementadas as funcionalidades da Pessoa
 */

#include <iostream>
#include "Pessoa.h"

using namespace std;

void Pessoa::mostrar(){
    cout << nome << endl << nascimento << endl << sexo << endl;
}
