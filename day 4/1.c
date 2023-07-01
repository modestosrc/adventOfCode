#include <stdio.h>

int contemInteiramente(int min1, int max1, int min2, int max2) {
    if (min1 >= min2 && max1 <= max2) return 1;
    if (min2 >= min1 && max2 <= max1) return 1;

    return 0;
}

int main(void) {
    int resposta = 0;
    char buffer[64];
    FILE *arquivo = fopen("input", "r");
    if (arquivo == NULL) {
        printf("Erro abrindo arquivo");
        return 1;
    }
    int max1, max2, min1, min2;

    while (fscanf(arquivo, "%d-%d,%d-%d", &min1, &max1, &min2, &max2) == 4) {
        resposta += contemInteiramente(min1, max1, min2, max2);
    }

    printf("%d\n", resposta);
    fclose(arquivo);
    return 0;
} 