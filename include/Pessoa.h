/**
 * Declaração da estrutura Pessoa que representa uma pessoa na árvore genealógica
 */

#pragma once // Garante que esse header seja incluso uma só vez
#include <string>
#include <vector>
#include <utility>
#include <unordered_set>
#include "util.h"
#include "Menu.h"

using namespace std;

struct Pessoa
{
    string nome;                             ///< Nome completo da pessoa
    Data nascimento;                         ///< Data de nascimento
    char genero;                             ///< Gênero ('M' para masculino, 'F' para feminino)

    static const int GERACAO_INICIAL = -1;   ///< Valor inicial da geracai
    int geracao = GERACAO_INICIAL;           ///< Geracao da pessoa (-1 = não definida)

    Pessoa *pai = nullptr;                   ///< Ponteiro para o pai (nullptr se nao definido)
    Pessoa *mae = nullptr;                   ///< Ponteiro para a mae (nullptr se nao definido)
    vector<Pessoa*> filhos;                  ///< Vetor com os filhos
    
    Menu menu;                               ///< Menu de opcoes para interacao com o usuario

    static const int L_NOME = 30;            ///< Largura da coluna Nome
    static const int L_NASC = 15;            ///< Largura da coluna Nascimento
    static const int L_PAIS = 15;            ///< Largura da coluna Pai/Mae
    static const int L_GEN  = 10;            ///< Largura da coluna Genero
    static const int L_GER  = 10;            ///< Largura da coluna Geracao


    /**
     * @brief Exibe o cabeçalho da tabela de pessoas
     * 
     * Imprime os nomes das colunas formatados com as larguras definidas
     * pelas constantes L_NOME, L_NASC, etc.
     */
    static void exibir_cabecario();


    /**
     * @brief Exibe o nome, nascimento, genero, pais e geracao dessa pessoa
     * @param cor A cor (padrao = padrao)
     */
    void exibir_linha(string cor="padrao");
    
    
    /**
     * @brief Exibe recursivamente todos os ascendentes dessa pessoa
     */
    void exibir_ascendentes(int nivel);


    /**
     * @brief Exibe recursivamente todos os descendentes dessa pessoa
     */
    void exibir_descendentes(int nivel);
    

    /**
     * @brief Exibe recursivamente todos os ascendentes e descendentes
     * 
     * Primeiro exibe todos os ascendentes e depois
     * todos os descendentes.
     */
    void exibir_asc_desc();


    /**
     * @brief Exibe informacoes dessa pessoa
     * 
     * Mostra nome, nascimento, genero e quantidade de descendentes, pais e filhos.
     */
    void exibir_info();


    /**
     * @brief Exibe o menu de opcoes para esta pessoa
     * 
     * Se o menu ainda não foi criado, chama criar_menu() automaticamente.
     */
    void exibir_menu();


    /**
     * @brief Exibe uma sub-arvore começando dessa pessoa
     * 
     * Exibe recursivamente a pessoa e seus descendentes, usando indentaçao
     * para mostrar a hierarquia.
     * @param nivel Nível atual na árvore (0 = esta pessoa, 1 = filhos, 2 = netos, etc.)
     */
    void exibir_arvore(int nivel=0);


    /**
     * @brief Conta recursivamente o total de ascendentes (diretos e indiretos)
     * @param visitadas Set de pessoas já visitadas (nullptr para criar novo set)
     * @returns Número total de ascendentes desta pessoa
     */
    int contar_ascendentes(unordered_set<Pessoa*>* visitadas = nullptr);


    /**
     * @brief Conta recursivamente o total de descendentes (diretos e indiretos)
     * @param visitadas Set de pessoas já visitadas (nullptr para criar novo set)
     * @returns Número total de descendentes desta pessoa
     */
    int contar_descendentes(unordered_set<Pessoa*>* visitadas = nullptr);


    /**
     * @brief Define o pai dessa pessoa
     * 
     * Adiciona essa pessoa a lista de filhos do pai
     * e calcula a geracao
     * @param pai Ponteiro para a pessoa que será o pai
     */
    void definir_pai(Pessoa* pai);


    /**
     * @brief Define a mae dessa pessoa
     * 
     * Adiciona essa pessoa a lista de filhos da mae 
     * e calcula a geracao
     * @param mae Ponteiro para a pessoa que será a mae
     */
    void definir_mae(Pessoa* mae);


    /**
     * @brief Calcula e define a geracao desta pessoa baseada nos pais
     * 
     * A geracao será a maior geracao entre a do pai e da mae + 1.
     * Atualiza recursivamente a geracao de todos os filhos.
     * 
     * Pequeno problema, se mudar os pais, a nova geracao só será atualizada quando reiniciar o programa
     */
    void definir_geracao();


    /**
     * @brief Cria o menu para esta pessoa
     * 
     * Cria as opcoes definidas dentro da funcao
     */
    void criar_menu();


    /**
     * @brief Retorna apenas o primeiro nome
     * @returns Primeiro nome da pessoa ou nome completo se nao houver espacos
     */
    string primeiro_nome();


    /**
     * @brief Gera uma chave única para identificar essa pessoa
     * 
     * Formato: "AAAAMMDDnome"
     * @returns String contendo valor numérico da data + nome em minusculas
     */
    string chave();


    /**
     * @brief Retorna todas as pessoas diretamente conectadas (pais e filhos)
     * 
     * Usado para achar o grau de parentesco.
     * @returns Vetor contendo pai, mae e filhos
     */
    vector<Pessoa*> conexoes();


    /**
     * @brief Converte os dados da pessoa para formato CSV
     * 
     * Formato: "ano,mes,dia,nome,genero,chave_pai,chave_mae"
     * @returns String com dados separados por vírgula
     */
    string serializar();


    /**
     * @brief Cria uma pessoa a partir de uma string CSV
     * 
     * Os pais devem ser vinculados depois que todas as pessoas 
     * forem criadas usando as chaves retornadas.
     * @param dados String no formato CSV (ano,mes,dia,nome,genero,pai,mae)
     * @returns Tupla contendo:
     * 
     *   - Pessoa*: Ponteiro para a pessoa criada ou nullptr
     * 
     *   - string: Chave do pai (pode estar vazia)
     * 
     *   - string: Chave da mae (pode estar vazia)
     */
    static tuple<Pessoa*, string, string> deserializar(string dados);
};
