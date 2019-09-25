# Projetos
Projetos desenvolvidos ao longo da disciplina Introdução à Programação Paralela 
oferecida pelo programa de Pós-Graduação do Instituto de Física de São Carlos.

## Como funciona?

As especificações de cada projeto se encontram nos arquivos .pdf presentes em cada um 
dos diretórios. Dentro deles existe também um arquivo em .c (ou .cpp) com o programa 
desenvolvido para o projeto. Para gerar um executável basta executar o comando:

```bash
gcc progama.c -o executavel
```

Caso o programa esteja com a extensão .cpp:
```bash
g++ progama.cpp -o executavel
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

Em breve...
