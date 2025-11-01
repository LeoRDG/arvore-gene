#!/bin/bash

# Name of the test to run (without path or .cpp)
# Example: pass 'tests1' to compile tests/tests1.cpp
nome=$1
if [ -z "$nome" ]; then
    echo "Usage: $0 <nome_doarquivo>"
    exit 1
fi

output="./$nome.out"
arquivo="./tests/$nome.cpp"

if [ ! -f "$arquivo" ]; then
    echo "$arquivo nao existe"
    exit 1
fi

echo "Removendo antigo"
rm -f "$output"

# Compile all src files except main.cpp
src=(./src/*.cpp)
for f in "${src[@]}"; do
    if [[ "$f" == *"main.cpp" ]]; then
        continue
    fi
    echo "Compilando $f ..."
    g++ -c "$f" -I ./include -o "${f%.cpp}.o"
done

# Compile the test file
echo "Compilando teste $arquivo ..."
g++ -c "$arquivo" -I ./include -o "./tests/${nome}.o"

g++ ./src/*.o ./tests/${nome}.o -o "$output"

rm -f ./src/*.o ./tests/*.o

"$output"
