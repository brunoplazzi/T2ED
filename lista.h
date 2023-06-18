#include "img.h"
#ifndef LISTA_H
#define LISTA_H

typedef struct lista Lista;

// operacoes
Lista *lista_create(void);
int lista_isEmpty(Lista *l);
void lista_append(Lista *l, IMG *img);
int lista_size(Lista *l);
void lista_histExtractor(Lista *l, char *salvarComo);

#endif