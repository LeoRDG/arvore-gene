#pragma once // Garante que esse header seja incluso uma só vez
#include <functional>

using namespace std;

struct Opcao{
    string descricao;
    //void(*func)();
    function <void()> func = nullptr;
};

struct Menu{
    vector<Opcao> opcoes;

    void imprimir();


    bool processar_resposta(int);
};