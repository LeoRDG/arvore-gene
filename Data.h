#include <string>

using namespace std;

/**
 * @brief aqui esta uma estrutura de data
 */
struct Data{
    int dia=0, mes=0, ano=0;
    static const int ANO_MIN = 1000;

    /// @brief Quantidade de dias que cada mes tem no calendario
    static int qtd_dias[13];

    Data(string data);

    Data(int dia, int mes, int ano);

    /**
     * @brief Verifica se os valores de dia, mes, ano sao validos
     * @returns true ou false, sependendo se os valores sao validos ou nao
     */
    bool valido();

    /// @brief Formata a data para o formato brasileiro.
    /// @return A data formatada.
    string str();

    /**
     * @brief Retorna um valor numérico para essa data
     * @returns Um inteiro que representa essa data
     */
    int valor();

    /**
     * Retorna uma data com o dia de hoje.
     */
    static Data hoje();

    /**
     * @brief Calcula se um ano é bisexto ou nao
     * @param anos
     * @returns true ou false se o ano for bisexto ou nao
     */
    static bool bisexto(int ano);
};