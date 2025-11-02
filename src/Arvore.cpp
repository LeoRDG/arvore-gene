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
    string nome = ler_string("Digite o nome da pessoa que voce quer adicionar:\n");
    char genero =  pedir_genero();
    Data nascimento = pedir_data();

    Pessoa*pessoa = criar_pessoa(nome, genero, nascimento);

    if (!confirmar("Gostaria de definir os pais dessa pessoa?")) return;
    ui_definir_pais(pessoa);
}

void Arvore::ui_definir_pais(Pessoa*pessoa){
    //clear();
    print("Definindo os pais de '" + pessoa->nome + "'");
    vector<Pessoa*> possiveis_pais = pesquisar_pessoas("", pessoa->nascimento.valor(), 'M');
    exibir_pessoas(possiveis_pais);
    int resposta = ler_int("Escolha uma dessas pessoas para ser o pai: ", possiveis_pais.size(), 1) -1;
    pessoa->definir_pai(possiveis_pais[resposta]);

    limpar_tela();
    print("Definindo os pais de '" + pessoa->nome + "'");
    vector<Pessoa*> possiveis_maes = pesquisar_pessoas("", pessoa->nascimento.valor(), 'F');
    exibir_pessoas(possiveis_maes);
    resposta = ler_int("Escolha uma dessas pessoas para ser a mae: ", possiveis_maes.size(), 1) -1;
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
        print_com_cor("Nenhuma pessoa encontrada", "vermelho");
        return;
    }
    
    exibir_pessoas(encontradas);
    int num = ler_int("Qual pessoa voce estava procurando? ", encontradas.size(), 1);
    
    Pessoa*p = encontradas[num-1];
    p->exibir_info();
    p->exibir_menu();
    p->menu.esperar_resposta();
}

void Arvore::ui_exibir_por_geracao() {
    int geracao = ler_int("Digite a geracao que está procurando: ");
    vector<Pessoa*> encontradas = pesquisar_pessoas("", INT_MAX, '\0', geracao);

    if (encontradas.empty()) {
        print_com_cor("Nenhuma pessoa encontrada nessa geraçao.\n", "vermelho");
        return;
    }

    exibir_pessoas(encontradas);
}

void Arvore::ui_exibir_parentesco() {
    exibir_pessoas(familia);
    Pessoa*pessoaA = familia[ler_int("Qual a primeira pessoa? ")-1];
    Pessoa*pessoaB = familia[ler_int("Qual a segunda pessoa? ")-1];

    pair<int, stack<Pessoa*>> dist = calcular_distancia(pessoaA, pessoaB);
    
    if (dist.first < 0) print_com_cor("As duas pessoas nao tem nenhum grau de parentesco\n", "vermelho");
    else if (dist.first == 0) print_com_cor("As duas pessoas sao as mesmas, parentesco: 0\n", "amarelo");
    else {
        while (!dist.second.empty()) {
            Pessoa* atual = dist.second.top();
            dist.second.pop();

            if (atual == pessoaA || atual == pessoaB) print_com_cor(atual->nome, "amarelo");
            else print_com_cor(atual->nome, "cinza");
            
            if (atual != pessoaB) print_com_cor(" -> ", "verde");
            else print();
        }
        print("O grau de parentesco entre essas duas pessoas e: ", '\0');
        print_com_cor(to_string(dist.first)+"\n", "verde");
    }
}

void Arvore::exibir_info(){
    print("Data: " + Data::hoje().str());
    print("Nome da Arvore: " + nome);
    print("Quantidade de pessoas:", ' ');
    print_com_cor(to_string(familia.size()), "verde");
    print();
}

void Arvore::exibir_pessoas(vector<Pessoa*> pessoas){
    printf("%zu/%zu Pessoas encontradas\n", pessoas.size(), familia.size());
    print("________________________________________________");
    cout << "ID. ";
    Pessoa::exibir_cabecario();

    for (int i=0; i<pessoas.size(); i++) {
        //printf("% 3d ", i+1);
        cout << cores.at("verde") << setw(4) << i+1 << cores.at("padrao"); 
        pessoas[i]->exibir();
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
    ofstream arquivo(nome + ".csv");

    for (auto pessoa : familia) {
        arquivo << pessoa->serializar() << "\n";
    }

    arquivo.close();
}

void Arvore::carregar(){
    ifstream arquivo(nome + ".csv");
    string linha;
    unordered_map<string, Pessoa*> pessoas;              // map para guardar a pessoa usando sua chave
    vector<tuple<Pessoa*, string, string>> pessoas_pais; // vetor de tuplas para guardar a pessoa e as chaves dos pais

    // Primeiro loop para criar todas as pessoas a partir do csv
    while ( getline(arquivo, linha) ) {
        auto pessoa_tuple = Pessoa::deserializar(linha);
        Pessoa *p = get<0>(pessoa_tuple);
        familia.push_back(p);
        pessoas.insert({p->chave(), p});
        pessoas_pais.push_back(pessoa_tuple);
    }

    // Segundo loop para definir os pais das pessoas 
    for (auto pessoa : pessoas_pais){
        auto [p, pai, mae] = pessoa;
        if (pai.size() >= 1) p->definir_pai(pessoas[pai]);
        if (mae.size() >= 1) p->definir_mae(pessoas[mae]);
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
        // Se qualquer um desses testes for true, nao adicionar a pessoa ao vetor
        if ( !contem(pessoa->nome, nome) ) continue;
        if ( pessoa->nascimento.valor() >= valor_data ) continue;
        if ( genero != '\0' && pessoa->genero != genero ) continue;
        if ( geracao != -1 && pessoa->geracao != geracao ) continue;
        encontradas.push_back(pessoa);
    }
    return encontradas;
}

pair<int, stack<Pessoa*>> Arvore::calcular_distancia(Pessoa*a, Pessoa*b) {
    /*
        Algoritmo BFS
        https://www.youtube.com/watch?v=xlVX7dXLS64

        Cria uma fila com a pessoaA dentro
        Enquanto a fila nao estiver vazia

        Verifica se a primeira pessoa da fila é a pessoaB
        Se for, sai do loop pois o parentesco foi encontrado

        Se nao for..
        Repete o processo para cada Pessoa diretamente ligada à que saiu da fila

        Se o loop encerrar porque a fila esvaziou as duas pessoas não tem parentesco definido

    */

    queue<Pessoa*> fila;
    fila.push(a);
    unordered_set<Pessoa*> visitadas;
    unordered_map<Pessoa*, int> distancia_map = {{a, 0}};
    unordered_map<Pessoa*, Pessoa*> anterior;

    while(!fila.empty()) {
        Pessoa*atual = fila.front();
        fila.pop();
        
        if (atual == b) break;
        if (visitadas.count(atual) == 1) continue;
        
        for (Pessoa *p : atual->conexoes()) {
            if (visitadas.count(p) == 1) continue;
            visitadas.insert(atual);
            fila.push(p);
            distancia_map[p] = distancia_map[atual]+1;
            anterior[p] = atual;
        }
    }

    if (anterior.count(b) == 0) return {-1, {}};    // Se a pessoa b nao estiver no map, ela nao foi encontrada (nao tem relacao com a)
    //if (distancia_map[b] == 0) return {0, {b}};       // Se a distancia entre a e b for 0, sao a mesma pessoa

    stack<Pessoa*> caminho;
    Pessoa *atual = b;
    while (atual != a) {
        caminho.push(atual);
        atual = anterior[atual];
    }
    if (distancia_map[b] > 0) caminho.push(a);

    return {distancia_map[b], caminho};
}
