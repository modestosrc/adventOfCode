#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

long calculaPrioridade(char buffer[64]) {
    static int linha = 0; linha++;
    static unsigned char vistos[53] = {0};
    size_t comprimento_buffer = strlen(buffer);

    buffer[comprimento_buffer-1] = 0; comprimento_buffer--;
    assert(comprimento_buffer % 2 == 0);

    for (size_t i = 0; i < comprimento_buffer; i++) {
        long resultado;
        int id_linha = linha % 3;

        if (buffer[i] >= 'a') resultado = buffer[i] - 'a' + 1;
        else resultado = buffer[i] - 'A' + 27;

        vistos[resultado] |= 1 << id_linha;

        if (vistos[resultado] == 7) {
            memset(vistos, 0, sizeof(vistos));
            return resultado;
        }
    }

    return 0;
}

int main(void) {
    FILE *arquivo = fopen("input", "r");
    char buffer[64];
    long resposta = 0;

    while (fgets(buffer, sizeof(buffer), arquivo) != NULL)
    resposta += calculaPrioridade(buffer); 

    printf("%ld\n", resposta);
    fclose(arquivo);

    return 0;
}