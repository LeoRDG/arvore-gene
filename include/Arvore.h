/**
 * Aqui será declarada a struct Arvore e suas funcionalidades
 */

#include "Pessoa.h"
#include "util.h"
#include <vector>
#include <stack>
#include <climits>
#include "Menu.h"


struct Arvore
{   
    string nome;
    Menu menu;
    vector<Pessoa*> familia; 

    /**
     * @brief Inicializa a arvore
     * @param nm O nome dessa árvore
     */
    Arvore(string nm);


    /**
     * Funcionalidade obrigatória 1,2
     * 
     * Adiciona uma pessoa nessa árvore e define seus pais
     */
    void ui_adicionar_pessoa();

    /**
     * @brief funcao para definir os pais de uma pessoa
     * @param pessoa A pessoa para quais os pais serao definidos
     */
    void ui_definir_pais(Pessoa*pessoa);

    /**
    * @brief Funcionalidade obrigatória 5 
    * Busca pessoas por nome e exibe no console
    */
    void ui_buscar_pessoa(); 

    /**
     * Funcionalidade Opcional
     * 
     * Exibe no console todas as pessoas de uma determinada geraão
     * 
     * @param geracao Um numero inteiro (x >= 0) represando a geracao que quer achar 
     */
    void ui_exibir_por_geracao();

    /**
     * Funcionalidade opcional
     * 
     * Calcula o grau de parentesco entre duas pessoas
     * 
     * @param a Pessoa A
     * @param b Pessoa B
     * @returns Um numero inteiro representando o grau
     */
    void ui_exibir_parentesco();

    /**
     * @brief Exibe informacoes simples dessa arvore
     */
    void exibir_info();

    /**
     * @brief Dada um vetor de pessoas, exibe cada uma delas
     * @param pessoas O vetor de pessoas
     */
    void exibir_pessoas(vector<Pessoa*> pessoas);

    /**
     * @brief Imprime no console as opcoes para manipular a arvore
     */  
    void exibir_menu();

    /**
     * @brief Cria o menu dessa arvore
     */
    void criar_menu();
    
    /**
     * @brief Funcionalidade opcional
     * 
     * Salva essa arvore em um arquivo
     */
    void salvar();
    
    /**
     * Funcionalidade opcional
     * 
     * Carrega a arvore de um arquivo
     */
    void carregar();
    
    /**
     * @brief cria uma pessoa e adiciona à familia
     * @returns Um ponteiro da pessoa que foi criada
     */
    Pessoa* criar_pessoa(string nome, char genero, Data nascimento);

    /**
     * @brief Pesquisa por pessoas usando alguns parametros
     * @param 
     */
    vector<Pessoa*> query(string nome="", int dt_valor = INT_MAX, char genero='\0', int geracao=-1);

    /**
     * @brief Calcula a distancia entre duas pessoas
     * @param a, b As duas pessoas para achar a distancia entre elas
     * @returns Um par com um inteiro representando a distancia entre as duas pessoas
     * E um vetor de pessoas que representa o caminho para chegar de uma a outra
     */
    static pair<int, stack<Pessoa*>> calcular_distancia(Pessoa*a, Pessoa*b);

};