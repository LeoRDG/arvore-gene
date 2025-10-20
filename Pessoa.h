/**
 * Aqui será declarada a struct pessoa e suas funcionalidades
 */

#pragma once // Garante que esse header seja incluso uma só vez
#include <string>
#include <vector>
#include "util.h"

using namespace std;

struct Pessoa
{
    string nome;
    Data nascimento;
    char genero;

    int geracao;

    Pessoa *pai = nullptr;
    Pessoa *mae = nullptr;
    vector<Pessoa*> filhos;

    static const int L_NOME = 30;
    static const int L_NASC = 15;
    static const int L_GEN  =  2;
    
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
};