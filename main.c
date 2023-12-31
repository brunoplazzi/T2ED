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
    
    char teste[] = "histogram.txt";
    
    if(strcmp(teste, name) != 0){
      char dict[81];
      dict[0] = '\0';

      strcat(dict, local);
      strcat(dict, name);


      IMG *img = lerArquivo(dict);
      lista_append(l, img);
    }
    
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

//extrai histograma da imagem do query
void lerHistQuery(unsigned int* hist){

  char queryDict[81] = "./query/queryIMG.pgm";
  
  IMG *queryIMG = lerArquivo(queryDict);

  for(int i=0; i<256;i++){
    hist[i] = queryIMG->hist[i];
  }

}

//recebe veror dos indices das 5 provaveis localidades e salva as fotos na pasta results
void imprimeTop5(int *vetor){

  // vetor com as localidades do ifes
  char *localidade[20] = {
    "bibliotecaEntrada",
    "bloco5",
    "bloco8Interno",
    "blocoInexistente",
    "caminhoLateral",
    "cantina",
    "corredorHallCantina",
    "escada",
    "estacionamento",
    "hall",
    "ifesEntrada",
    "laboratorioPaixao",
    "laboratorios700",
    "laboratorios900",
    "patioArvore",
    "patioEnsinoMedio",
    "patioProfessores",
    "patioXadrez",
    "quadra",
    "salaDeAulaSuperior",
  };

  char base[] = "./base/img/";
  char ext[] = "1.pgm";
  char baseResult[] = "./results/";
  
  char dict[81];
  char result[81];
  
  //ponteiro IMG auxiliar
  IMG * imageTop5;
  

  //ler as imagens e apendar
  for(int i = 0; i<5; i++){

    //ajeita o dict pra leitura
    strcpy(dict, base);
    strcat(dict, localidade[vetor[i]]);
    strcat(dict, "/");
    strcat(dict, localidade[vetor[i]]);
    strcat(dict, ext);

    imageTop5 = lerArquivo(dict);

    //ajeitando result para salvar imagem
    strcpy(result, baseResult);
    strcat(result, localidade[vetor[i]]);
    strcat(result, ext);
    
    salvarArquivo(imageTop5, result);

  }

  for(int i=0; i<5;i++){
    printf("%d %s\n",i+1, localidade[vetor[i]]);
  }

}





int main(void) {
  
  int i;
  
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
        printf("Recarga dos histogramas iniciada!\n");
        recarregarHistogramas();
      }
      
    }
    //opcao numero 2
    else if (escolha == 2){
      
      int confirm = -1;

      printf("Certifique-se de que a pasta [query] possui uma imagem com nome [queryIMG.pgm] e que a pasta [results] esta vazia\n");
      printf("Deseja prosseguir com a consulta de imagem?\n");
      printf("[1] Prosseguir\n");
      printf("[0] Voltar\n");

      scanf("%d", &confirm);

      if(confirm == 1){
        printf("Consulta de imagem iniciada!\n");
        
          //gerar lista com os histogramas medios
        ListaH* listaDeHists = listarHistogramasMedios();
        //nomeia as localidades
        lista_nomear(listaDeHists);

        //histograma da imagem pesquisada inicialmente zerado
        unsigned int queryHist[256];

        for(i=0; i<256; i++){
          queryHist[i] = 0;
        }

        //le imagem da query e escreve o seu histograma no hist recebido como parametro
        lerHistQuery(queryHist);


        //vetor com as notas referentes a proximidade zerado
        unsigned long int notasProximidade[20];

        for (i = 19;i >= 0;i--){
          notasProximidade[i] = 0;
        }

        //preenche vetor de notas
        lista_defineNotas(listaDeHists, queryHist, notasProximidade);

        
        //extracao dos indices dos 5 lugares mais proximos
        unsigned long int menorNota;
        int menorIndex;; 
        
        int indicesMenores[5] = {0,0,0,0,0};
        
        //por 5 vezes...
        for(int j=0;j<5;j++){
          
          //menor igual ao primeiro elemento
          menorNota = abs(notasProximidade[0]);
          menorIndex = 0;
          
          for(i=0;i<20;i++){
            if(notasProximidade[i] > 0){
              if(notasProximidade[i] <= menorNota){
                menorNota = notasProximidade[i];
                menorIndex = i;
              }
            }
          }
          notasProximidade[menorIndex] = -1; //para ser ignorado na proxima iteracao
          indicesMenores[j] = menorIndex;
        }

        imprimeTop5(indicesMenores);

        printf("\n");
        printf("Fim do programa\n");
        return 0;

      }

    }
  
  }
  
  printf("Fim do programa\n");

  return 0;
}
