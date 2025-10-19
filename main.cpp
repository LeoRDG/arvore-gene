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

int main() {
    Arvore arvore = Arvore();
    int resposta;
    bool resposta_valida = true;

    while (true) {
        clear();
        arvore.imprimir_menu();
        arvore.processar_resposta( ler_int("Digite um número: ") );
        pausar();
    }
    return 0;
}
