#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char encontraLetraIgual(char buffer[64]) {
    static char buffer_array[3][64];
    static int contador = 0;
    strcpy(buffer_array[contador], buffer);
    contador++;

    if ((contador % 3) != 0) return '\0';
    for (int i = 0; i < (strlen(buffer_array[0])) - 1; i++) {
        for (int j = 0; j < (strlen(buffer_array[1])) - 1; j++) {
            for (int k = 0; k < (strlen(buffer_array[2])) - 1; k++) {
                if (buffer_array[0][i] == buffer_array[1][j] && buffer_array[0][i] == buffer_array[2][k]) {
                    contador = 0;
                    return buffer_array[0][i]; 
                }
            }
        }
    }
}


long calculoPrioridade(char caractere) {
    if (caractere == '\0') return 0;
    if (caractere < 'a') return ((caractere - 'A') + 26 + 1);
    else return ((caractere - 'a') + 1);
}

int main(void) {
    FILE *arquivo = fopen("input", "r");
    char buffer[64];
    char letra_repetida[2];
    long resposta = 0;
    while (fgets(buffer, sizeof(buffer), arquivo) != NULL){
        letra_repetida[0] = encontraLetraIgual(buffer);
        letra_repetida[1] = '\0';
        resposta += calculoPrioridade(letra_repetida[0]);
    } 
    printf("%ld\n", resposta);
    fclose(arquivo);
    return 0;
}