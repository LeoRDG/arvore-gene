/**
 * Aqui será declarada a struct Arvore e suas funcionalidades
 */

#include "Pessoa.h"

struct Arvore
{
    /**
     * Funcionalidade obrigatória 1,2
     * 
     * Adiciona uma pessoa nessa árvore e define seus pais
     */
    void adicionar_pessoa();
    
    
    /**
     * Funcionalidade obrigatória 5
     * 
     * Busca uma pessoa pelo nome dela
     * 
     * @param nome O nome da pessoa que deseja encontrar
     * @returns A pessoa encontrada
     */
    Pessoa *encontrar_pessoa(string nome); 
    
    
    /**
     * Funcionalidade opcional
     * 
     * Salva essa arvore em um arquivo
     */
    void gravar_arvore();
    
    
    /**
     * Funcionalidade opcional
     * 
     * Carrega a arvore de um arquivo
     */
    void carregar_arvore();
    
    
    /**
     * Funcionalidade opcional
     * 
     * Calcula o grau de parentesco entre duas pessoas
     * 
     * @param a Pessoa A
     * @param b Pessoa B
     * @returns Um numero inteiro representando o grau
     */
    int parentesco(Pessoa *a, Pessoa *b);
    
    
    /**
     * Funcionalidade Opcional
     * 
     * Exibe no console todas as pessoas de uma determinada geraão
     * 
     * @param geracao Um numero inteiro (x >= 0) represando a geracao que quer achar 
     */
    void exibir_geracao(int geracao);
};