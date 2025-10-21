#include <string>
#include <functional>
#include "Data.h"
#pragma once

using namespace std;

struct Opcao{
    string descricao;
    //void(*func)();
    function <void()> func = nullptr;
};


/**
 * @brief Essa funcao le um numero inteiro do usuario
 * @param msg A mensagem que voce quer mostrar ao usuario
 * @returns Um numero inteiro (input do usuario) 
 */
int ler_int(string msg, int max=INT_MAX, int min=0);


/**
 * @brief Essa funcao le apenas um char do usuario
 * @param msg A mensagem que voce quer mostrar ao usuario
 * @returns O char que o usuario informou
 */
char ler_char(string msg);


/**
 * @brief Essa funcao le uma string do usuario
 * @param msg A mensagem que voce quer mostrar ao usuario
 * @returns Uma string com tudo que o usuario escreveu até o enter  
 */
string ler_string(string msg);


/**
 * @brief Limpa o buffer do cin
 */
void ignore_tudo();


/**
 * @brief Converte uma string para letras minusculas.
 * @param str A string que deseja converter.
 * @returns A tring convertida em letras minusculas.
 */
string to_lower_str(string str);


/**
 * @brief Checa se uma string contem a outra substring menor
 * @param str1 
 * @param str2
 * @param ignore_case Se true (padrao), vai ignorar maiuscula e minuscula
 * @returns True se qualquer uma das duas strings contem a outra
 */
bool contem(string str1, string str2, bool ignore_case=true);


/**
 * @brief Pede uma data ao usuario, a funcao só termina se a data for valida.
 * @returns A struct Data com a data que o usu'ario informou.
 */
Data pedir_data();


/**
 * @brief pausa a execucao até que o usuario aperte enter
 */
void pausar();


/**
 * @brief Pede um genero ao usuario (f,m), a funcao só termina se o genero for valido.
 * @returns O genero o usu'ario informou.
 */
char pedir_genero();


/// @brief Limpa o console
void clear();


/**
 * @brief Funcao para facilitar na hora de imprimir coisas no console
 * @param str A mensage para imprimir na tela, por padrao é uma string vazia
 * @param end O que escrever na tela por ultimo, por padrao cria uma nova linha
 */
void print(string str="", char end='\n');


/**
 * @brief Pede para o usuario confirmar se ele quer realizar uma acao
 * @param msg Mensagem para mostrar ao usuario
 * @returns Verdadeiro se o usario digitar sim ou s se nao falso
 */
bool confirmar(string msg);