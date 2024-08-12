#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define tamanho 30

typedef struct {
  char letra;
  int parteDePalavra; // 0 - não, 1 - sim
} CelulaM;

void preencherMatriz(CelulaM matriz[tamanho][tamanho]) {
  const char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      matriz[i][j].letra = alfabeto[rand() % 26];
      // inicialza a matriz e atribui parteDePalavra = 0
      matriz[i][j].parteDePalavra = 0;
    }
  }
}

int podeInserir(CelulaM matriz[tamanho][tamanho], char *palavra, int linha,
                int coluna, int direcao) {
  int len = strlen(palavra);
  if (direcao == 0) { // Horizontal
    if (coluna + len > tamanho)
      return 0;
    for (int i = 0; i < len; i++) {
      if (matriz[linha][coluna + i].parteDePalavra)
        return 0;
    }
  } else if (direcao == 1) { // Vertical
    if (linha + len > tamanho)
      return 0;
    for (int i = 0; i < len; i++) {
      if (matriz[linha][coluna + i].parteDePalavra)
        return 0;
    }
  } else if (direcao == 2) { // Diagonal
    if (linha + len > tamanho || coluna + len > tamanho)
      return 0;
    for (int i = 0; i < len; i++) {
      if (matriz[linha][coluna + i].parteDePalavra)
        return 0;
    }
  }
  return 1;
}

void inserirPalavra(CelulaM matriz[tamanho][tamanho], char *palavra) {
  int comprimento = strlen(palavra);
  int linha, coluna, direcao;
  do {
    linha = rand() % tamanho;
    coluna = rand() % tamanho;
    direcao = rand() % 3; // 0: Horizontal, 1: Vertical, 2: Diagonal
  } while (!podeInserir(matriz, palavra, linha, coluna, direcao));

  for (int i = 0; i < comprimento; i++) {
    if (direcao == 0) {
      matriz[linha][coluna + i].letra = palavra[i];
      matriz[linha][coluna + i].parteDePalavra = 1;
    } else if (direcao == 1) {
      matriz[linha + i][coluna].letra = palavra[i];
      matriz[linha + i][coluna].parteDePalavra = 1;
    } else if (direcao == 2) {
      matriz[linha + i][coluna + i].letra = palavra[i];
      matriz[linha + i][coluna + i].parteDePalavra = 1;
    }
  }
}

void imprimirMatriz(CelulaM matriz[tamanho][tamanho]) {
  // imprime a matriz
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      printf("%c ", matriz[i][j].letra);
    }
    printf("\n");
  }
}

void escolhaPalavra(CelulaM matriz[tamanho][tamanho], char *palavras) {
  char resposta;
  printf("Digite a palavra: ");
  scanf("%s", palavras);

  printf("digitar nova palavra? (s/n): ");
  scanf(" %c", &resposta);
  if (resposta == 's' || resposta == 'S') {
    inserirPalavra(matriz, palavras);
    escolhaPalavra(matriz, palavras);
  }
}

int main(void) {
  srand(time(NULL));
  CelulaM matriz[tamanho][tamanho]; // inicializa a matriz
  preencherMatriz(matriz);

  char palavras[tamanho]; // escolhe as palavras q vao ser inseridas
  escolhaPalavra(matriz, palavras);

  imprimirMatriz(matriz);
  return 0;
}