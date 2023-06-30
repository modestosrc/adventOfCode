#include <stdio.h>
#include <stdlib.h>

int checagem(char *lista);
void populaLista(char *lista);

int main(void)
{
    FILE *arquivo;
    arquivo = fopen("input", "r");
    if (arquivo == NULL)
    {
        printf("Erro abrindo arquivo\n");
        return 1;
    }

    char *letras = (char *)malloc(sizeof(char) * 14);
    if (letras == NULL)
    {
        printf("Erro alocando memoria\n");
        return 1;
    }
    populaLista(letras);

    int i = 0;
    int contador = 0;
    while ((letras[0] = fgetc(arquivo)) != EOF)
    {
        contador++;
        if (checagem(letras)) break;

        for (i = 13; i > 0; i--)
        {
            letras[i] = letras[i - 1];
        }
    }


    printf("%d\n", contador);
    free(letras);
    fclose(arquivo);
    return 0;
}

int checagem(char *lista)
{
    if (lista[13] == 0) return 0;
    
    int i, j;
    for (i = 0; i < 13; i++)
        for (j = i + 1; j <= 13; j++)
            if (lista[i] == lista[j]) return 0;

    return 1;
    
}

void populaLista(char *lista)
{
    for (int i = 0; i < 14; i++)
            lista[i] = 0;
}
