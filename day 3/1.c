#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char reorganizacao(char buffer[64]) {
    size_t comprimento_buffer = strlen(buffer) - 1;
    char resposta[2] = "P";

    for (int i=0; i <= ((int)comprimento_buffer/2) -1; i++) {
        for (int j=(comprimento_buffer/2); j <= comprimento_buffer - 1; j++) {
            if (buffer[i] == buffer[j]) {
                return buffer[i];
            }
        }
    }

    return '\0';
}

long calculoPrioridade(char caractere) {
    if (caractere < 'a') return ((caractere - 'A') + 26 + 1);
    else return ((caractere - 'a') + 1);
}

int main(void) {
    FILE *arquivo = fopen("input", "r");
    char buffer[64];
    char letra_repetida[2];
    long resposta = 0;
    while (fgets(buffer, sizeof(buffer), arquivo)){
        letra_repetida[0] = reorganizacao(buffer);
        //letra_repetida[1] = '\0';
        resposta += calculoPrioridade(letra_repetida[0]);
    } 
    printf("%ld\n", resposta);
    fclose(arquivo);
    return 0;
}