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
    Arvore arvore = Arvore("arvore");
    arvore.carregar();

    while (true) {
        clear();
        arvore.info_simples();
        arvore.imprimir_menu();
        arvore.processar_resposta( ler_int("Digite um número: ") );
        arvore.salvar();
        pausar();
    }
    return 0;
}
