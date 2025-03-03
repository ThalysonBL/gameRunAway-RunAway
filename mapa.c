#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mapa.h"

void copiamapa(MAPA *destino, MAPA *origem)
{
  destino->linhas = origem->linhas;
  destino->colunas = origem->colunas;

  alocamapa(destino);

  for (int i = 0; i < origem->linhas; i++)
  {
    strcpy(destino->matriz[i], origem->matriz[i]); // essa função copia a string
  }
}

void andanomapa(MAPA *m, int xorigem, int yorigem, int xdestino, int ydestino)
{
  char personagem = m->matriz[xorigem][yorigem];
  m->matriz[xdestino][ydestino] = personagem;
  m->matriz[xorigem][yorigem] = VAZIO;
}

int ehvalida(MAPA *m, int x, int y)
{
  if (x >= m->linhas)
    return 0;
  if (y >= m->colunas)
    return 0;
  return 1;
}

int ehvazia(MAPA *m, int x, int y)
{
  return m->matriz[x][y] == VAZIO;
}

void encontramapa(MAPA *m, POSICAO *p, char c)
{
  for (int i = 0; i < m->linhas; i++)
  {
    for (int j = 0; j < m->colunas; j++)
    {
      if (m->matriz[i][j] == c)
      {
        p->x = i;
        p->y = j;
        break;
      }
    }
  }
}

void liberamapa(MAPA *m)
{
  for (int i = 0; i < m->linhas; i++) // para acessar o conteudo do ponteiro utilize '->'
  {
    free(m->matriz[i]); // ao acabar o programa precisamos liberar a memoria
  }
  free(m->matriz);
}

void alocamapa(MAPA *m)
{
  m->matriz = malloc(sizeof(char *) * m->linhas); // sizeof pega o tamanho do char (cada sistema pode ter um tamanho diferente do char, esse comando pega dinamicamente)
  for (int i = 0; i < m->linhas; i++)
  {
    m->matriz[i] = malloc(sizeof(char) * (m->colunas + 1)); // +1 para o '\0' no final
  }
}

void lemapa(MAPA *m)
{
  FILE *f;
  f = fopen("mapa.txt", "r");

  if (f == 0)
  {
    printf("Erro na leitura do mapa\n");
    exit(1);
  }
  fscanf(f, "%d %d", &(m->linhas), &(m->colunas));

  alocamapa(m);

  for (int i = 0; i < m->linhas; i++)
  {
    fscanf(f, "%s", m->matriz[i]);
  }

  fclose(f);
}

void imprimemapa(MAPA *m)
{
  for (int i = 0; i < m->linhas; i++)
  {
    printf("%s\n", m->matriz[i]);
  }
}