#include <stdlib.h>
#include <stdio.h>
#define FALSE 0
#define TRUE 1

typedef struct TipoRegistro
{
  int Chave;
} TipoRegistro;
typedef struct TipoPagina *TipoApontador;
typedef struct TipoPagina
{
  int n;
  TipoRegistro *r;
  TipoApontador *p;
} TipoPagina;

typedef struct Celula_strFila *ApontadorFila;
typedef struct Celula_strFila
{
  int numAcessos;
  TipoPagina pagina;
  ApontadorFila Prox;
} CelulaFila;
typedef struct TipoFila
{
  ApontadorFila Frente, Tras;
} TipoFila;

TipoApontador Inicializa();
void InsereNaPagina(TipoApontador, TipoRegistro, TipoApontador);
void Ins(TipoRegistro, TipoApontador, short *, TipoRegistro *, TipoApontador *, int);
void InsereArvore(TipoRegistro, TipoApontador *, int);
void Reconstitui(TipoApontador, TipoApontador, int, short *, int);
void Antecessor(TipoApontador, int, TipoApontador, short *, int);
void Ret(int, TipoApontador *, short *, int);
void Retira(int, TipoApontador *, int);
int Enfileira(TipoPagina, TipoFila *, int, int *);
void Desenfileira(TipoFila *, int *);
int Vazia(TipoFila);
void PoliticaFIFO(int *missez, TipoApontador HD, int numPaginas, int numConsultas, int consultas, TipoFila *Ram);
int EstaNaMemoria(TipoFila, int, ApontadorFila *);
void ColocaNaMemoria(TipoPagina, TipoFila *, int, int *, int);
int Politicas(TipoApontador HD, int numPaginas, int numConsultas, int *consultas, TipoFila);
void Vizualiza(TipoRegistro *, TipoApontador, FILE *);
void FFVazia(TipoFila *);