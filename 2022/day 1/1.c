#include <stdio.h>
#include <stdlib.h>

void updateMaior(long *maior, long soma) {
    if (soma > *maior) *maior = soma;
}

int main(void) {
    char buffer[64];
    long maior = 0, soma = 0;
    char *caminho = "input";
    FILE *arquivo = fopen(caminho, "r");
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        if (buffer[0] == '\n' || buffer[0] == '\r') {
            updateMaior(&maior, soma);
            soma = 0;
            continue;
        }
        soma += strtol(buffer, NULL, 10);
    }
    printf("%ld\n", maior);
}