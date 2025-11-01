/**
 * Aqui será declarada a struct pessoa e suas funcionalidades
 */

#pragma once // Garante que esse header seja incluso uma só vez
#include <string>
#include <vector>
#include "util.h"
#include "Menu.h"

using namespace std;

struct Pessoa
{
    string nome;
    Data nascimento;
    char genero;

    int geracao = -1;

    string chave_pai, chave_mae; // Variaveis temporarias para carregar os pais da pessoa

    Pessoa *pai = nullptr;
    Pessoa *mae = nullptr;
    vector<Pessoa*> filhos;
    Menu menu;

    static const int L_NOME = 30;
    static const int L_NASC = 15;
    static const int L_PAIS = 15;
    static const int L_GEN  = 10;
    static const int L_GER = 10;
    
    /**
     * @returns Retorna o primeiro dessa pessoa
     */
    string primeiro_nome();

    /**
     * @brief Define o pai dessa pessoa
     * @param ppai A pessoa que 'e pai dessa pessoa
     */
    void set_pai(Pessoa*ppai);

    /**
     * @brief Define o pai dessa pessoa
     * @param mmae A pessoa que é mae dessa pessoa
     */
    void set_mae(Pessoa*mmae);

    /**
     * Funcionalidade obrigatória 3
     * 
     * Exibe no console os ascendentes e descendentes dessa pessoa
     */
    void exibir_asc_desc();
    

    /**
     * Funcionalidade obrigatória 4
     * 
     * Exibe no console todos os descendentes dessa pessoa
     */
    void exibir_descendentes();


    /**
    * Funcionalidade obrigatória 4
    *
    * Exibe no console todos os ascendentes dessa pessoa
    */
    void exibir_ascendentes();
    

    /**
     * Funcionalidade opcional
     * 
     * Conta quantos descendentes (diretos e indiretos) essa pessoa tem
     * 
     * @return Quantidade de descendentes
     */
    int contar_descendentes();


    /// @brief Mostra o nome, nascimento e genero dessa pessoa
    void mostrar();

    /**
     * Funcionalidade opcional
     *
     * Define um valor para a geração para posteriormente apresentar a geração por nível
     *
     *
     */

    void definir_geracao(int nivel);


    /**
    * @brief Gera uma chave para essa pessoa (nome + nascimento),
    * para evitar duplicatas
    * @returns Uma string que representa essa pessoa.
    */
    string chave();


    /**
    * @brief Essa funçao é usada para salvar os dados da pessoa
    * Ela cria uma string com os dados separados por virgula
    * @returns Uma string com os dados dessa pessoa
    */
    string serialize();


    /**
    * @brief Cria uma pessoa a partir de dados salvos
    * @param str Os dados carregados em formato de string
    * @returns O ponteiro de uma struct dessa pessoa
    */
    static Pessoa * deserialize(string dados);

    static void imprimir_cabecario();

    /**
    * @brief Exibe informacoes dessa pessoa
    */
    void mostrar_info();


    /**
     * @brief Mostra o menu com as opcoes para o usuario selecionar
     */
    void mostrar_menu();


    /**
     * @brief Cria as opcoes do menu
     */
    void criar_opcoes();


    /**
     * @brief Funcao para listar a arvore partindo dessa pessoa
     * @param s A "geraçao" atual, começa do 0, filhos -> 1, netos -> 2, etc..
     */
    void exibir_arvore(int s=0);

    /**
     * @brief Encontra outra pessoa relacionada
     * @param p A pessoa à encontrar
     * @returns Um numero que representa o grau de parentesco entre essas duas pessoas
     */
    int find(Pessoa *p);

    
    /**
     * @brief Funcao para pegar as pessoas diretamente conectadas a essa pessoa
     * @returns Um vetor com os pais e os filhos dessa pessoa
     */
    vector<Pessoa*> conexoes();
};