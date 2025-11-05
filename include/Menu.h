#pragma once // Garante que esse header seja incluso uma só vez
#include <functional>
#include <string>
#include <vector>

using namespace std;

/**
 * @brief Representa uma opcao do menu
 */
struct Opcao{
    string descricao;                 ///< Texto exibido ao usuario
    function<void()> func = nullptr;  ///< Funcão a ser executada quando opcao for selecionada
};

/**
 * @brief É um menu com multiplas opcoes
 */
struct Menu{
    vector<Opcao> opcoes;  ///< Lista de opçoes disponíveis no menu
    bool continua = true;         ///< boolean para vereificar se continua no loop desse menu

    /**
     * @brief Imprime as opçoes do menu
     */
    void imprimir();

    /**
     * @brief Processa a resposta do usuario e executa a funcao correspondente
     * @param resposta Numero da opcão selecionada
     * @returns true se a resposta foi válida e processada, se nao false
     */
    bool processar_resposta(int resposta);

    /**
     * @brief Aguarda o usuario informar uma opcao e processa a resposta
     * 
     * Pede um numer intiero ao usuario e chama processar_resposta() automaticamente.
     */
    void esperar_resposta();
};