#ifndef IMG_H
#define IMG_H

//definicao do tipo IMG
typedef struct {
  char tipo[5];
  int largura, altura;
  int brilhoMax;
  unsigned char **mat;
} IMG;

//operacoes

IMG lerArquivo(char *dict);

void liberaMemoria(IMG foto);

void histogramExtractor(IMG foto);

#endif