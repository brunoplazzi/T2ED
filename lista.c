#include "lista.h"
#include "img.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct listaNode ListaNode;

// estruturas
struct lista {
  ListaNode *first;
};

struct listaNode {
  IMG *img;
  ListaNode *next;
};

// operacoes

// criar uma lista vazia
Lista *lista_create(void) {

  Lista *p = (Lista *)malloc(sizeof(Lista));
  p->first = NULL;

  return p;
}

// verifica se lista esta vazia
int lista_isEmpty(Lista *l) { return l->first == NULL; }

// adicionar elemento na lista
void lista_append(Lista *l, IMG *img) {

  // cria o node vazio
  ListaNode *node = (ListaNode *)malloc(sizeof(ListaNode));
  node->next = NULL;

  // coloca o node no inicio da lista
  if (lista_isEmpty(l)) {
    l->first = node;
  } else {
    node->next = l->first;
    l->first = node;
  }

  // inserir conteudo no node
  node->img = img;
}

int lista_size(Lista *l) {

  int cont = 0;

  ListaNode *p = l->first;

  while (p != NULL) {
    cont++;
    p = p->next;
  }
  return cont;
}

void lista_histExtractor(Lista *l, char *salvarComo) {

  int i;
  int divisor = lista_size(l); // 5

  // histograma medio zerado
  unsigned char histMedio[256];
  for (i = 0; i < 256; i++) {
    histMedio[i] = 0;
  }

  // ponteiro parar percorrer a lista
  ListaNode *p = l->first;

  while (p != NULL) {
    for (i = 0; i < 256; i++) {
      histMedio[i] += p->img->hist[i];
    }
    p = p->next;
  }

  for (i = 0; i < 256; i++) {
    histMedio[i] = histMedio[i] / divisor;
  }

  // escrever no arquivo o histograma
  FILE *histogram;

  char saveAs[81];
  strcpy(saveAs, salvarComo);

  strcat(saveAs, "histogram.txt");

  histogram = fopen(saveAs, "wt");

  for (i = 0; i < 256; i++) {
    fprintf(histogram, "%d\n", histMedio[i]);
  }

  fclose(histogram);
}

//"./base/img/cantina/"