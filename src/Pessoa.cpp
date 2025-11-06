/**
 * Aqui serão implementadas as funcionalidades da Pessoa
 */

#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include <tuple>
#include <map>
#include <utility>
#include <vector>
#include <unordered_set>
#include "../include/Pessoa.h"
#include "../include/util.h"

using namespace std;

void Pessoa::exibir_cabecario(){
    cout << left << setw(L_NOME) << "Nome";
    cout << setw(L_NASC) << "Nascimento";
    cout << setw(L_GEN) << "Genero";
    cout << setw(L_PAIS) << "Pai";
    cout << setw(L_PAIS) << "Mae";
    cout << setw(L_GEN) << "Geracao";
    cout << "\n";
}


void Pessoa::exibir_linha(string cor){
    cout << cores.at(cor);
    cout << left << setw(L_NOME) << limite_str(nome, L_NOME-1);
    cout << setw(L_NASC) << nascimento.str();
    cout << setw(L_GEN) << genero;

    for (auto p : {pai, mae}) {
        cout << setw(L_PAIS);
        (p == nullptr) ? cout << "" : cout << limite_str(p->primeiro_nome(), L_PAIS-1);
    }

    cout << setw(L_GER);
    (geracao == GERACAO_INICIAL) ? cout << "???" : cout << geracao;
    
    cout << cores.at("padrao");
    cout << "\n";
}


void Pessoa::exibir_ascendentes(int nivel) {

    if (pai == nullptr && mae == nullptr) {
        for (int i=0; i <nivel; i++) cout << "  ";
        print("Nao ha ascendentes cadastrados para: " + this->nome, '\n', "vermelho");
        return;
    }
    else{
        if (pai != nullptr) {
            pai->exibir_ascendentes(nivel+1);
            for (int i=0; i <nivel; i++) cout << "  ";
            print("Pai de " + this->nome + ": ", '\0', "cinza");
            print(pai->nome);
            // cout << "Pai de "<< this->nome << ": " << pai->nome << "\n";
        }
        
        if (mae != nullptr) {
            mae->exibir_ascendentes(nivel+1);
            for (int i=0; i <nivel; i++) cout << "  ";
            print("Mae de " + this->nome + ": ", '\0', "cinza");
            print(mae->nome);
            // cout << "Mae de " <<this->nome << ": " << mae->nome << "\n";
        }
    }
}


void Pessoa::exibir_descendentes(int nivel) {
    if (filhos.empty()) {
        for (int i=0; i <nivel; i++) cout << "  ";
        print("Nao ha descendentes cadastrados para: " + this->nome, '\n', "vermelho");
        return;
    }

    for (Pessoa* filho : filhos) {
        for (int i=0; i <nivel; i++) cout << "  ";
        print("Filho de " + nome + ": ", '\0', "cinza");
        print(filho->nome);
        // cout << "Filho de " << this->nome<< " :" << " "<< filho->nome << "\n";
        filho->exibir_descendentes(nivel + 1);
    }
}


void Pessoa::exibir_asc_desc(){
    exibir_ascendentes(1);
    print(nome, '\n', "amarelo");
    exibir_descendentes(1);
}


void Pessoa::exibir_info(){
    limpar_tela();
    auto asc_set = new unordered_set<Pessoa*>;
    auto desc_set = new unordered_set<Pessoa*>;

    cout << "Nome: " << nome << "\n"
         << "Nascimento: " << nascimento.str() << "\n"
         << "Genero: " << genero << "\n"
         << "Descendentes: " << contar_descendentes(asc_set) << "\n"
         << "Ascendentes: " << contar_ascendentes(desc_set) << "\n"
    ; 

    delete asc_set;
    delete desc_set;
}


void Pessoa::exibir_menu(){
    if (menu.opcoes.empty()) criar_menu();
    menu.imprimir();
}


void Pessoa::exibir_arvore(int nivel){
    // Se essa pessoa nao tem filhos, exibir somente o nome e retorna
    if (filhos.empty()) {
        print(to_string(nivel), ' ', "cinza");
        for (int i = 0; i < nivel; i++) print("--", '\0', "cinza");
        print(nome, '\n', "vermelho");
        return;
    }

    // Agrupa filhos por casal
    map<pair<Pessoa*, Pessoa*>, vector<Pessoa*>> casais;
    for (Pessoa* filho : filhos) {
        casais[{filho->pai, filho->mae}].push_back(filho); 
    }

    // Exibe cada casal e seus filhos
    for (auto par : casais){
        auto casal_pai = par.first.first;
        auto casal_mae = par.first.second;
        auto filhos_casal = par.second;

        print(to_string(nivel), ' ', "cinza");
        for (int i = 0; i < nivel; i++) print("--", '\0', "cinza");

        // Formata casal (pai + mae ou ??? se nao existir)
        if (casal_pai && casal_mae) {
            print(casal_pai->nome, ' ');
            print("+", ' ', "amarelo");
            print(casal_mae->nome);
        }
        else if (casal_pai) {
            print(casal_pai->nome, ' ');
            print("+", ' ', "amarelo");
            print("???", '\n', "cinza");
        }
        else if (casal_mae){
            print("???", ' ', "cinza");
            print("+", ' ', "amarelo");
            print(casal_mae->nome);
        } 
        else {
            print("??? + ???", '\n', "cinza");
        }

        // Exibe os filhos desse casal (recursivamente)
        for (auto f: filhos_casal) {
            f->exibir_arvore(nivel + 1);
        }
    }
}


int Pessoa::contar_ascendentes(unordered_set<Pessoa*>* visitadas){  
    int contagem = 0;
    
    // Conta o pai e seus pais, se ja nao foi contado
    if (pai != nullptr && !visitadas->count(pai)) {
        contagem++;
        visitadas->insert(pai);
        contagem += pai->contar_ascendentes(visitadas);
    }
    
    // Conta a mae e seus pais, se ja nao foi contado
    if (mae != nullptr && !visitadas->count(mae)) {
        contagem++;
        visitadas->insert(mae);
        contagem += mae->contar_ascendentes(visitadas);
    }
    
    return contagem;
}


int Pessoa::contar_descendentes(unordered_set<Pessoa*>* visitadas){  
    int contagem = 0;
    
    for (Pessoa* f : filhos) {
        // Se o filho ja esta no set, conta ele e seus filhos
        if (!visitadas->count(f)) {
            contagem++;
            visitadas->insert(f);
            contagem += f->contar_descendentes(visitadas);
        }
    }
        
    return contagem;
}


void Pessoa::definir_pai(Pessoa* pai){
    this->pai = pai;
    pai->filhos.push_back(this);
    definir_geracao();
}


void Pessoa::definir_mae(Pessoa* mae){
    this->mae = mae;
    mae->filhos.push_back(this);
    definir_geracao();
}


void Pessoa::definir_geracao() {
    // Geraçao eh o maximo entre pai e mae + 1
    int g_pai = (pai == nullptr) ? GERACAO_INICIAL : pai->geracao;
    int g_mae = (mae == nullptr) ? GERACAO_INICIAL : mae->geracao;
    int nivel = max(g_pai, g_mae);

    // Evita recalcular se ja esta correto
    if (geracao >= nivel+1) return;

    geracao = nivel+1;

    // Define a geracao dos os descendentes
    for (auto* f : filhos) {
        f->definir_geracao();
    }
}


void Pessoa::criar_menu(){
    menu = {{
        {"Exibir Ascendentes",                [this]() {
            exibir_ascendentes(1);
            print(nome, '\n', "amarelo");
        }},
        {"Exibir Descendentes",               [this]() {
            print(nome, '\n', "amarelo");
            exibir_descendentes(1);
        }},
        {"Exibir Ascendentes e descendentes", [this]() {exibir_asc_desc();}},
        {"Remover da Arvore",                 [this]() {print("Funcionalidade nao implementada", '\n', "vermelho");}},
        {"Exibir Arvore",                     [this]() {exibir_arvore(0);}},
        {"Voltar",                            [this]() {menu.continua=false;}},
    }};
}


string Pessoa::primeiro_nome(){
    int espaco = nome.find(' ');
    // find() retorna string::npos se nao encontrar, se acontecer, retornar nome completo
    if (espaco == string::npos) return nome;
    return nome.substr(0, espaco);
}


string Pessoa::chave(){
    // Junta o nome e o valor do nascimento e deixando tudo minusculo
    return to_string(nascimento.valor()) + minusculas(nome);
}


vector<Pessoa*> Pessoa::conexoes(){
    vector<Pessoa*> resultado = filhos;
    if (pai != nullptr) resultado.push_back(pai);
    if (mae != nullptr) resultado.push_back(mae);
    return resultado;
}


string Pessoa::serializar(){
    stringstream stream;
    string resultado;

    // Formato: ano,mes,dia,nome,genero,chave_pai,chave_mae
    stream << setfill('0') << setw(4) << nascimento.ano << ","
    << setw(2) << nascimento.mes << ","
    << setw(2) << nascimento.dia << ","
    << nome << ","
    << genero << ',';

    // Se nao tiver pai/mae, deixa vazio (espaco em branco)
    (pai == nullptr) ? stream << " ," : stream << pai->chave() << ",";
    (mae == nullptr) ? stream << " "  : stream << mae->chave();

    getline(stream, resultado);

    return resultado;
}


tuple<Pessoa*, string, string> Pessoa::deserializar(string dados){
    // Formato: ano,mes,dia,nome,genero,chave_pai,chave_mae
    vector<string> vetor_dados;
    istringstream str(dados);
    string dado;

    // Separa os dados por virgula
    while ( getline(str, dado, ',') ){
        vetor_dados.push_back(dado);
    }

    // Valida formato a quantidade de dados
    if (vetor_dados.size() != 7) return {nullptr, "", ""};

    // Se ocorrer um erro ao converter a string para int, retornar nullptr
    int dia, mes, ano;
    try {
        dia = stoi(vetor_dados[2]);
        mes = stoi(vetor_dados[1]);
        ano = stoi(vetor_dados[0]);
    } catch (invalid_argument) {
         return {nullptr, "", ""};
    }

    string nome = vetor_dados[3];
    char genero = vetor_dados[4][0];

    Data nascimento = Data(dia, mes, ano);

    Pessoa* pessoa = new Pessoa{nome, nascimento, genero};

    // Retorna pessoa criada e chaves dos pais (para definir depois)
    return {pessoa, vetor_dados[5], vetor_dados[6]};
}
