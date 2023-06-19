#ifndef IMG_H
#define IMG_H

// definicao do tipo IMG
typedef struct {
  char tipo[5];
  int largura, altura;
  int brilhoMax;
  unsigned char **mat;
  unsigned int hist[256];
} IMG;

// operacoes

IMG *lerArquivo(char *dict);

void liberaMemoria(IMG *foto);

#endif