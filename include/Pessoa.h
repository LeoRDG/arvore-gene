/**
 * Aqui será declarada a struct pessoa e suas funcionalidades
 */

#pragma once // Garante que esse header seja incluso uma só vez
#include <string>
#include <vector>
#include <utility>
#include "util.h"
#include "Menu.h"

using namespace std;

struct Pessoa
{
    string nome;
    Data nascimento;
    char genero;

    int geracao = -1;

    Pessoa *pai = nullptr;
    Pessoa *mae = nullptr;
    vector<Pessoa*> filhos;
    
    Menu menu;

    // Larguras dos "campos" para exibição das informações
    static const int L_NOME = 30;
    static const int L_NASC = 15;
    static const int L_PAIS = 15;
    static const int L_GEN  = 10;
    static const int L_GER = 10;

    /**
     * @brief Mostra o nome, nascimento e genero dessa pessoa
     */
    void exibir();
    
    /**
     * @returns Retorna o primeiro dessa pessoa
     */
    string primeiro_nome();

    /**
     * @brief Define o pai dessa pessoa
     * @param ppai A pessoa que 'e pai dessa pessoa
     */
    void definir_pai(Pessoa* pai);

    /**
     * @brief Define o pai dessa pessoa
     * @param mmae A pessoa que é mae dessa pessoa
     */
    void definir_mae(Pessoa* mae);

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


    /**
     * Funcionalidade opcional
     *
     * Define um valor para a geração para posteriormente apresentar a geração por nível
     */
    void definir_geracao();


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
    string serializar();


    /**
    * @brief Cria uma pessoa a partir de dados salvos
    * @param str Os dados carregados em formato de string
    * @returns O ponteiro de uma struct dessa pessoa
    */
    static tuple<Pessoa*, string, string> deserializar(string dados);

    static void exibir_cabecario();

    /**
    * @brief Exibe informacoes dessa pessoa
    */
    void exibir_info();


    /**
     * @brief Mostra o menu com as opcoes para o usuario selecionar
     */
    void exibir_menu();


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
     * @brief Funcao para pegar as pessoas diretamente conectadas a essa pessoa
     * @returns Um vetor com os pais e os filhos dessa pessoa
     */
    vector<Pessoa*> conexoes();
};