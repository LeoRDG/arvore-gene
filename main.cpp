/**
 * Aqui rodará o programa principal
 *
 * Contém o loop principal da CLI para gerenciar pessoas
 * e relações da árvore, imprimir e salvar os dados em arquivos
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

void processar_resposta(int resposta)
{
    switch (resposta){
    case 1:
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        break;
    case 6:
        break;
    case 7:
        break;
    case 8:
        break;
    case 9:
        break;

    }

}

int main() {
    Arvore arvore = Arvore();
    int resposta;
    bool valida = true;

    while (true) {
        clear();
        arvore.imprimir_opcoes();
        if (!valida) cout << "Resposta Inválida" << "\n";
        cout << "Digite um número " << "\n";
        cin >> resposta;
        valida = arvore.processar_resposta(resposta);
    }
    return 0;
}
