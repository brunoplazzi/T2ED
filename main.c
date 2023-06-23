#include "img.h"
#include "lista.h"
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef void (*FileCallback)(const char *, Lista *, char *);

//percorre a pasta selecionada chamando a funcao callback (preencheLista), que preenche a lista de imagens da localidade
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


//le o nome do diretorio da imagem, extrai seu struct IMG, adiciona a lista de imagens da localidade
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

//gera o histograma medio da localidade
void extratorLocalidade(char *localidade) {

  // lista vazia criada
  Lista *lista = lista_create();

  leitorPastas(localidade, preencheLista, lista, localidade);

  // extrair histograma medio para o txt
  lista_histExtractor(lista, localidade);
}

//funcao que extrai os histogramas das localidades
void recarregarHistogramas(){
  
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

  for (int i = 0; i < 20; i++) {
    
    printf("Extraindo da localidade (%d/20)\n", i+1);
    extratorLocalidade(localidade[i]);

  }

}

//recebe uma localidade, le o histograma da pasta, preenche um histograma externo
void leArquivoHist(char *localidade, unsigned int *hist) {

  int i;

  // preenche hist com valores nulos
  for (i = 0; i < 256; i++) {
    hist[i] = 0;
  }

  // prepara o diretorio para leitura do arquivo
  char local[81];
  strcpy(local, localidade);
  char histogram[] = "histogram.txt";
  strcat(local, histogram);
  //printf("Local lido: %s\n", local);

  // abrindo arquivo
  FILE *in;
  in = fopen(local, "rt");
  if (in == NULL) {
    printf("Erro na leitura do arquivo\n");
  }

  // copiando valores do arquivo para o hist
  for (i = 0; i < 256; i++) {
    fscanf(in, "%d\n", &hist[i]);
  }

  fclose(in);

}



//percorrer as pastas e retornar uma lista de histogramas medios
ListaH * listarHistogramasMedios(){
  
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
  
  //cria lista vazia
  ListaH * l = listaH_create();

  //histograma auxiliar
  unsigned int histograma[256];

  //para cada localidade...
  for (int i=0; i< 20; i++){
    
    //ler o histograma da localidade e preencher o hist auxiliar
    leArquivoHist(localidade[i], histograma);
    
    //appenda a lista
    lista_histAppend(l, histograma, localidade[i]);
  }

  //retorna a lista
  return l;
}



int main(void) {
  
  
  
  //essaa funcoes a seguir vão dentro da opção 2 (consultar localidade)
  
  //gerar lista com os histogramas medios
  ListaH* listaDeHists = listarHistogramasMedios();
  //nomeia as localidades
  lista_nomear(listaDeHists);
  //print de teste
  lista_print(listaDeHists);

  
  
  
  
  // compara query com cada no da lista
  // retorna as cinco localidades mais provaveis

  

  printf("fim do programa\n");

  return 0;
}


//MENU ABAIXO
  
/*
  
  
  //menu de selecao do programa
  int escolha = -1;

  while(escolha != 0) {
    printf("Digite o numero do que deseja fazer:\n");
    printf("[1] Recarregar histogramas\n");
    printf("[2] Consultar localidade\n");
    printf("[0] SAIR\n\n");

    scanf("%d", &escolha);
  
    //opcao numero 1
    if(escolha == 1){
      
      int confirma = -1;
      
      printf("Deseja prosseguir com a recarga das localidades? Esse processo pode demorar um pouco.\n");
      printf("[1] Prosseguir\n");
      printf("[0] Voltar\n");

      scanf("%d", &confirma);

      if(confirma == 1){
        printf("executa a recarga dos histogramas\n");
        //recarregarHistogramas();
      }
      
    }
    //opcao numero 2
    else if (escolha == 2){
      printf("funcao que compara a localidade com a lista de histogramas medios");
    }
  
  }
*/
