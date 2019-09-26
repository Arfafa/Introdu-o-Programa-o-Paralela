#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void insert(ADJACENCY_LIST *adlist, int *pair);
void add_neighbor(NODE *vx, int neigh);
void write(ADJACENCY_LIST *adlist, char *file_name);
void liberate(ADJACENCY_LIST *adlist);

int main(int argc, char **argv) {
  ADJACENCY_LIST *adlist = (ADJACENCY_LIST *)malloc(sizeof(ADJACENCY_LIST));
  FILE *file;
  int n, count;
  int pair[2];

  for (int i = 1; i < argc; i++) {

    file = fopen(argv[i], "r");

    if (file != NULL) {
      count = 0;

      adlist->size = 0;
      adlist->start = NULL;
      adlist->end = NULL;

      while (fscanf(file, "%d", &n) != EOF) {
        pair[count % 2] = n;

        if (count % 2)
          insert(adlist, pair);

        count++;
      }

      write(adlist, argv[i]);

      liberate(adlist);
      fclose(file);
    }
  }

  free(adlist);

  return 0;
}

void insert(ADJACENCY_LIST *adlist, int *pair) {
  NODE *aux, *chain;

  for (int i = 0; i < 2; i++) {
    NODE *new = (NODE *)malloc(sizeof(NODE));

    new->vertex = pair[i];
    new->total_neighbors = 1;
    new->next = NULL;

    new->neighbors = (int *)malloc(sizeof(int));

    new->neighbors[0] = pair[(i + 1) % 2];

    aux = adlist->start;
    chain = adlist->start;

    if (adlist->start == NULL) {
      adlist->start = new;
      adlist->end = new;
      adlist->size = 1;
    }

    else {
      while (aux != NULL && aux->vertex <= new->vertex) {
        if (aux->vertex == new->vertex) {
          aux->total_neighbors++;
          add_neighbor(aux, new->neighbors[0]);
        }

        chain = aux;
        aux = aux->next;
      }

      if (aux == NULL && chain->vertex < new->vertex) {
        chain->next = new;
        adlist->end = new;
        adlist->size++;

      }

      else if (aux != NULL && aux->vertex > new->vertex &&
               chain->vertex < new->vertex) {
        new->next = aux;
        chain->next = new;
        adlist->size++;
      }

      else if (aux != NULL && aux->vertex == adlist->start->vertex) {
        new->next = adlist->start;
        adlist->start = new;
        adlist->size++;
      }
    }
  }
}

void add_neighbor(NODE *vx, int neigh) {

  int i = 0, aux = neigh, chain;

  vx->neighbors =
      (int *)realloc(vx->neighbors, vx->total_neighbors * sizeof(int));

  while (i < vx->total_neighbors - 1 && vx->neighbors[i] < neigh)
    i++;

  for (int j = i; j < vx->total_neighbors; j++) {
    chain = vx->neighbors[j];
    vx->neighbors[j] = aux;
    aux = chain;
  }
}

void write(ADJACENCY_LIST *adlist, char *file_name) {

  NODE *aux = adlist->start, *chain;
  int j, count, l = strlen(file_name) - 1;
  FILE *file;

  while (l >= 0 && file_name[l] != '.')
    l--;

  if (l >= 0)
    file_name[l] = '\0';

  strcat(file_name, ".cng");

  file = fopen(file_name, "w");

  while (aux != NULL) {
    chain = aux->next;

    while (chain != NULL) {
      count = 0;

      for (int i = 0; i < aux->total_neighbors; i++) {
        j = 0;

        while (j < chain->total_neighbors &&
               chain->neighbors[j] <= aux->neighbors[i]) {
          if (chain->neighbors[j] == aux->neighbors[i])
            count++;

          j++;
        }
      }

      if (count)
        fprintf(file, "%d %d %d\n", aux->vertex, chain->vertex, count);

      chain = chain->next;
    }

    aux = aux->next;
  }

  fclose(file);
}

void liberate(ADJACENCY_LIST *adlist) {
  NODE *aux, *chain;

  aux = adlist->start;

  while (aux != NULL) {
    chain = aux->next;

    free(aux);

    aux = chain;
  }
}
