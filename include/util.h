/**
 * Aqui tem funcoes auxiliares para input/output, 
 * formatação, validação e manipulação de strings
 */

#pragma once
#include <string>
#include <functional>
#include "Data.h"
#include <climits>
#include <unordered_map>

using namespace std;

/**
 * @brief Mapa de cores ANSI para imprimir com cor
 */
const unordered_map<string, string> cores = {
    {"vermelho", "\033[38;5;9m"},
    {"verde",    "\033[38;5;47m"},
    {"azul",     "\033[38;5;12m"},
    {"amarelo",  "\033[38;5;3m"},
    {"cinza",    "\033[38;5;8m"},
    {"padrao",   "\033[0m"},
    {"rosa",     "\033[38;5;206m"},
};


/**
 * @brief Le um numero inteiro do usuario até que o numero seja válido.
 * @param msg Mensagem exibida ao usuário
 * @param max Valor maximo (padrão: INT_MAX)
 * @param min Valor minimo (padrão: 0)
 * @returns Numero inteiro válido dentro do intervalo informado
 */
int ler_int(string msg, int max=INT_MAX, int min=0);


/**
 * @brief Lê um único caractere do usuário
 * @param msg Mensagem exibida ao usuário
 * @returns Caractere digitado pelo usuário
 */
char ler_char(string msg);


/**
 * @brief Lê uma linha de texto do usuário
 * @param msg Mensagem exibida ao usuário
 * @returns String com tudo que o usuário escreveu até o Enter
 */
string ler_string(string msg);


/**
 * @brief Limpa o buffer do cin para evitar problemas de leitura
 */
void ignore_tudo();


/**
 * @brief Converte uma string inteira para minuscula.
 * @param str String a ser convertida
 * @returns String convertida para minúsculas
 */
string minusculas(string str);


/**
 * @brief Verifica se uma string contem a outra, ignorando maiusculas e minusuclas
 * @param str1 Primeira string
 * @param str2 Segunda string
 * @returns true se qualquer uma das duas strings contem a outra
 */
bool contem(string str1, string str2);


/**
 * @brief Pede uma data em format de string ao usuario até que seja válida
 * @returns Objeto Data válido
 */
Data pedir_data();


/**
 * @brief Pausa a execução até que o usuário pressione Enter
 * 
 * Para permitir que o usuário leia as informacoes antes de continuar.
 */
void pausar();


/**
 * @brief Pede um genero ao usuario ('M' ou 'F')
 * @returns 'M' para masculino ou 'F' para feminino
 */
char pedir_genero();


/**
 * @brief Limpa o console usando sequência ANSI
 */
void limpar_tela();


/**
 * @brief Imprime uma string no console
 * @param str Mensagem a ser impressa (padrao: string vazia)
 * @param end Caracter final a ser impresso (padrão: '\n')
 */
void print(string str="", char end='\n');


/**
 * @brief Imprime uma string colorida no console usando ANSI
 * 
 * "vermelho", "verde", "azul", "amarelo", "cinza", "rosa"
 * @param str Texto a ser impresso
 * @param cor Nome da cor (padrão: "padrao")
 */
void print_com_cor(string str, string cor="padrao");


/**
 * @brief Pede para o usuario confirmar (sim/não)
 * @param msg Mensagem de confirmação para ser exibida
 * @returns true se usuário digitou "sim" ou "s", false caso contrário
 */
bool confirmar(string msg);

/**
 * @brief Limita uma string a um tamanho máximo, 
 * 
 * Se a string for maior que max, retorna os primeiros (max-2) caracteres + ".." 
 * para indicar que a string nao esta completa
 * @param str String a ser limitada
 * @param max Tamanho máximo permitido
 * @returns String truncada se exceder max, ou string original caso contrário
 */
string limite_str(string str, int max);