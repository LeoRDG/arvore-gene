#include "Regex.h"
#include <regex>
#include <iostream>


using namespace std;

const regex Regex::NOME("^[a-zA-ZáéíóúâêôãõçÁÉÍÓÚÂÊÔÃÕÇ]{2,} +[a-zA-ZáéíóúâêôãõçÁÉÍÓÚÂÊÔÃÕÇ]{2,}(?: +[a-zA-ZáéíóúâêôãõçÁÉÍÓÚÂÊÔÃÕÇ]{2,})*$");
const regex Regex::DATA("^\\d{1,2}\\/\\d{1,2}\\/\\d{1,4}$");
const regex Regex::GENERO("^[mMfF]$");

bool valida_nome(string nome) {
    bool result = regex_match(nome, Regex::NOME);
    cout << nome << " -> ";
    cout << result << endl;
    return result;
} 