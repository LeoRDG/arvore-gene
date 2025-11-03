/**
 * Aqui serão implementadas as funcionalidades da Pessoa
 */

#include "../include/Arvore.h"
#include "../include/Pessoa.h"
#include "../include/util.h"
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
    //limpar_tela();
    print("Definindo os pais de '" + pessoa->nome + "'");
    
    // Filtra apenas homens que nasceram antes da pessoa
    vector<Pessoa*> possiveis_pais = pesquisar_pessoas("", pessoa->nascimento.valor(), 'M');
    exibir_pessoas(possiveis_pais);
    int resposta = ler_int("Escolha uma dessas pessoas para ser o pai: ", possiveis_pais.size(), 1) - 1;
    pessoa->definir_pai(possiveis_pais[resposta]);

    limpar_tela();
    print("Definindo os pais de '" + pessoa->nome + "'");
    
    // Filtra apenas mulheres que nasceram antes da pessoa
    vector<Pessoa*> possiveis_maes = pesquisar_pessoas("", pessoa->nascimento.valor(), 'F');
    exibir_pessoas(possiveis_maes);
    resposta = ler_int("Escolha uma dessas pessoas para ser a mae: ", possiveis_maes.size(), 1) - 1;
    pessoa->definir_mae(possiveis_maes[resposta]);
}

void Arvore::ui_buscar_pessoa(){
    string nome = ler_string("Digite o nome da pessoa que deseja achar, deixe em branco para mostrar todas as pessoas: ");
    limpar_tela();
    print("Pesquisando por '" + nome + "'");
    print("________________________________________________");

    // Procura por pessoas com nomes parecidos e se achar, coloca elas em um vetor
    vector<Pessoa*> encontradas = pesquisar_pessoas(nome);

    // Se pessoas foram encontradas, mostrar elas
    if ( encontradas.empty() ) {
        print("Nenhuma pessoa encontrada", '\n', "vermelho");
        return;
    }
    
    exibir_pessoas(encontradas);
    int num = ler_int("Qual pessoa voce estava procurando? ", encontradas.size(), 1);
    
    Pessoa* p = encontradas[num-1];
    p->exibir_info();
    p->exibir_menu();
    p->menu.esperar_resposta();
}

void Arvore::ui_exibir_por_geracao() {
    int geracao = ler_int("Digite a geracao que está procurando: ");
    vector<Pessoa*> encontradas = pesquisar_pessoas("", INT_MAX, '\0', geracao);

    if (encontradas.empty()) {
        print("Nenhuma pessoa encontrada nessa geraçao.", '\n', "vermelho");
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

    pair<int, stack<Pessoa*>> dist = calcular_distancia(pessoaA, pessoaB);
    
    if (dist.first < 0) print("As duas pessoas nao tem nenhum grau de parentesco", '\n', "vermelho");
    else if (dist.first == 0) print("As duas pessoas sao as mesmas, parentesco: 0", '\n', "amarelo");
    else {
        while (!dist.second.empty()) {
            Pessoa* atual = dist.second.top();
            dist.second.pop();

            if (atual == pessoaA || atual == pessoaB) print(atual->nome, '\0', "amarelo");
            else print(atual->nome, '\0', "cinza");
            
            if (atual != pessoaB) print(" -> ", '\0', "verde");
            else print();
        }
        print("O grau de parentesco entre essas duas pessoas e: ", '\0');
        print(to_string(dist.first), '\n', "verde");
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
        { "Buscar pessoa",                        [this]() {ui_buscar_pessoa();} },
        { "Mostrar gerações",                     [this]() {ui_exibir_por_geracao();}},  
        { "Exibir parentesco entre 2 pessoas",    [this]() {ui_exibir_parentesco();}},
        { "Sair",                                 [this]() {exit(0);} },
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
        auto pessoa_tuple = Pessoa::deserializar(linha);
        Pessoa *p = get<0>(pessoa_tuple);
        if (p == nullptr) continue;
        familia.push_back(p);
        pessoas.insert({p->chave(), p});
        pessoas_pais.push_back(pessoa_tuple);
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
    // Explora nivel por nivel ate encontrar a pessoa destino

    queue<Pessoa*> fila;
    fila.push(a);
    unordered_set<Pessoa*> visitadas;
    unordered_map<Pessoa*, int> distancia_map = {{a, 0}};
    // Guarda de onde veio cada pessoa para reconstruir o caminho
    unordered_map<Pessoa*, Pessoa*> anterior;

    while(!fila.empty()) {
        Pessoa* atual = fila.front();
        fila.pop();
        
        if (atual == b) break;
        if (visitadas.count(atual) == 1) continue;
        visitadas.insert(atual);
        
        // Explora todas as "conexoes" (pais e filhos) da pessoa atual
        for (Pessoa *p : atual->conexoes()) {
            if (visitadas.count(p) == 1) continue;
            fila.push(p);
            distancia_map[p] = distancia_map[atual]+1;
            anterior[p] = atual;
        }
    }

    // Se b nao foi encontrado, nao tem parentesco
    if (anterior.count(b) == 0) return {-1, {}};

    // Reconstroi o caminho de b até a usando o map anterior
    stack<Pessoa*> caminho;
    Pessoa *atual = b;
    while (atual != a) {
        caminho.push(atual);
        atual = anterior[atual];
    }
    if (distancia_map[b] > 0) caminho.push(a);

    return {distancia_map[b], caminho};
}
