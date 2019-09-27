# Projetos
Projetos desenvolvidos ao longo da disciplina Introdução à Programação Paralela 
oferecida pelo programa de Pós-Graduação do Instituto de Física de São Carlos.

## Como funciona?

As especificações de cada projeto se encontram nos arquivos .pdf presentes em cada um 
dos diretórios. Dentro deles existe também um arquivo em .c (ou .cpp) com o programa 
desenvolvido para o projeto. Para gerar um executável basta o comando:

```bash
gcc -Wall -Wextra -Wpedantic progama.c -o executavel
```

Caso o programa esteja com a extensão .cpp:
```bash
g++ -Wall -Wextra -Wpedantic progama.cpp -o executavel
```

As flags -Wall -Wextra e -Wpedantic podem ser adicionadas nos comandos citados anteriormente 
com o intuito de verificar a emissão de warnings no nível mais alto.

Para que a formatação dos arquivos fosse sempre consistente utilizei o programa 
clang-format-8 com o estilo llvm.

Até o presente momento, utilizo apenas C para fazer os programas. Os mesmos que estejam 
com extensão .cpp provavelmente não usam nada (ou quase nada) que seja específico do C++.

Os arquivos .tar.gz presentes em cada diretório são os arquivos de teste utilizados. Para 
descompactá-los:

```bash
tar -xzf arquivo.tar.gz
```

## Projeto 01

### Entrada

A entrada para o programa é um arquivo que descreve o grafo no formato conhecido como edgelist.
Neste formato, são dados dois a dois os índices de vértices conectados por arestas. Vale lembrar que 
devem ser consideradas ambas as direções das arestas, e que a separação de linhas não é relevante.

Para este projeto, pode-se assumir sobre o arquivo:
- Os vértices serão numerados de 0 a n-1 no arquivo.
- Cada vértice aparecerá pelo menos uma vez no arquivo. Isto é, o número de vértices 
do grafo é um a mais do que o maior valor presente no arquivo.
- Caso o par i,j apareça no arquivo, então o par j,i não aparecerá.

O nome do arquivo em questão deve ser lido pelo programa a partir da linha de comando. Esse, 
por sua vez, pode ou não possuir uma extensão .edgelist.

### Saída

A saída produzida deve ser um arquivo texto (ASCII) no seguinte formato:
- Cada linha corresponde às informações sobre um par distinto de vértices.
- A linha possui três valores inteiros, i, j e k e indica que entre os vértices
i e j existe k vizinhos em comum.
- Apenas i, j, k ou j, i, k devem aparecer no arquivo de saída, nunca os dois.
- Se o número de vizinhos em comum entre dois vértices é zero, o par correspondente
não deve aparecer no arquivo de saída.

O nome do arquivo de saída produzido deve ser o nome do arquivo de entrada, mas
com extensão .cng (a extensão anterior, se existente, deve ser removida). Por exemplo,
a saída produzida para o arquivo net102.edgelist deve car no arquivo net102.cng.

**OBS: As informações acima estão presentes no arquivo projeto1.pdf de forma muito 
mais detalhada. Neste arquivo optei por fazer apenas um resumo**

### Programa

Como já explicado, o programa deveria ler um arquivo que descreve um grafo. Uma maneira simples 
para retratar uma estrutura desse tipo são as [Matrizes de Adjancência](https://en.wikipedia.org/wiki/Adjacency_matrix), 
porém as redes com as quais estamos lidando aqui são [redes esparsas](https://en.wikipedia.org/wiki/Sparse_network) 
e sim esta informação foi omitida pelo pdf do projeto. O grande problema em representar redes esparsas com 
sua matriz de adjacência correspondente consistem no fato que acabamos em gastar muita memória alocando uma matriz 
composta, em sua maioria, por zeros.

Como resolver este problema então? Bem, existe uma outra forma de retrar redes conhecida como [Lista de Adjacência](https://en.wikipedia.org/wiki/Adjacency_list) 
e esta estrutura é mais apropriada para representar redes esparsas, contornando o problema apontado anteriormente.

Para tanto, foram criadas as structs:

```c
typedef struct node {
  int vertex;
  int total_neighbors;
  int *neighbors;
  struct node *next;

} NODE;

typedef struct adjacency_list {
  NODE *start;
  NODE *end;
  int size;

} ADJACENCY_LIST;
```

A Struct NODE possui o nó (vertex), o número total de vizinhos que este possui (total\_neighbors), seus vizinhos (neighbors) 
e aponta para o pŕoximo nó da lista.

Já a struct ADJACENCY\_LIST aponta para o começo (start) e fim (end) da lista e ainda guarda a informação sobre seu 
tamanho (size).

Por sua vez as funções:

```c
void insert(ADJACENCY_LIST *adlist, int *pair);
void add_neighbor(NODE *vx, int neigh);
void write(ADJACENCY_LIST *adlist, char *file_name);
void liberate(ADJACENCY_LIST *adlist);
```
- insert: insere um novo par de nós dentro da lista de adjacência.
- add\_neighbor: adiciona um novo vizinho para um nó já presente na lista.
- write: gera o arquivo de saída.
- liberate: desaloca o espaço ocupado pelas structs NODE e ADJACENCY\_LIST.

Não entrarei em detalhes sobre cada for, while ou if utilizado pois neste espaço quero apenas ressaltar algumas 
decisões de implementação utilizadas. Caso queira entender como foi implementada cada função, sugiro dar uma lida 
no programa first\_project.c.

Dentre as decisões tomadas, gostaria de falar sobre o uso do [insertion sort](https://en.wikipedia.org/wiki/Insertion_sort) 
no programa. Este algoritmo tem como o problema principal possuir uma [complexidade \(O(n^2)\)](https://en.wikipedia.org/wiki/Big_O_notation) 
no pior caso. Porém, o mesmo possui algumas vantagens que merecem ser destacadas:

- É o método a ser utilizado quando o arquivo está "quase" ordenado
- É um bom método quando se desejar adicionar poucos elementos em um arquivo já ordenado, pois seu custo é linear.
- O algoritmo de ordenação por inserção é estável.

Como o programa em questão lê um par de nós e já os adiciona em sua lista de adjacência, temos que a lista já 
está ordenada quando buscamos adicionar outro par. Ou seja, estamos trabalhando com insertion sort em seu melhor caso 
o qual, por sua vez, possui uma complexidade \(O(n)\) o que torna o algoritmo mais interessante em termos de 
otimização.
