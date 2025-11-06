/**
 * Aqui rodará o programa principal
 *
 * Contém o loop principal
 */

#include "../include/Arvore.h"

int main() {
    Arvore arvore = Arvore("arvore");
    arvore.carregar();

    while (arvore.menu.continua) {
        limpar_tela();
        arvore.exibir_info();
        arvore.exibir_menu();
        arvore.menu.esperar_resposta();
        arvore.salvar();
        if (arvore.menu.continua) pausar();
    }
    for (auto p: arvore.familia) delete p;
    return 0;
}
