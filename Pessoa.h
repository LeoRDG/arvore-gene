/**
 * Aqui será declarada a struct pessoa e suas funcionalidades
 */

#pragma once // Garante que esse header seja incluso uma só vez
#include <string>

using namespace std;

struct Pessoa
{
    string nome;
    string nascimento;
    char sexo;

    int geracao;

    Pessoa *pai;
    Pessoa *mae;
    
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
    

    /// @brief Mostra o nome, nascimento e sexo dessa pessoa
    void mostrar();
};