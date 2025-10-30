#!/bin/bash

arquivo='output.out'

echo 'Removendo arquivo antigo..'
rm -f ./$arquivo

echo 'Compilando código..'

# Cria uma lista de arquivos .cpp
arquivos=(./src/*.cpp)

# Compila um por um, mostrando o nome do arquivo
for f in "${arquivos[@]}"; do
    echo "Compilando $f ..."
    g++ -c "$f" -I ./include -o "${f%.cpp}.o"
done

# Linka todos os objetos em um único executável
echo 'Gerando executável...'
g++ ./src/*.o -I ./include -o ./$arquivo

echo "Pronto"
./$arquivo