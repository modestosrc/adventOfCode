#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LINHAS 9
#define COLUNAS  64

char **iniciaCarga() 
{
    char **caixas = (char **)malloc(LINHAS * sizeof(char *));
    if (caixas == NULL) 
        return NULL;

    for (int i = 0; i < COLUNAS; i++) 
    {
        caixas[i] = (char *)malloc(COLUNAS * sizeof(char));
        if (caixas[i] == NULL) 
            return NULL;
    }

    char valores[LINHAS][COLUNAS] = 
    {
        { 'R', 'S', 'L', 'F', 'Q', '\0' },
        { 'N', 'Z', 'Q', 'G', 'P', 'T', '\0' },
        { 'S', 'M', 'Q', 'B', '\0' },
        { 'T', 'G', 'Z', 'J', 'H', 'C', 'B', 'Q', '\0' },
        { 'P', 'H', 'M', 'B', 'N', 'F', 'S', '\0' },
        { 'P', 'C', 'Q', 'N', 'S', 'L', 'V', 'G', '\0' },
        { 'W', 'C', 'F', '\0' },
        { 'Q', 'H', 'G', 'Z', 'W', 'V', 'P', 'M', '\0' },
        { 'G', 'Z', 'D', 'L', 'C', 'N', 'R', '\0' }
    };

    for (int i = 0; i < LINHAS; i++) 
        strcpy(caixas[i], valores[i]);

    return caixas;
}

int contaColunas(char *lista) 
{
    int contador = 0;

    for (int i = 0; i < COLUNAS; i++) 
    {
        if (lista[i] == '\0')
            return contador;
        else
            contador++;
    }

    return 0;
}

void printResposta(char **carga, int *comprimentos)
{
    for (int i = 0; i < LINHAS; i++)
    {
        printf("%c", carga[i][comprimentos[i]]);
    }

    printf("\n");
}

int *listaComprimentos(char **carga)
{
    int *lista = (int *)malloc(LINHAS * sizeof(int));

    for (int i = 0; i < LINHAS; i++)
        lista[i] = contaColunas(carga[i]) - 1;

    return lista;
}

void executaAcao(char **carga, int *comprimentos,int caixas, int de, int para)
{
    int i, index, comprimentoDe;
    de--;
    para--;
    index = comprimentos[de] - caixas + 1;
    comprimentoDe = comprimentos[de];
    //printf("%d %d %d %d %d\n", caixas, de, para, colunade, colunapara);

    for (int i = index; i <= comprimentoDe; i++)
    {
        //printf("%c %c\n", carga[para][colunapara], carga[de][colunade]);
        carga[para][++comprimentos[para]] = carga[de][i];
        comprimentos[de]--;
    }

    carga[de][comprimentos[de] + 1] = '\0';
    carga[para][comprimentos[para] + 1] = '\0';
}

int main(void) 
{
    char **carga;
    carga = iniciaCarga();
    char resposta[10];
    int *comprimentos = listaComprimentos(carga);

    char buffer[64];
    FILE *arquivo = fopen("input", "r");
    if (arquivo == NULL)
    {
        printf("Erro abrindo arquivo");
        return 1;
    }

    int caixas, de, para;
    while (fscanf(arquivo, "move %d from %d to %d\n", &caixas, &de, &para) == 3)
    {
        executaAcao(carga, comprimentos, caixas, de, para);
    }

    printResposta(carga, comprimentos);

    fclose(arquivo);
    free(comprimentos);
    free(carga);

    return 0;
}
