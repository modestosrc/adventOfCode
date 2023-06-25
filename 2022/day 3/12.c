#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    FILE *arquivo = fopen("input", "r");
    long resposta = 0;
    char buffer[64];

    while (fgets(buffer, sizeof(buffer), arquivo)) {
        long valor_letra;
        size_t tamanho_buffer = strlen(buffer);
        static unsigned char mapa_bits[53];

        buffer[tamanho_buffer-1] = 0; tamanho_buffer--;

        for (size_t i = 0; i < tamanho_buffer; i++) {

           if (buffer[i] >= 'a') valor_letra = buffer[i] - 'a' + 1;
           else valor_letra = buffer[i] - 'A' + 26 + 1;

           if (i < (tamanho_buffer / 2)) {
            mapa_bits[valor_letra] = 1;
           } else {
                if (mapa_bits[valor_letra]) {
                 resposta += valor_letra;
                 memset(mapa_bits, 0, sizeof(mapa_bits));
                }
            }

        }

        
    }

    fclose(arquivo);
    printf("%ld\n", resposta);
    
    return 0;
}