#!/bin/bash

arquivo='output.out'

echo 'Removendo arquivo antigo..'
rm -f ./$arquivo

echo 'Compilando código..'
g++ ./src/*.cpp \
-I ./include \
-o ./$arquivo

echo "Pronto"
./$arquivo