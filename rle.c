#include <stdio.h>
#include <string.h>

char* rle(char *texto) {

    static char resultado[1000];
    int k = 0;
    int n = strlen(texto);

    // Percorre todos os caracteres do texto
    for (int i = 0; i < n; i++) {

        // Conta as ocorrências do caractere atual
        int count = 1;

        while (i < n - 1 && texto[i] == texto[i + 1]) {
            count++;
            i++;
        }

        // Adiciona o caractere ao resultado
        resultado[k++] = texto[i];

        // Converte a quantidade para string
        char temp[20];
        sprintf(temp, "%d", count);

        // Adiciona a quantidade ao resultado
        for (int j = 0; temp[j] != '\0'; j++) {
            resultado[k++] = temp[j];
        }
    }

    // Finaliza a string resultante
    resultado[k] = '\0';

    return resultado;
}

int main() {
    char texto[1000];

    printf("=== Algoritmo Run-Length Encoding (RLE) ===\n");
    printf("Digite a string para comprimir (ex: wwwwaaadexxxxxxywww): ");
    scanf("%999s", texto);

    printf("String comprimida: %s\n", rle(texto));

    return 0;
}
