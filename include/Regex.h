#include <regex>

using namespace std;

struct Regex {
    // Expressao regular para validar nome
    static const regex NOME;

    // Expressao regular para validar formato de data
    static const regex DATA;

    // Expressao regular para validar genero;
    static const regex GENERO;

};

bool valida_nome(string);
