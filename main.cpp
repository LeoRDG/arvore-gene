#include <iostream>

using namespace std;

struct Pessoa
{
    string nome;
    string nascimento;
    char sexo;

    int geracao;

    Pessoa *pai;
    Pessoa *mae;

    void exibir_asc_desc();     // {3} Função para exibir os ascendentes e descendentes dessa pessoa
    void exibir_descendentes(); // {4} Função para exibir todos os descendentes a partir deste ancestral
    int  contar_descendentes();  // {o} Função para contar quantos descendentes essa pessoa tem
};

struct Arvore
{
    void adicionar_pessoa();               // {1,2} Funcao para adicionar uma pessoa e definir os pais
    Pessoa *encontrar_pessoa(string nome); // {5} Funçao para buscar uma pessoa pelo nome
    void gravar_arvore();                  // {o} Gravar arvore em um arquivo
    void carregar_arvore();                // {o} Carregar arvore de um arquivo
    int parentesco(Pessoa* a, Pessoa* b);  // Funcao para calcular o grau de parentesco entre duas pessoas
    void exibir_geracao(int geracao);      // Funcao para exibir todas as pessoas de uma geracao
};

int main()
{
    return 0;
}
