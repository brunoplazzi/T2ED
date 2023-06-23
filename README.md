
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
- img <br />
Uma estrutura para armazenar a imagem PGM na memória, com a identificação da imagem, largura, altura, brilho máximo de cada pixel(Por se tratar de uma imagem preto e branco), a matriz dos pixels da imagem e o histograma da imagem. Contendo também a função para leitura do arquivo da imagem e salvamento em uma matriz na memória e outra para liberar a memória alocada.
- lista <br />
Nessa estrutura temos a implementação de duas listas, uma lista para armazenar as imagens com ponteiros para a primeira e a próxima imagem e outra lista para armazenar os histogramas, tendo a localidade do histograma salvo, o próprio histograma e um ponteiro para a próxima imagem. Com funções para criar as listas, verificar seus tamanhos, liberar a memória alocada, verificar se está vazia, adicionar elementos, nomear locais e geração dos histogramas a partir das imagens já na memória.


## Demonstração

Um gif ou um link de alguma demonstração

