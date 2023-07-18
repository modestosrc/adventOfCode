#include <stdio.h>
#include <stdlib.h>

int calcPontos(int jogada_oponente, int resultado) {
    int i = jogada_oponente-'A';
    int j = resultado-'X';

    static int pontos[3][3] = {
        {0+3, 3+1, 6+2},
        {0+1, 3+2, 6+3},
        {0+2, 3+3, 6+1}
    };

    return pontos[i][j];
}

int main(void) {
    char *local = "input";
    FILE *arquivo = fopen(local, "r");
    char buffer[64];
    int pontos = 0;

    while(fgets(buffer, sizeof(buffer), arquivo) != NULL) {
        pontos += calcPontos(buffer[0], buffer[2]);
    } 

    printf("%d\n", pontos);
    fclose(arquivo);
}
