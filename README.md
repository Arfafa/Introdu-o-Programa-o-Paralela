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
