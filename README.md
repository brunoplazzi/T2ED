
# Trabalho 2 -  Estrutura de Dados

Este projeto consiste em um sistema de processamento de imagens desenvolvido como um trabalho acadêmico, da disciplina de estrutura de dados do IFES-Serra. O objetivo do projeto é aplicar os conhecimentos adquiridos em sala de aula, realizando processamento de imagens, busca de imagens baseada no seu conteúdo(CBIR), leitura de arquivos, cálculo de histogramas, geração de histograma médio e comparação de histogramas, para o reconhecimento de imagens e identificação de localidades dentro do campus do IFES-Serra. O trabalho consiste em criar um programa que, através de uma imagem fornecida pelo usuário, consiga reconhecer e dizer para o usuário que localidade é aquela.

### Autores

- Bruno Schneider Plazzi: [@brunoplazzi](https://www.github.com/brunoplazzi)
- Natan Lagassa [@natanloc](https://www.github.com/natanloc)
- Filipe Moura Anunciação: [@filipeabmoura](https://www.github.com/filipeabmoura)
- João Marcos Pimentel: [@joaomrpimentel](https://www.github.com/joaomrpimentel)

<hr >

## Informações Importantes

- Para o funcionamento correto do programa é necessário baixar a base de dados com as imagens utilizadas pelo programa. O arquivo pode ser baixado no link do google drive abaixo. Substitua a pasta 'base' (que esta vazia neste repositório) pela pasta de mesmo nome disponível no link para download:


[DOWNLOAD - Base de imagens - T2ED](https://drive.google.com/drive/folders/1myZVmIY_j-1Bj4vEWI_FqXvHB66KLOVG)


- Para o funcionamento correto do programa, o executável criado após a compilação dos arquivos deve estar no mesmo diretório dos arquivos '.c'.

- Este programa utliliza, como base, imagens no formato '.pgm'. Todas imagens devem estar nesse formato para o correto funcionamento do programa.

- Para realizar uma consulta de imagens, é imprescindível que o nome da imagem colocada na pasta 'query' esteja com o nome "queryIMG.pgm". Utilize apenas uma imagem por vez para consulta.

- A base de dados já esta pré carregada com os histogramas médios, para que o programa possa ser utilizado imadiatamente para buscas de imagens. Entretanto, o usuário pode recarregar a base durante o uso  do programa (ver detalhes mais adiante em "Utilização do programa"). 

<hr >

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
<hr >

## Utilização do programa

Ao executar o programa, o usuário entra no menu principal e deverá selecionar uma das 3 opções oferecidas, digitando o seu número correspondente:

```
Digite o numero do que deseja fazer:
[1] Recarregar histogramas
[2] Consultar localidade
[0] SAIR
```
__[1] Recarregar histogramas__: Esta opção irá realizar a leitura da base de imagens, localidade por localidade, e vai gerar o histograma médio de cada uma delas. O histograma será salvo na pasta de cada localidade, com o nome de 'histogram.txt'. Como a leitura e geração dos histogramas medios é um processo relativamente demorado (cerca de 10 a 15 minutos em nossos testes) ao selecionar essa opção o programa solicitará q o usuário confirme sua escolha. Case escolha seguir, o programa realizará a recarga dos histogramas. Caso contrário, o programa retorna ao menu principal.

__[1] Consultar localidade__: Essa opção vai realizar a consulta da localidade baseada na imagem que se encontra na pasta 'query'. Como é necessário que tenha uma imagem na pasta 'query' para o funcionamento correto do programa, o programa vai pedir a confirmação do usuário pra prosseguir com a consulta. Caso ele prossiga, o programa processará a imagem da pasta 'query', vai selecionar as 5 localidades mais prováveis e escreverá na pasta 'results'. Além disso, os nomes das 5 localidades serão exibidos no console após o processo e o programa finalizará sua execução. Caso opte por não prosseguir com a consulta, o programa retorna ao menu principal.

__[0] SAIR__: O programa encerra sua execução e uma mensagem "Fim do programa" é exibida.

<hr >

## Ideia central do programa

Este tópico tem como objetivo explicar, em alto nível, a lógica adotada pelo grupo para a implementação do programa.

Temos 20 localidades, cada uma com pelo menos 10 fotos de ângulos variados. Espera-se que uma mesma localidade tenha uma distribuição de intensidade de brilho parecida nas fotos. Tiramos então dessa localidade um histograma médio de intensidades, que é a média dos histogramas individuais das fotos. Assim, cada localidade teria seu histograma médio, que é uma espécie de assinatura daquele local.

Colocamos esses histogramas médios em uma lista encadeada, extraimos o histograma da imagem pesquisada e podemos comparar, uma a uma, qual é a localidade que possui o histograma mais próximo ao da imagem pesquisada.

Ao final, retornamos ao usuário do programa as 5 localidades mais provavéis, ou seja, aquelas que a diferença de seu histograma para o histograma da imagem pesquisada é menor.

<hr >

## Funcionamento detalhado do programa

O Programa se divide em duas grandes tarefas: Extrair os histogramas médios(1) e realizar consulta de imagem(2). Para maior clareza das informações, os parâmetros das funções foram ocultados neste documento.

__[1] Extração dos histogramas médios__: Esta é a parte _offline_ do programa. Ao final deste processo cada localidade terá um arquivo 'histogram.txt' referente ao histograma médio da localidade.

1. _recarregarHistogramas(...)_: É a função que chama todo o processo. ela vai chamar a função _extratorLocalidade(...)_ para cada uma das 20 localidades na pasta base/img.
2. _extratorLocalidade(...)_: Cria uma lista encadeada de imagens (IMGs), chama a função _leitorPastas(...)_ que percorre a pasta da localidade, foto a foto.
3. _leitorPastas(...)_: para cada foto encontrada na imagem, chama uma função callback _preencheLista(...)_
4. _preencheLista(...)_: lê a imagem, extrai o IMG, adiciona a lista encadeada criada para a localidade
5. _lista_histExtractor(...)_: recebe a lista encadeada da localidade e gera o arquivo 'histogram.txt' que é a representação do histograma médio daquela localidade.

__[2] Consulta de imagem__: Esta é a parte _online_ do programa. Aqui será realizada a comparação do histograma da imagem pesquisada com os histogramas médios extraidos da base. Ao final desse processo, 5 localidades serão imprimidas na tela e a primeira foto de cada uma delas,da base de dados, será salva na pasta 'results'.

1. _listarHistogramasMedios(...)_: Vai criar uma lista encadeada de histogramas (listaH), percorrer todas localidades chamando a função _leArquivoHist(...)_ para cada uma delas. Esta função lê o histograma da localidade e e em seguida este histograma é adicionado na lista encadeada pela função _lista_histAppend(...)_.
2. _lerHistQuery(...)_: Função lê o histograma da imagem pesquisada que se encontra na pasta 'query'.
3. _lista_defineNotas(...)_: Preenche o vetor de notas das 20 localidades. As notas são referentes a proximidade do histograma pesquisado com o histograma médio da localidade. Quanto menor a nota, mais próximo são os locais.
4. É definido, diretamente na _main()_, o vetor com os índices das 5 localidades mais próximas.
5. _imprimeTop5(...)_: Recebe o vetor com os índices das 5 localidades mais próximas, extrai da base de imagens 5 IMGs (cada um referenete a primeira imagem de cada localidade possível) e salva essas imagens na pasta 'results'. Por fim, imprime no console as 5 localidades prováveis.

<hr >

## Estruturas de dados utilizadas

Descrições das principais estruturas de dados utilizadas no programa. Utilizamos em nosso trabalho o conceito de listas encadeadas para manipulação das imagens e dos dados extraidos dela. Utilizamos também dois tipos abstratos de dados (TADs): O tipo img e o tipo lista, que descreveremos a seguir.

### __IMG:__

O TAD img lida com o struct IMG, que é a estrutura que lida com as informações das imagens .pgm utilizadas no programa. O struct IMG possui todas informações do arquivo da imagem e um vetor que armazena o histograma da imagem. O TAD lida principalmente com a leitura e escrita das imagens. 

```
typedef struct {
  char tipo[5];
  int largura, altura;
  int brilhoMax;
  unsigned char **mat;
  unsigned int hist[256];
} IMG;
```

### __Lista:__

O TAD lista é o responsável pelas operações envolvendo listas encadeadas. Ele engloba dois tipos dinstintos de lista, cada uma com uma finalidade e um node próprio. A _Lista_ é composta pelo _ListaNode_, struct que guarda um ponteiro para um IMG. Ela é utilizada na parte _offline_, durante o processo de extração dos histogramas médios.

```
//Node utilizado pela Lista

struct listaNode {
  IMG *img;
  ListaNode *next;
};

```
Já o outro tipo de lista, o _ListaH_, utiliza o _HistNode_. Esse tipo de node armazena o diretório e o histograma médio de um local. Esse tipo de lista é utilizado na parte _online_ do programa, para listar todos os histogramas médios que serão comparados com o histograma da imagem na query.

```
//Node utilizado pela ListaH

struct histNode{
  char * local;
  unsigned int hist[256];
  HistNode *next;
};
```


<hr >

## Considerações finais

Esse trabalho foi muito desafiador, desde o início. Após muita conversa entre os membros do grupo e muitas conjecturas, conseguimos implementar uma solução satisfatória para o problema proposto. Conseguimos, também, aplicar os conhecimentos adquiridos em sala de aula cumprindo com o propósito real do trabalho que é o de consolidar nosso conhecimento sobre as estruturas de dados, como e quando utiliza-las e saber que sua utilização pode auxiliar muito na resolução dos problemas. O maior desafio (assim como no primeiro trabalho), sem dúvidas, foi a utilização da linguagem de programação C. Entretanto. mesmo com as dificuldades, conseguimos perceber nitidamente nossa evolução na programação com esta linguagem e como o domínio de seus conceitos é fundamental para entender estruturas de dados.
