#include "estruturas.h"
#include <stdio.h>
#include <stdlib.h>


void PesquisaArvore(TipoRegistro *x, TipoApontador Ap, TipoFila *memoria, int numPaginas, int *tamanhoFila, int *misses, int tipo)
{
    int i = 1;
    ApontadorFila aux;

    while (i < Ap->n && x->Chave > Ap->r[i - 1].Chave)
        i++;
    if (x->Chave == Ap->r[i - 1].Chave)
    {
        if (!EstaNaMemoria(*memoria, x->Chave, &aux))
        {
            (*misses)++;
            ColocaNaMemoria(*Ap, memoria, numPaginas, tamanhoFila, tipo);
        }
        *x = Ap->r[i - 1];
        return;
    }
    if (x->Chave < Ap->r[i - 1].Chave)
    {
        if (!EstaNaMemoria(*memoria, Ap->r[0].Chave, &aux))
        {
            (*misses)++;
            ColocaNaMemoria(*Ap, memoria, numPaginas, tamanhoFila, tipo);
        }
        PesquisaArvore(x, Ap->p[i - 1], memoria, numPaginas, tamanhoFila, misses, tipo);
    }
    else
    {
        if (!EstaNaMemoria(*memoria, Ap->r[0].Chave, &aux))
        {
            (*misses)++;
            ColocaNaMemoria(*Ap, memoria, numPaginas, tamanhoFila, tipo);
        }
        PesquisaArvore(x, Ap->p[i], memoria, numPaginas, tamanhoFila, misses, tipo);
    }
}
void PoliticaFIFO(int * missez, TipoApontador HD, int numPaginas, int numConsultas, int consultas, TipoFila *Ram)
{
    TipoRegistro x;
    int misses = 0, tamanhoFila = 0;

    FFVazia(Ram);
    x.Chave = consultas;
    PesquisaArvore(&x, HD, Ram, numPaginas, &tamanhoFila, &misses, 0);
    *missez = misses;
}

void Vizualiza(TipoRegistro *x, TipoApontador Ap, FILE *fpSaida)
{
    long i = 1, j;
    while (i < Ap->n && x->Chave > Ap->r[i - 1].Chave)
    {
        i++;
    }
    if (x->Chave == Ap->r[i - 1].Chave)
    {
        for (j = 0; j < Ap->n; j++)
        {
            fprintf(fpSaida, "%d ", Ap->r[j].Chave);
        }
        fprintf(fpSaida, "\n");
        return;
    }
    if (x->Chave < Ap->r[i - 1].Chave)
    {
        for (j = 0; j < Ap->n; j++)
        {
            fprintf(fpSaida, "%d ", Ap->r[j].Chave);
        }
        Vizualiza(x, Ap->p[i - 1], fpSaida);
    }
    else
    {
        for (j = 0; j < Ap->n; j++)
        {
            fprintf(fpSaida, "%d ", Ap->r[j].Chave);
        }
        Vizualiza(x, Ap->p[i], fpSaida);
    }
}

int Politicas(TipoApontador HD, int numPaginas, int numConsultas, int *consultas, TipoFila memoria)
{
    TipoRegistro x;
    int i, tipo = 0, misses = 0, tamanhoFila = 0;

    FFVazia(&memoria);

    for (i = 0; i < numConsultas; i++)
    { 
        x.Chave = consultas[i];
        PesquisaArvore(&x, HD, &memoria, numPaginas, &tamanhoFila, &misses, tipo);
    }
    return misses;
}

int EstaNaMemoria(TipoFila memoria, int registro, ApontadorFila *retorno)
{
    int n, j;
    ApontadorFila aux;
    TipoPagina pag;

    aux = memoria.Frente;
    while (aux->Prox != NULL)
    {                            
        pag = aux->Prox->pagina; 
        n = aux->Prox->pagina.n; 
        for (j = 0; j < n; j++)
        {
            if (registro == pag.r[j].Chave)
            {
                *retorno = aux;
                return TRUE;
            }
        }
        aux = aux->Prox;
    }
    return FALSE;
}

void ColocaNaMemoria(TipoPagina pag, TipoFila *memoria, int numPaginas, int *tamanhoFila, int tipo)
{
    if (!Enfileira(pag, memoria, numPaginas, tamanhoFila))
    {
        Desenfileira(memoria, tamanhoFila);
        Enfileira(pag, memoria, numPaginas, tamanhoFila);
    }
}
