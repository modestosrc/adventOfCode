#include <stdio.h>
#include <stdlib.h>

void updateMaior(long *maior, int n, long soma) {
    for (int i = 0; i < n; i++) {
        if (soma <= maior[i]) continue;
        for (int j = n-1; j > i; j--) maior[j] = maior[j-1];
        maior[i] = soma;
        break;
    }
}

int main(void) {
    char buffer[64];
    long maior[3] = {0}, soma = 0;
    char *caminho = "input";
    FILE *arquivo = fopen(caminho, "r");
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        if (buffer[0] == '\n' || buffer[0] == '\r') {
            updateMaior(maior, 3, soma);
            soma = 0;
            continue;
        }
        soma += strtol(buffer, NULL, 10);
    }
    printf("%ld\n", maior[0]+maior[1]+maior[2]);
}