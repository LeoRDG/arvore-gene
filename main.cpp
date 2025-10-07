/**
 * Aqui rodará o programa principal
 * 
 * Contém o loop principal da CLI para gerenciar pessoas
 * e relações da árvore, imprimir e salvar os dados em arquivos
 */

#include <iostream>
#include "Arvore.h"
#include "Pessoa.h"

using namespace std;

int main()
{
    Arvore *arvore = new Arvore{};
    Pessoa *pessoa = new Pessoa{"Pessoa teste", "01/01/2312", 'm'};

    pessoa->mostrar();

    return 0;
}
