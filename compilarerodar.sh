#!/bin/bash

arquivo='output.out'

echo 'Removendo arquivo antigo..'
rm -f ./$arquivo

arquivos=(./src/*.cpp)

# Compila 1 por 1
for f in "${arquivos[@]}"; do
    echo "Compilando $f ..."
    g++ -c "$f" -I ./include -o "${f%.cpp}.o"
done

# Linka todos os objetos em um único executável
echo 'Gerando executável...'
g++ ./src/*.o -I ./include -o ./$arquivo
rm -f ./src/*.o

echo "Pronto"
./$arquivo