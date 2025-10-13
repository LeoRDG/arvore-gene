#include <string>
#include <functional>

#pragma once

using namespace std;

struct Opcao{
    string descricao;
    //void(*func)();
    function <void()> func = nullptr;
};