#include <stdlib.h>
#include <stdio.h>
#include "estruturas.h"

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Entrada Inválida!\n");
        return 0;
    }

    char *entrada = argv[1];
    char *saida = argv[2];

    int Tamanho, ordemArvore, numValores, numConsultas, j;
    ApontadorFila Aux = NULL;
    TipoApontador Disco = Inicializa();
    TipoRegistro Registro;
    TipoFila Memoria;
    FFVazia(&Memoria);

    FILE *ArquivoEntrada = fopen(entrada, "r");
    FILE *ArquivoSaida = fopen(saida, "w");

    fscanf(ArquivoEntrada, "%d", &Tamanho);
    fscanf(ArquivoEntrada, "%d", &ordemArvore);

    int numPaginas = 2; //(Tamanho / (4 * 2 * ordemArvore) + (4 * 2 * ordemArvore + 1));

    fscanf(ArquivoEntrada, "%d", &numValores);

    int *result = (int *)calloc(sizeof(int), numValores);

    for (j = 0; j < numValores; j++)
    {
        fscanf(ArquivoEntrada, "%d", &Registro.Chave);
        result[j] = Registro.Chave;
        InsereArvore(Registro, &Disco, ordemArvore);
    }

    fscanf(ArquivoEntrada, "%d", &numConsultas);
    int consultas[numConsultas];
    for (j = 0; j < numConsultas; j++)
    {
        fscanf(ArquivoEntrada, "%d", &consultas[j]);
    }
    int misses, fifom = 0;

    for (j = 0; j < numConsultas; j++)
    {
        Registro.Chave = consultas[j];
        if (EstaNaMemoria(Memoria, consultas[j], &Aux))
        {
            fprintf(ArquivoSaida, "hit\n");
        }
        else
        {
            Vizualiza(&Registro, Disco, ArquivoSaida);
            PoliticaFIFO(&misses, Disco, numPaginas, numConsultas, consultas[j], &Memoria);
            fifom += misses;
        }
    }
    fprintf(ArquivoSaida, "%d\n", fifom);
    fclose(ArquivoEntrada);
    fclose(ArquivoSaida);
    return 0;
}
