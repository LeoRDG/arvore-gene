# Árvore Genealógica
Arvore Genealógica para trabalho de Linguagens de Programação.


## Objetivo Geral
Implementar um sistema/software em C++para representar e manipular uma árvore genealógica, aplicando estruturas de dados hierárquicas, como árvores, ou filas e listas. 

### FUNCIONALIDADE OBRIGATÓRIAS 
- [x] Adicionar pessoa 
- [x] Definir relação (Pai, mae, filho)
- [ ] Exibir ascendentes e descendentes de uma pessoa -- DEIXA CO PAI(JÃO)
- [ ] Listar toda a arvore a partir de um ancestral 
- [x] Buscar pessoa por nome 


### FUNCIONALIDADES OPCIONAIS 
- [ ] Exibir nivel de parentesco entre 2 pessoas
- [ ] Contagem de descendentes diretos e indiretos 
- [x] Mostrar gerações por nivel 
- [x] Gravar e carregar de um arquivo de texto

Para compilar corretamente, todos os arquivos cpp devem ser incluidos

##### Linux/Macos
~~g++ *.cpp -o output.out && ./output.out~~

~~clang++ *.cpp -o output.out && ./output.out~~

###### Usa o alias abaixo, só muda o caminho
```
alias arv='rm -f ~/Desktop/ADS/arvore-gene/out.out && \
clang++ ~/Desktop/ADS/arvore-gene/src/*.cpp \
-I ~/Desktop/ADS/arvore-gene/include \
-o ~/Desktop/ADS/arvore-gene/out.out && \
~/Desktop/ADS/arvore-gene/out.out'
```

##### Windows
Quem usa windows??
