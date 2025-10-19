/**
 * Aqui será declarada a struct Arvore e suas funcionalidades
 */

#include "Pessoa.h"
#include "util.h"
#include <vector>
#include <unordered_map>

struct Arvore
{   
    string nome;
    vector<Opcao> opcoes;
    unordered_map<string, Pessoa*> familia;

    /**
     * @brief Inicializa a arvore
     * @param nm O nome dessa árvore
     */
    Arvore(string nm);
    
    /**
     * @brief Imprime no console as opcoes para manipular a arvore
     */  
    void imprimir_menu();

    /**
    * @brief Processa o input do usuario e chama a funcao correta
    * @param resposta A opcao que o usuario escolheu
    * @return verdadeiro se a funcao for valida, senao falso
    */
    bool processar_resposta(int resposta);


    /**
     * Funcionalidade obrigatória 1,2
     * 
     * Adiciona uma pessoa nessa árvore e define seus pais
     */
    void adicionar_pessoa();

    /**
    * @brief Funcionalidade obrigatória 5 
    * Busca pessoas por nome e exibe no console
    */
    void buscar_pessoas(); 
    
    
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
     * Funcionalidade opcional
     * 
     * Calcula o grau de parentesco entre duas pessoas
     * 
     * @param a Pessoa A
     * @param b Pessoa B
     * @returns Um numero inteiro representando o grau
     */
    int parentesco(Pessoa *a, Pessoa *b);
    
    
    /**
     * Funcionalidade Opcional
     * 
     * Exibe no console todas as pessoas de uma determinada geraão
     * 
     * @param geracao Um numero inteiro (x >= 0) represando a geracao que quer achar 
     */
    void exibir_geracao(int geracao);
};