/**
 * Aqui rodará o programa principal
 *
 * Contém o loop principal
 */

#include <iostream>
#include <vector>
#include <functional>
#include "Arvore.h"
#include "Pessoa.h"

using namespace std;

void print(string str)
{
    cout << str << "\n";
}

void clear(){
    cout << "\033c";
}

int main() {
    Arvore arvore = Arvore();
    int resposta;
    bool resposta_valida = true;

    while (true) {
        //clear();
        arvore.imprimir_opcoes();
        if (!resposta_valida) cout << "Resposta {" << resposta << "} Inválida" << "\n";
        cout << "Digite um número " << "\n";
        cin >> resposta;
        resposta_valida = arvore.processar_resposta(resposta);
    }
    return 0;
}
