#include "img.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// le arquivo da imagem e retorna o tipo IMG
IMG *lerArquivo(char *dict) {
  IMG* foto = (IMG*)malloc(sizeof(IMG));
  int i, j;
  int pixel;

  // abrindo arquivo
  FILE *in;
  in = fopen(dict, "rt");
  if (in == NULL) {
    printf("ERRO NA LEITURA DO ARQUIVO!\n");
  }

  // lendo 3 primeiras linhas do arquivo
  fscanf(in, "%[^\n]\n", foto->tipo);
  fscanf(in, "%d %d\n", &foto->largura, &foto->altura);
  fscanf(in, "%d\n", &foto->brilhoMax);

  // gera matriz
  foto->mat = (unsigned char **)malloc(foto->altura * sizeof(unsigned char *));
  for (i = 0; i < foto->altura; i++) {
    foto->mat[i] = (unsigned char *)malloc(foto->largura * sizeof(unsigned char));
    for (j = 0; j < foto->largura; j++) {
      fscanf(in, "%d", &pixel);
      foto->mat[i][j] = pixel;
    }
  }

  fclose(in);

  unsigned char k;

  // valores do vetor igual a zero
  for (i = 0; i < foto->brilhoMax+1; i++) {
    foto->hist[i] = 0;
  }

  // quantidade de cada pixel vai para o vetor
  for (i = 0; i < foto->altura; i++) {
    for (j = 0; j < foto->largura; j++) {
      k = foto->mat[i][j];
      foto->hist[k] = foto->hist[k] + 1;
    }
  }

  return foto;
}

// libera a memória alocada para as matrizes
void liberaMemoria(IMG foto) {

  int i;
  for (i = 0; i < foto.altura; i++) {
    free(foto.mat[i]);
  }
  free(foto.mat);
}