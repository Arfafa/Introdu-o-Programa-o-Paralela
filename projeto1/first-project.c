#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int vertex;
  int total_neighbors;
  // int *neighbors;
  struct node *next;

} NODE;

typedef struct graph {
  NODE *inicio;
  NODE *fim;
  int tamanho;

} GRAPH;

void insert(GRAPH *network, int *dupla);
void write(GRAPH *network);
void liberar(GRAPH *network);

int main(int argc, char **argv) {
  GRAPH *network = (GRAPH *)malloc(sizeof(GRAPH));
  FILE *file;
  int n, count;
  int dupla[2];

  for (int i = 1; i < argc; i++) {

    file = fopen(argv[i], "r");

    if (file != NULL) {
      printf("%s\n", argv[i]);
      count = 0;

      network->tamanho = 0;
      network->inicio = NULL;
      network->fim = NULL;

      while (fscanf(file, "%d", &n) != EOF) {
        dupla[count % 2] = n;

        if (count % 2)
          insert(network, dupla);

        count++;
      }

      write(network);

      liberar(network);
      fclose(file);
    }
  }

  free(network);

  return 0;
}

void insert(GRAPH *network, int *dupla) {
  NODE *aux, *corr;

  for (int i = 0; i < 2; i++) {
    NODE *new = (NODE *)malloc(sizeof(NODE));

    new->vertex = dupla[i];
    new->total_neighbors = 1;
    new->next = NULL;

    aux = network->inicio;
    corr = network->inicio;

    if (network->inicio == NULL) {
      network->inicio = new;
      network->fim = new;
      network->tamanho = 1;
    }

    else {
      while (aux != NULL && aux->vertex <= new->vertex) {
        if (aux->vertex == new->vertex)
          aux->total_neighbors++;

        corr = aux;
        aux = aux->next;
      }

      if (aux == NULL && corr->vertex < new->vertex) {
        corr->next = new;
        network->fim = new;
        network->tamanho++;

      }

      else if (aux != NULL && aux->vertex > new->vertex &&
               corr->vertex < new->vertex) {
        new->next = aux;
        corr->next = new;
        network->tamanho++;
      }

      else if (aux != NULL && aux->vertex == network->inicio->vertex) {
        new->next = network->inicio;
        network->inicio = new;
        network->tamanho++;
      }
    }
  }
}

void write(GRAPH *network) {

  NODE *aux = network->inicio;

  while (aux != NULL) {
    printf("Node: %d\n", aux->vertex);
    printf("Total de Vizinhos: %d\n", aux->total_neighbors);

    aux = aux->next;
  }

  printf("Tamanho da rede: %d\n", network->tamanho);
}

void liberar(GRAPH *network) {
  NODE *aux, *corrente;

  corrente = network->inicio;

  while (corrente != NULL) {
    aux = corrente->next;

    free(corrente);

    corrente = aux;
  }
}
