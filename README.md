
# Trabalho 2 Estrutura de Dados

Uma busca de imagens baseada no seu conteúdo(CBIR), que utiliza os conceitos de TADs e listas encadeadas aprendidos em sala.


## Autores

- [@brunoplazzi](https://www.github.com/brunoplazzi)
- [@natanloc](https://www.github.com/natanloc)
- [@filipeabmoura](https://www.github.com/filipeabmoura)
- [@joaomrpimentel](https://www.github.com/joaomrpimentel)




## Instalação

Clone o repositório em seu Desktop:

```bash
  git clone https://github.com/brunoplazzi/T2ED.git
```
Após isso, compile o código e execute:
```bash
  gcc -o T2ED main.c img.c lista.c
  ./T2ED
```
    
## Estruturas de dados utilizadas
Descrições das principais estruturas de dados utilizadas no programa
- IMG
Uma estrutura para armazenar a imagem PGM P2 na memória, onde:
```c
  char tipo[5];
```
Armazena o tipo de imagem, como é uma imagem PGM P2, a primeira linha indica que ela é P2
```c
  int largura, altura;
```
Armazena a largura e a altura da imagem como dois inteiros
```c
  int brilhoMax;
```
Por ser uma imagem preto e branco, armazenamos o brilho máximo que cada pixel pode ter.
```c
  unsigned char **mat;
```
Utilizamos unsigned char para armazenar os pixels da imagem em uma matriz
```c
unsigned int hist[256];
```
Utilizamos unsigned int para armazenar o histograma da imagem
- lista
