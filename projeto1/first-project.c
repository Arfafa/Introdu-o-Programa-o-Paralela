#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  int vertex;
  int total_neighbors;
  int *neighbors;
  struct node *next;

} NODE;

typedef struct graph {
  NODE *inicio;
  NODE *fim;
  int tamanho;

} GRAPH;

void insert(GRAPH *network, int *dupla);
void add_neighbor(NODE *elem, int viz);
void write(GRAPH *network, char *file_name);
void liberar(GRAPH *network);

int main(int argc, char **argv) {
  GRAPH *network = (GRAPH *)malloc(sizeof(GRAPH));
  FILE *file;
  int n, count;
  int dupla[2];

  for (int i = 1; i < argc; i++) {

    file = fopen(argv[i], "r");

    if (file != NULL) {
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

      write(network, argv[i]);

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

    new->neighbors = (int *)malloc(sizeof(int));

    new->neighbors[0] = dupla[(i + 1) % 2];

    aux = network->inicio;
    corr = network->inicio;

    if (network->inicio == NULL) {
      network->inicio = new;
      network->fim = new;
      network->tamanho = 1;
    }

    else {
      while (aux != NULL && aux->vertex <= new->vertex) {
        if (aux->vertex == new->vertex) {
          aux->total_neighbors++;
          add_neighbor(aux, new->neighbors[0]);
        }

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

void add_neighbor(NODE *elem, int viz) {

  int i = 0, aux = viz, corr;

  elem->neighbors =
      (int *)realloc(elem->neighbors, elem->total_neighbors * sizeof(int));

  while (i < elem->total_neighbors - 1 && elem->neighbors[i] < viz)
    i++;

  for (int j = i; j < elem->total_neighbors; j++) {
    corr = elem->neighbors[j];
    elem->neighbors[j] = aux;
    aux = corr;
  }
}

void write(GRAPH *network, char *file_name) {

  NODE *aux = network->inicio, *corr;
  int j, count, l = strlen(file_name) - 1;
  FILE *file;

  while (l >= 0 && file_name[l] != '.')
    l--;

  if (l >= 0)
    file_name[l] = '\0';

  strcat(file_name, ".cng");

  file = fopen(file_name, "w");

  while (aux != NULL) {
    corr = aux->next;

    while (corr != NULL) {
      count = 0;

      for (int i = 0; i < aux->total_neighbors; i++) {
        j = 0;

        while (j < corr->total_neighbors &&
               corr->neighbors[j] <= aux->neighbors[i]) {
          if (corr->neighbors[j] == aux->neighbors[i])
            count++;

          j++;
        }
      }

      if (count)
        fprintf(file, "%d %d %d\n", aux->vertex, corr->vertex, count);

      corr = corr->next;
    }

    aux = aux->next;
  }

  fclose(file);
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
