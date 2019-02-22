#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define TAMANHO_HT 101

typedef struct
{
    char *Chave;
} hashTable;
hashTable *criaTabela(const int Tamanho)
{
    hashTable *Temp = (hashTable *)calloc(sizeof(hashTable), Tamanho);

    for (int init = 0; init < Tamanho; init++)
    {
        Temp[init].Chave = (char *)calloc(sizeof(char), 15);
    }
    return Temp;
}
int h(char *Chave)
{
    int k = 0;
    for (int i = 1; i <= strlen(Chave); i++)
    {
        k += Chave[i - 1] * i;
    }
    return k * 19;
}
int calculaHash(char *Chave)
{
    return h(Chave) % TAMANHO_HT;
}
int Colisoes(int *MediaDeAcessos, hashTable *tabela, char *Chave)
{
    int hash, conta = 1;

    for (int i = 0; i <= 20; i++)
    {
        hash = h(Chave) + (conta * conta) + (23 * conta);
        hash = hash % TAMANHO_HT;
        conta += 1;
        if (strlen(tabela[hash].Chave) == 0)
        {
            *MediaDeAcessos += i;
            return hash;
        }
    }
    return -1; //Deu erro!
}
void Inserir(int *MediaDeAcessos, hashTable *tabela, char *Chave)
{
    int hash = calculaHash(Chave);
    if (strlen(tabela[hash].Chave) == 0)
    {
        strcpy(tabela[hash].Chave, Chave);
        *MediaDeAcessos += 1;
    }
    else if (strcmp(tabela[hash].Chave, Chave) == 0)
    {
        printf("Chave [%s] já inserida!\n", Chave);

    }
    else
    {
        hash = Colisoes(MediaDeAcessos, tabela, Chave);
        if (hash != (-1))
        {
            strcpy(tabela[hash].Chave, Chave);
        }
    }
}
void Remover(int *MediaDeAcesos, hashTable *tabela, char *Chave)
{
    int hash = calculaHash(Chave);
    if (strlen(tabela[hash].Chave) != 0)
    {
        if (strcmp(tabela[hash].Chave, Chave) == 0)
        {
            strcpy(tabela[hash].Chave, "");
            *MediaDeAcesos += 1;
            return;
        }
        else
        {
            int hash, conta = 1;

            for (int i = 0; i <= 20; i++)
            {
                hash = h(Chave) + (conta * conta) + (23 * conta);
                hash = hash % TAMANHO_HT;
                conta += 1;
                if (strcmp(tabela[hash].Chave, Chave) == 0)
                {
                    strcpy(tabela[hash].Chave, "");
                    *MediaDeAcesos += i;
                    return;
                }
            }
        }
    }
}
void Listar(FILE *fileSaida, hashTable *tabela, const int Tamanho)
{
    int Count = 0;
    for (int i = 0; i < Tamanho; i++)
        if (strlen(tabela[i].Chave) != 0)
            Count++;

    fprintf(fileSaida, "%d\n", Count);

    for (int i = 0; i < Tamanho; i++)
        if (strlen(tabela[i].Chave) != 0)
            fprintf(fileSaida, "%d:%s\n", i, tabela[i].Chave);
}
int main(int argc, char const *argv[])
{
    hashTable *obj;
    FILE *Entrada = fopen(argv[1], "r");
    FILE *fileSaida = fopen(argv[2], "w");

    int Testes, Linhas;
    char *flag = (char *)calloc(sizeof(char), 15);
    clock_t startTime = clock();
    fscanf(Entrada, "%d", &Testes);

    int MediaDeAcessos = 0,g;

    for (int k = 0; k < Testes; k++)
    {
        obj = criaTabela(TAMANHO_HT);
        fscanf(Entrada, "%d", &Linhas);
        for (int l = 0; l < Linhas; l++)
        {
            fscanf(Entrada, "%s", flag);
            if (flag[0] == 'A')
            {
                Inserir(&MediaDeAcessos, obj, &(flag[4]));
            }
            else
            {
                Remover(&MediaDeAcessos, obj, &(flag[4]));
            }
        }
        printf("%d/%d ",MediaDeAcessos,Linhas);
        printf("Média de Acessos: %f\n", (float)MediaDeAcessos/Linhas);
        Listar(fileSaida, obj, TAMANHO_HT);
        MediaDeAcessos = 0;
    }
    printf("%f\n", (clock() - startTime) / (double)CLOCKS_PER_SEC);

    fclose(fileSaida);
    fclose(Entrada);
    free(obj);

    return 0;
}
