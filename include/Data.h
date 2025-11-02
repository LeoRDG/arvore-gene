#include <string>

using namespace std;

/**
 * @struct Data
 * @brief Representa uma data (dia, mês, ano)
 * 
 * Armazena e valida datas, com suporte para anos
 * bisextos e validacao de datas.
 */
struct Data{
    int dia=0, mes=0, ano=0;
    static const int ANO_MIN = 1000;

    /**
     * @brief Array com quantidade de dias em cada mes
     * 
     * Indice 0 não é usado. Indices 1-12 correspondem aos meses.
     * Fevereiro (Indice 2) deve ser ajustado para anos bissextos.
     */
    static int dias_no_mes[13];

    /**
     * @brief Construtor a partir de string no formato "dd/mm/aaaa"
     * @param data String com data no formato brasileiro
     */
    Data(string data);

    /**
     * @brief Construtor a partir de valores individuais
     * @param dia Dia do mes
     * @param mes Mes (1-12)
     * @param ano Ano
     */
    Data(int dia, int mes, int ano);

    /**
     * @brief Verifica se a data é valida
     * 
     * - Data não está no futuro
     * 
     * - Mês está entre 1 e 12
     * 
     * - Ano >= ANO_MIN
     * 
     * - Dia está dentro do intervalo valido para o mes
     * @returns true se a data é válida, false caso contrario
     */
    bool valido();

    /**
     * @brief Formata a data para o formato brasileiro (dd/mm/aaaa)
     * @returns String com data formatada (ex: "15/03/2024")
     */
    string str();

    /**
     * @brief Converte a data para valor numérico
     * @returns Inteiro no formato AAAAMMDD (ex: 20240315)
     */
    int valor();

    /**
     * @brief Retorna a data de hoje
     * @returns Objeto Data com a data atual do sistema
     */
    static Data hoje();

    /**
     * @brief Verifica se um ano é bisexto
     * @param ano Ano a ser verificado
     * @returns true se o ano for bisexto, se nao false
     */
    static bool bisexto(int ano);
};