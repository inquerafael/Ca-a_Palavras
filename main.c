#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define tamanho 10

typedef struct { // estrutura contem uma letra e uma flag
  char letra;
  int parteDePalavra; // flag: 0 - não, 1 - sim
} CelulaM;

void preencherMatriz(CelulaM matriz[tamanho][tamanho]) {
  const char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      matriz[i][j].letra =
          alfabeto[rand() % 26]; // preenche a matriz com letras aleatorias
      matriz[i][j].parteDePalavra =
          0; // todas as celulas comecam com 0 = sem palavra
    }
  }
}

int podeInserir(
    CelulaM matriz[tamanho][tamanho], char *palavra, int linha, int coluna,
    int direcao,
    int possivel) { // verifica se cabe a palavra e se a palavra ja foi inserida
  int len = strlen(palavra); // tamanho da palavra

  if (direcao == 0 && tamanho < len) { // Horizontal
    if (coluna + len > tamanho)
      return 0;
    for (int i = 0; i < len; i++) {
      // verifica se a letra é igual para nao modificar a palavra q ja usa a
      // celula
      if (matriz[linha][coluna + i].parteDePalavra == 1 &&
          matriz[linha][coluna + i].letra != palavra[i])
        // se a celula for diferente da celula(palavra q usa o espaço), retorna
        // 0
        return 0;
    }
  } else if (direcao == 1 && tamanho < len) { // Vertical
    if (linha + len > tamanho)
      return 0;

    for (int i = 0; i < len; i++) {
      if (matriz[linha][coluna + i].parteDePalavra == 1 &&
          matriz[linha][coluna + i].letra != palavra[i])
        return 0;
    }
  } else if (direcao == 2 && tamanho < len) { // Diagonal
    if (linha + len > tamanho || coluna + len > tamanho)
      return 0;
    for (int i = 0; i < len; i++) {
      if (matriz[linha][coluna + i].parteDePalavra == 1 &&
          matriz[linha][coluna + i].letra != palavra[i])
        return 0;
    }
  } else {
    printf("Direção inválida.\n");
    possivel = 0;
    return possivel;
  }
  return 1;
}

void inserirPalavra(CelulaM matriz[tamanho][tamanho], char *palavra) {
  int comprimento = strlen(palavra); // retotna um inteiro (tam. palavra)
  int linha, coluna, direcao;        // variaveis para a direcao
  int possivel = 1;
  do {
    linha = rand() % tamanho;  // sorteia uma linha
    coluna = rand() % tamanho; // sorteia uma coluna
    direcao = rand() % 3;      // 0: Horizontal, 1: Vertical, 2: Diagonal
  } while (!podeInserir(matriz, palavra, linha, coluna, direcao,
                        possivel) &&
           possivel == 1); // se a palavra nao cabe, sorteia novamente

  for (int i = 0; i < comprimento; i++) {
    if (direcao == 0) {
      // percorre matriz/palavra sobrescrevendo as celulas
      matriz[linha][coluna + i].letra = palavra[i];
      // recebe 1, indica que a palavra foi inserida na celula
      matriz[linha][coluna + i].parteDePalavra = 1;
    } else if (direcao == 1) { // o mesmo
      matriz[linha + i][coluna].letra = palavra[i];
      matriz[linha + i][coluna].parteDePalavra = 1;
    } else if (direcao == 2) { // o mesmo
      matriz[linha + i][coluna + i].letra = palavra[i];
      matriz[linha + i][coluna + i].parteDePalavra = 1;
    } else {
      printf("Nao foi possivel inserir a palavra");
      break;
    }
  }
}

void imprimirMatriz(CelulaM matriz[tamanho][tamanho]) {
  // percorre e imprime a matriz.
  for (int i = 0; i < tamanho; i++) {
    for (int j = 0; j < tamanho; j++) {
      printf("%c ", matriz[i][j].letra);
    }
    printf("\n");
  }
}

void escolhaPalavra(CelulaM matriz[tamanho][tamanho], char *palavras) {
  char resposta;

  printf("\t• Digite a palavra: ");
  scanf("%s", palavras);
  inserirPalavra(matriz, palavras);

  printf("\t• Nova Palavra? (s/n): ");
  scanf(" %c", &resposta);
  if (resposta == 's' || resposta == 'S') {
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