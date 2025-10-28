/**
 * Aqui rodará o programa principal
 *
 * Contém o loop principal
 */

#include "../include/Arvore.h"

int main() {
    Arvore arvore = Arvore("arvore");
    arvore.carregar();

    while (true) {
        clear();
        arvore.info_simples();
        arvore.imprimir_menu();
        arvore.menu.esperar_resposta();
        arvore.salvar();
        pausar();
    }
    return 0;
}
