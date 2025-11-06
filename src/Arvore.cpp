/**
 * Aqui serão implementadas as funcionalidades da Pessoa
 * Funcoes iniciadas com ui, sao funcoes que exigem interacao do usuario
 */

#include "../include/Arvore.h"
#include "../include/Pessoa.h"
#include "../include/util.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <tuple>

using namespace std;


Arvore::Arvore(string nome){
    this->nome = nome;
}


void Arvore::ui_adicionar_pessoa(){
    string nome = pedir_nome();
    char genero =  pedir_genero();
    Data nascimento = pedir_data();

    Pessoa* pessoa = criar_pessoa(nome, genero, nascimento);

    if (!confirmar("Gostaria de definir os pais dessa pessoa?")) return;
    ui_definir_pais(pessoa);
}


void Arvore::ui_definir_pais(Pessoa* pessoa){
    if (pessoa == nullptr) return;

    limpar_tela();
    int resposta;
    print("Definindo os pais de '" + pessoa->nome + "'");
    
    // Filtra apenas homens que nasceram antes da pessoa
    vector<Pessoa*> possiveis_pais = pesquisar_pessoas("", pessoa->nascimento.valor(), 'M');
    exibir_pessoas(possiveis_pais);
    if (possiveis_pais.size() > 0){
        int resposta = ler_int("Escolha uma dessas pessoas para ser o pai: (0) para cancelar ", possiveis_pais.size()) - 1;
        if (resposta >= 0) pessoa->definir_pai(possiveis_pais[resposta]);
    }

    limpar_tela();
    print("Definindo os pais de '" + pessoa->nome + "'");
    
    // Filtra apenas mulheres que nasceram antes da pessoa
    vector<Pessoa*> possiveis_maes = pesquisar_pessoas("", pessoa->nascimento.valor(), 'F');
    exibir_pessoas(possiveis_maes);
    if (possiveis_maes.size() > 0){
        resposta = ler_int("Escolha uma dessas pessoas para ser a mae: (0) para cancelar ", possiveis_maes.size()) - 1;
        if (resposta >= 0) pessoa->definir_mae(possiveis_maes[resposta]);
    }
}


Pessoa* Arvore::ui_buscar_pessoa(){
    // Procura por pessoas com nomes parecidos e se achar, coloca elas em um vetor
    string nome = ler_string("Digite o nome da pessoa que deseja achar, deixe em branco para mostrar todas as pessoas: ");
    limpar_tela();
    print("Pesquisando por '" + nome + "'", '\n', "bg_cinza");
    vector<Pessoa*> encontradas = pesquisar_pessoas(nome);

    // Se nenhuma pessoa for encontradas, retornar nullptr
    if ( encontradas.empty() ) {
        print("Nenhuma pessoa encontrada", '\n', "vermelho");
        return nullptr;
    }

    // Se só achar uma pessoa, retornar ela
    if (encontradas.size() == 1) return encontradas.at(0);
    
    // Se achar muitas pessoas, exibir e pedir clarificaçao
    // Pessoas sao exibidas a partir de 1, se o usuario digitar 0, retornar nullptr
    exibir_pessoas(encontradas);
    int indice = ler_int("Qual pessoa voce estava procurando? (0 para cancelar) ", encontradas.size(), 0) - 1;
    return (indice < 0) ? nullptr : encontradas.at(indice);
}


void Arvore::ui_pessoa_menu(){
    // Busca pessoa para definir os pais
    Pessoa* p = ui_buscar_pessoa();
    if (p == nullptr) return;
    
    while (p->menu.continua){
        p->exibir_info();
        p->exibir_menu();
        p->menu.esperar_resposta();
        if (p->menu.continua) pausar();    // o if evita pausar duas vezes (pause desse menu e do anterior) quando sair
    }
}


void Arvore::ui_exibir_por_geracao() {
    int geracao = ler_int("Digite a geracao que esta procurando: ");
    vector<Pessoa*> encontradas = pesquisar_pessoas("", INT_MAX, '\0', geracao);

    if (encontradas.empty()) {
        print("Nenhuma pessoa encontrada nessa geracao.", '\n', "vermelho");
        return;
    }

    exibir_pessoas(encontradas);
}


void Arvore::ui_exibir_parentesco() {
    exibir_pessoas(familia);
    int indiceA = ler_int("Qual a primeira pessoa? ", familia.size(), 1) - 1;
    int indiceB = ler_int("Qual a segunda pessoa? ", familia.size(), 1) - 1;
    Pessoa* pessoaA = familia[indiceA];
    Pessoa* pessoaB = familia[indiceB];

    auto [distancia, caminho] = calcular_distancia(pessoaA, pessoaB);
    
    if (distancia < 0) print("As duas pessoas nao tem nenhum grau de parentesco", '\n', "vermelho");
    else if (distancia == 0) print("As duas pessoas sao as mesmas, parentesco: 0", '\n', "amarelo");
    else {
        while (!caminho.empty()) {
            Pessoa* atual = caminho.top();
            caminho.pop();

            if (atual == pessoaA || atual == pessoaB) print(atual->nome, '\0', "amarelo");
            else print(atual->nome, '\0', "cinza");
            
            if (atual != pessoaB) print(" -> ", '\0', "verde");
            else print();
        }
        print("O grau de parentesco entre essas duas pessoas e: ", '\0');
        print(to_string(distancia), '\n', "verde");
    }
}


void Arvore::exibir_info(){
    print("Data: " + Data::hoje().str());
    print("Nome da Arvore: " + nome);
    print("Quantidade de pessoas:", ' ');
    print(to_string(familia.size()), '\n', "verde");
}


void Arvore::exibir_pessoas(vector<Pessoa*> pessoas){
    printf("%zu/%zu Pessoas encontradas\n", pessoas.size(), familia.size());
    print("________________________________________________");
    cout << "ID. ";
    Pessoa::exibir_cabecario();

    for (int i=0; i<pessoas.size(); i++) {
        // Alterna cor de fundo para facilitar leitura
        string cor_fundo = (i%2 == 0) ? "bg_cinza" : "padrao";
        cout << cores.at(cor_fundo);                                            /// Muda o background do numero
        cout << cores.at("verde") << setw(4) << i+1 << cores.at("padrao");      /// Muda a cor do numero para verde
        pessoas[i]->exibir_linha(cor_fundo);
    }
}


void Arvore::exibir_menu() {
    if (menu.opcoes.empty()) criar_menu();
    menu.imprimir();
}


void Arvore::criar_menu() {
    // As opcoes do menu sao criadas aqui usando a struct Opcao
    // Esse metodo foi escolhido para nao precisar usar switch/if para cada caso
    // tornando o código mais modular e fácil de manter.
    
    menu = { {
        { "Adicionar pessoa",                     [this]() {ui_adicionar_pessoa();} },
        { "Buscar pessoa",                        [this]() {ui_pessoa_menu();} },
        { "Definir pais de uma pessoa",           [this]() {ui_definir_pais(ui_buscar_pessoa());} },
        { "Mostrar geracoes",                     [this]() {ui_exibir_por_geracao();}},  
        { "Exibir parentesco entre 2 pessoas",    [this]() {ui_exibir_parentesco();}},
        { "Sair",                                 [this]() {menu.continua = false;}},
        //{ "Salvar" ,                              [this]() {salvar();} },
        //{ "Carregar" ,                            [this]() {carregar();} },
    } };
}


void Arvore::salvar(){
    ofstream arquivo(nome + EXTENSAO);

    for (auto pessoa : familia) {
        arquivo << pessoa->serializar() << "\n";
    }

    arquivo.close();
}


void Arvore::carregar(){
    ifstream arquivo(nome + EXTENSAO);
    if (!arquivo.is_open()) return;

    string linha;
    // Map para buscar pessoa pela chave na hora de definir pais
    unordered_map<string, Pessoa*> pessoas;
    // Guarda pessoas e chaves dos pais para vincular depois
    vector<tuple<Pessoa*, string, string>> pessoas_pais;

    // Primeiro loop para criar todas as pessoas a partir do csv
    while ( getline(arquivo, linha) ) {
        auto [p, chave_pai, chave_mae] = Pessoa::deserializar(linha);
        if (p == nullptr) continue;
        familia.push_back(p);
        pessoas.insert({p->chave(), p});
        pessoas_pais.push_back({p, chave_pai, chave_mae});
    }

    // Segundo loop para definir os pais das pessoas usando as chaves guardadas
    for (auto pessoa : pessoas_pais){
        auto [p, pai, mae] = pessoa;
        if (!pai.empty() && pessoas.count(pai)) p->definir_pai(pessoas[pai]);
        if (!mae.empty() && pessoas.count(mae)) p->definir_mae(pessoas[mae]);
    }

    arquivo.close();
}


Pessoa* Arvore::criar_pessoa(string nome, char genero, Data nascimento){
    Pessoa *pessoa = new Pessoa{nome, nascimento, genero};
    familia.push_back(pessoa);
    return pessoa;
}


vector<Pessoa*> Arvore::pesquisar_pessoas(string nome, int valor_data, char genero, int geracao){
    vector<Pessoa*> encontradas;
    for (auto pessoa : familia) {
        // Se todos os filtros retornarem true, adicionar a pessoa atual ao vetor
        bool filtro_nome = contem(pessoa->nome, nome);
        bool filtro_data = pessoa->nascimento.valor() < valor_data;
        bool filtro_genero = genero == '\0' || pessoa->genero == genero;
        bool filtro_geracao = geracao == -1 || pessoa->geracao == geracao;

        if (filtro_nome && filtro_data && filtro_genero && filtro_geracao) {
            encontradas.push_back(pessoa);
        }
    }
    return encontradas;
}


pair<int, stack<Pessoa*>> Arvore::calcular_distancia(Pessoa* a, Pessoa* b) {
    // Algoritmo BFS (https://www.youtube.com/watch?v=xlVX7dXLS64)
    // Encontra o menor caminho entre duas pessoas
    // Explora nivel por nivel ate encontrar a pessoa destino

    queue<Pessoa*> fila;
    fila.push(a);                                          // Inicia com a pessoa origem
    unordered_set<Pessoa*> visitadas;                      // Evita visitar a mesma pessoa duas vezes
    unordered_map<Pessoa*, int> distancia_map = {{a, 0}};  // Distancia de cada pessoa ate a origem
    unordered_map<Pessoa*, Pessoa*> anterior;              // Guarda de onde veio cada pessoa (para reconstruir o caminho)

    while(!fila.empty()) {
        Pessoa* atual = fila.front();
        fila.pop();
        
        // Se encontrou o destino, para a busca
        if (atual == b) break;
        
        // Se ja foi visitada, pula para a proxima
        if (visitadas.count(atual) == 1) continue;
        visitadas.insert(atual);
        
        // Explora todas as conexoes (pais e filhos) da pessoa atual
        for (Pessoa *p : atual->conexoes()) {
            if (visitadas.count(p) == 1) continue;      // Se ja foi visitada, ignora
            fila.push(p);                               // Adiciona na fila para explorar depois
            distancia_map[p] = distancia_map[atual]+1;  // A distancia eh a distancia do atual + 1
            anterior[p] = atual;                        // Guarda que veio do atual (para reconstruir caminho depois)
        }
    }

    // Se b nao foi encontrado, nao tem parentesco
    if (anterior.count(b) == 0) return {-1, {}};

    // Reconstroi o caminho de b até a usando o map anterior
    stack<Pessoa*> caminho;
    Pessoa *atual = b;
    
    // Volta pelo mapa anterior ate chegar na origem (a)
    while (atual != a) {
        caminho.push(atual);
        atual = anterior[atual];
    }
    // Se a e b nao for a mesma pessoa, adiciona a origem no caminho
    if (distancia_map[b] > 0) caminho.push(a);

    return {distancia_map[b], caminho};
}
