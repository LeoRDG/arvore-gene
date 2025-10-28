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
        arvore.menu.imprimir();
        int resposta = ler_int("Digite um número: ", arvore.menu.opcoes.size());
        arvore.menu.processar_resposta( resposta );
        arvore.salvar();
        pausar();
    }
    return 0;
}
