/**
 * Aqui será declarada a struct Arvore e suas funcionalidades
 */

#include "Pessoa.h"
#include "Opcao.h"
#include <vector>

struct Arvore
{
    vector<Opcao> opcoes;
    vector<Pessoa*> familia;

    /// @brief Constructor
    Arvore();
    
    /// @brief Imprime no console as opcoes para manipular a arvore
    void imprimir_opcoes();

    /// @brief Processa o input do usuario e chama a funcao correta
    /// @param resposta A opcao que o usuario escolheu
    /// @return verdadeiro se a funcao for valida, senao falso
    bool processar_resposta(int resposta);


    /**
     * Funcionalidade obrigatória 1,2
     * 
     * Adiciona uma pessoa nessa árvore e define seus pais
     */
    void adicionar_pessoa();


    /// @brief Funcionalidade obrigatória 5 
    /// Busca uma pessoa pelo nome dela
    /// @return A pessoa encontrada
    Pessoa *encontrar_pessoa(); 
    
    
    /**
     * Funcionalidade opcional
     * 
     * Salva essa arvore em um arquivo
     */
    void gravar_arvore();
    
    
    /**
     * Funcionalidade opcional
     * 
     * Carrega a arvore de um arquivo
     */
    void carregar_arvore();
    
    
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