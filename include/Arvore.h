#include "Pessoa.h"
#include "util.h"
#include <vector>
#include <stack>
#include <climits>
#include "Menu.h"


/**
 * @struct Arvore
 * @brief Representa uma árvore genealógica
 */
struct Arvore
{   
    string nome;                    ///< Nome da árvore
    Menu menu;                      ///< Menu de opcoes para interacao com o usuario
    vector<Pessoa*> familia;        ///< Vetor contendo todas as pessoas da árvore
    
    const string EXTENSAO = ".csv"; ///< Extensão dos arquivos de salvamento/carregamento

    /**
     * @brief Inicializa a árvore com um nome
     * @param nome Nome dessa árvore
     */
    Arvore(string nome);


    /**
     * @brief Funcao paraa adicionar uma nova pessoa à árvore
     * 
     * Pede dados do usuário (nome, gênero, nascimento)
     * e permite definir os pais da pessoa criada.
     */
    void ui_adicionar_pessoa();

    /**
     * @brief Funcao para definir os pais de uma pessoa
     * @param pessoa Pessoa para a qual os pais serão definidos
     * 
     * Pede ao usuário que selecione o pai e mãe a partir
     * de pessoas já cadastradas na árvore.
     */
    void ui_definir_pais(Pessoa* pessoa);

    /**
     * @brief Funcao para buscar pessoas na arvore por nome
     */
    Pessoa* ui_buscar_pessoa();

    /**
     * @brief Funcao para definir os pais de uma pessoa existente
     * 
     * Permite buscar uma pessoa e definir seus pais
     */
    void ui_pessoa_menu(); 

    /**
     * @brief Funcao para exibir todas as pessoas de uma geração específica
     * 
     * Pede um número ao usuário e exibe todas as pessoas
     * que pertencem a essa geração
     */
    void ui_exibir_por_geracao();

    /**
     * @brief Funcao para calcular e exibir o grau de parentesco entre duas pessoas
     * 
     * Pede para o usuário selecionar duas pessoas e calcula o grau de parentesco
     * entre elas usando o algoritmo BFS, exibindo o caminho e a distancia.
     */
    void ui_exibir_parentesco();

    /**
     * @brief Exibe informacoes simples dessa arvore
     */
    void exibir_info();

    /**
     * @brief Dada um vetor de pessoas, exibe cada uma delas
     * @param pessoas O vetor de pessoas
     */
    void exibir_pessoas(vector<Pessoa*> pessoas);

    /**
     * @brief Imprime no console as opcoes para manipular a arvore
     */  
    void exibir_menu();

    /**
     * @brief Cria o menu dessa arvore
     */
    void criar_menu();
    
    /**
     * @brief Salva essa arvore em um arquivo
     */
    void salvar();
    
    /**
     * @brief Carrega a arvore de um arquivo
     */
    void carregar();
    
    /**
     * @brief cria uma pessoa e adiciona à familia
     * @returns Um ponteiro da pessoa que foi criada
     */
    Pessoa* criar_pessoa(string nome, char genero, Data nascimento);

    /**
     * @brief Pesquisa por pessoas usando filtros opcionais
     * @param nome Nome para buscar (string vazia = retorna todas)
     * @param valor_data Data máxima permitida (INT_MAX = basicamente sem limite)
     * @param genero Filtro por gênero ('\0' = todos os gêneros)
     * @param geracao Geração específica (-1 = todas as gerações)
     * @returns Vetor com todas as pessoas que atendem aos critérios da busca
     */
    vector<Pessoa*> pesquisar_pessoas(string nome="", int valor_data = INT_MAX, char genero='\0', int geracao=-1);

    /**
     * @brief Calcula a distancia e o caminho entre duas pessoas
     * 
     * Usa algoritmo BFS para encontrar o menor caminho/
     * parentesco entre duas pessoas na arvore.
     * 
     * @param a Primeira pessoa (origem)
     * @param b Segunda pessoa (destino)
     * @returns Pair contendo:
     *   - int: Distancia (-1 se não há relacao, 0 se for a mesma pessoa, >0 para grau de parentesco)
     *   - stack<Pessoa*>: Caminho de 'a' até 'b' (vazio se nao há relação)
     */
    static pair<int, stack<Pessoa*>> calcular_distancia(Pessoa* a, Pessoa* b);

};