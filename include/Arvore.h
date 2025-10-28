/**
 * Aqui será declarada a struct Arvore e suas funcionalidades
 */

#include "Pessoa.h"
#include "util.h"
#include <vector>
#include <unordered_map>
#include <climits>
#include "Menu.h"


struct Arvore
{   
    string nome;
    //vector<Opcao> opcoes;
    Menu menu;
    unordered_map<string, Pessoa*> familia; // Foi escolhido usar um map aqui para evitar adicionar duplicatas

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
     * @brief funcao para definir os pais de uma pessoa
     * @param pessoa A pessoa para quais os pais serao definidos
     */
    void definir_pais(Pessoa*pessoa);


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
    void exibir_geracao();


    /**
     * @brief Exibe informacoes simples dessa arvore
     */
    void info_simples();

    
    /**
     * @brief Dada um vetor de pessoas, exibe cada uma delas
     * @param pessoas O vetor de pessoas
     */
    void mostrar_pessoas(vector<Pessoa*> pessoas);


    /**
     * @brief Cria o menu dessa arvore
     */
    void criar_menu();

    
    /**
     * @brief Pesquisa por pessoas usando alguns parametros
     * @param 
     */
    vector<Pessoa*> query(string nome="", int dt_valor = INT_MAX, char genero='\0', int geracao=-1);
};