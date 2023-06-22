#include "img.h"
#ifndef LISTA_H
#define LISTA_H

typedef struct lista Lista;

// operacoes de lista com ListaNode
Lista *lista_create(void);
int lista_isEmpty(Lista *l);
void lista_append(Lista *l, IMG *img);
int lista_size(Lista *l);
void lista_histExtractor(Lista *l, char *salvarComo);

// operacoes de lista com HistNode
void lista_histAppend(Lista *l, unsigned int* hist, char* localidade);

#endif