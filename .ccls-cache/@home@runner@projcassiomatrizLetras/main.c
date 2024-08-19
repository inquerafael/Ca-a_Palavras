#include <stdio.h>

#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ANSI_COLOR_RED "\x1b[31m" // cores em ANSI utilizadas
#define ANSI_COLOR_GRAY "\e[0;37m"
#define ANSI_COLOR_RESET "\x1b[0m"

#define tamanho 30

typedef struct { // estrutura contem uma letra e uma flag
  char letra;
  int parteDePalavra; // flag: 0 - não, 1 - sim
  char *cor;
} CelulaM;

void preencherMatriz(CelulaM matriz[tamanho][tamanho]) {
  const char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      matriz[i][j].letra =
          alfabeto[rand() % 26]; // preenche a matriz com letras aleatorias
      matriz[i][j].parteDePalavra =
          0; // todas as celulas comecam com 0 = sem palavra
      matriz[i][j].cor = ANSI_COLOR_RESET;
    }
  }
}

int podeInserir(CelulaM matriz[tamanho][tamanho], char *palavra, int linha,
                int coluna, int direcao) {
  // verifica se cabe a palavra e se a palavra ja foi inserida
  int len = strlen(palavra); // tamanho da palavra

  if (direcao == 0) { // Horizontal
    if (coluna + len > tamanho) {
      return 0;
    }

    for (int i = 0; i < len; i++) {
      // verifica se a letra é igual para nao modificar a palavra q ja usa a
      // celula
      if (matriz[linha][coluna + i].parteDePalavra == 1) {
        // se a celula for diferente da celula(palavra q usa o espaço), retorna
        // 0
        return 0;
      }
    }
  } else if (direcao == 1) { // Vertical
    if (linha + len > tamanho) {
      return 0;
    }

    for (int i = 0; i < len; i++) {
      if (matriz[linha][coluna + i].parteDePalavra == 1) {
        return 0;
      }
    }
  } else if (direcao == 2) { // Diagonal
    if (linha + len > tamanho || coluna + len > tamanho) {
      return 0;
    }
    for (int i = 0; i < len; i++) {
      if (matriz[linha][coluna + i].parteDePalavra == 1) {
        return 0;
      }
    }
  } else {
    printf("Direção inválida.\n");
    return 0;
  }
  return 1;
}

void inserirPalavra(CelulaM matriz[tamanho][tamanho], char *palavra,
                    char *cor) {
  // variaveis para a direcao
  int linha, coluna, direcao;
  // retotna um inteiro (tam. palavra)
  int comprimento = strlen(palavra);

  do {
    linha = rand() % tamanho;  // sorteia uma linha
    coluna = rand() % tamanho; // sorteia uma coluna
    direcao = rand() % 3;      // 0: Horizontal, 1: Vertical, 2: Diagonal
  } while (!podeInserir(matriz, palavra, linha, coluna,
                        direcao)); // se a palavra nao cabe, sorteia novamente

  for (int p = 0; p < comprimento; p++) {
    if (direcao == 0) {
      // percorre matriz/palavra sobrescrevendo as celulas
      matriz[linha][coluna + p].letra = palavra[p];
      matriz[linha][coluna + p].cor = cor;
      // recebe 1, indica que a palavra foi inserida na celula
      matriz[linha][coluna + p].parteDePalavra = 1;

    } else if (direcao == 1) { // o mesmo

      matriz[linha + p][coluna].letra = palavra[p];
      matriz[linha + p][coluna].cor = cor;
      matriz[linha + p][coluna].parteDePalavra = 1;
    } else if (direcao == 2) { // o mesmo

      matriz[linha + p][coluna + p].letra = palavra[p];
      matriz[linha + p][coluna + p].cor = cor;
      matriz[linha + p][coluna + p].parteDePalavra = 1;
    }
  }
}

void imprimirMatriz(CelulaM matriz[tamanho][tamanho]) {
  // percorre e imprime a matriz.
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      printf("%s%c%s ", matriz[i][j].cor, matriz[i][j].letra, ANSI_COLOR_RESET);
    }
    printf("\n");
  }
}

/*void jogar(CelulaM matriz[tamanho][tamanho], char palavras) {
  int linha, coluna, direcao, cont = 0;
  //char resposta;
  //int p=0;
  //int li=0;
  do {
    printf("\t• Digite a linha: ");
    scanf("%d", &linha);
    printf("\t• Digite a coluna: ");
    scanf("%d", &coluna);
    printf("\n(0 - horizontal | 1 - vertical | 2 - dagonal)\n");
    printf("\t• Digite a direção: ");
    scanf("%d", &direcao);


    if (podeInserir(matriz, palavras, linha, coluna, direcao)) {
      verificaPalavra(matriz, palavras);
    }

  } while (cont < 5);
}*/
int main(void) {
  srand(time(NULL));
  CelulaM matriz[tamanho][tamanho]; // inicializa a matriz
  preencherMatriz(matriz);

  // palavras pre definidas
  char palavras[][tamanho] = {"carro",    "bike",      "cassio",    "completo",
                              "trabalho", "atividade", "computador"};

  // inserirPalavra(matriz, *palavras);
  int cont = 0;
  for (int i = 0; i < 7; i++) {
    inserirPalavra(matriz, palavras[i], ANSI_COLOR_RED);
  }
  // mostras as palavras disponiveis
  printf("Palavras disponiveis:\n");
  for (int i = 0; i < 7; i++) {
    printf("• %s ", palavras[i]);
    cont++;
    if (cont == 4) {
      printf("\n");
      cont = 0;
    }
  }
  printf("\n\n");
  imprimirMatriz(matriz);
  // jogar(matriz, *palav);

  // imprimirMatriz(matriz);
  return 0;
}