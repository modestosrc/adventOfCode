#include <stdio.h>
#include <stdlib.h>

int calculaPontos(int jogada_oponente, int jogada) {
    int i = jogada_oponente-'A';
    int j = jogada-'X';
    int pontos[3][3] = {
        {3+1, 6+2, 0+3},
        {0+1, 3+2, 6+3},
        {6+1, 0+2, 3+3}
    };
    return pontos[i][j];
}

int main(void) {
    char *local = "input";
    FILE *arquivo = fopen(local, "r");
    char buffer[64];
    int resultado = 0;

    while(fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        resultado += calculaPontos(buffer[0], buffer[2]); 
    } 

    printf("%d\n", resultado);
    fclose(arquivo);
}