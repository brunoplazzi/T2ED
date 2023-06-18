#include "img.h"
#include "lista.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef void (*FileCallback)(const char *, Lista *, char *);

void leitorPastas(char *pasta, FileCallback callback, Lista *l, char *localidade) {
  DIR *dp;
  struct dirent *ep;

  dp = opendir(pasta);
  int cont = 0;

  if (dp != NULL) {
    while ((ep = readdir(dp))) {
      callback(ep->d_name, l, localidade);
    }
    (void)closedir(dp);
  } else {
    perror("Não foi possível abrir o diretório");
  }
}

void printFileName(const char *name) {

  if (*name != '.') {
    printf("%s\n", name);
  }
}

void preencheLista(const char *name, Lista *l, char *local) {
  if (*name != '.') {
    char dict[81];
    dict[0] = '\0';

    strcat(dict, local);
    strcat(dict, name);

    IMG *img = lerArquivo(dict);
    lista_append(l, img);
  }
}

void extratorLocalidade(char *localidade) {

  // lista vazia criada
  Lista *lista = lista_create();

  leitorPastas(localidade, preencheLista, lista, localidade);

  // extrair histograma medio para o txt

  lista_histExtractor(lista, localidade);
}

int main(void) {

  // vetor com as localidades do ifes
  char *localidade[20] = {
    "./base/img/bibliotecaEntrada/",
    "./base/img/bloco5/",
    "./base/img/bloco8Interno/",
    "./base/img/blocoInexistente/",
    "./base/img/caminhoLateral/",
    "./base/img/cantina/",
    "./base/img/corredorHallCantina/",
    "./base/img/escada/",
    "./base/img/estacionamento/",
    "./base/img/hall/",
    "./base/img/ifesEntrada/",
    "./base/img/laboratorioPaixao/",
    "./base/img/laboratorios700/",
    "./base/img/laboratorios900/",
    "./base/img/patioArvore/",
    "./base/img/patioEnsinoMedio/",
    "./base/img/patioProfessores/",
    "./base/img/patioXadrez/",
    "./base/img/quadra/",
    "./base/img/salaDeAulaSuperior/",
  };

  extratorLocalidade(localidade[5]);

  // for (int i = 0; i < 20; i++) {
  //   extratorLocalidade(localidade[i]);
  // }

  // lista de histogramas medios

  // compara query com cada no da lista

  // retorna as cinco localidades mais provaveis

  printf("fim do processo\n");

  return 0;
}

