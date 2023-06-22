#include "lista.h"
#include "img.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct listaNode ListaNode;
typedef struct histNode HistNode;


//structs
struct lista {
  ListaNode *first;
};

struct listaH{
  HistNode* first;
};

//struct de ponteiros de imagens
struct listaNode {
  IMG *img;
  ListaNode *next;
};

//struct de histogramas, com diretorio e histograma
struct histNode{
  char * local;
  unsigned int hist[256];
  HistNode *next;
};


// operacoes referentes a lista com ListaNode

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

void liberarMemoria(Lista *l){

  ListaNode *p = l->first;

  while(p != NULL){
    ListaNode *t = p->next;
    liberaMemoria(p->img); //liberar a memoria da mat dentro do IMG
    free(p->img);          //libera a propria img
    free(p);               //libera o node
    p = t;
  }
  free(l);                 //libera a lista

}


void lista_histExtractor(Lista *l, char *salvarComo) {

  int i;
  int divisor = lista_size(l);

  // histograma medio zerado
  unsigned int histMedio[256];
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

  //liberar a memoria utilizada na geracao do histograma medio
  liberarMemoria(l);

}

//operacoes referentes a lista de histogramas medios
ListaH* listaH_create(){
  ListaH *p = (ListaH *)malloc(sizeof(ListaH));
  p->first = NULL;

  return p;
}


void lista_histAppend(ListaH *l, unsigned int* hist, char* localidade){

  //alocacao do HistNode apontado inicialmente para NULL
  HistNode *node = (HistNode*) malloc(sizeof(HistNode));
  node->next = NULL;
  
  //preencher hist do histNode
  for (int i = 0; i< 256; i++){
    node->hist[i] = hist[i];
  }

  //preencher o nome
  char local[81];
  strcpy(local, localidade);
  node->local = local;


  if(l->first == NULL){
    l->first = node;
  }
  else{
    node->next = l->first;
    l->first = node;
  }

}