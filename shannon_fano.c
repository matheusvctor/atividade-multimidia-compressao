#include <stdio.h>
#include <string.h>

// Estrutura para armazenar cada símbolo, sua probabilidade e o código gerado
typedef struct node {
    char sym[10];   // Símbolo
    float pro;      // Probabilidade ou frequência
    int arr[20];    // Array para armazenar os bits do código gerado
    int top;        // Índice (topo) do array de código
} node;

node p[20];

// Função recursiva para encontrar o código de Shannon-Fano
void shannon(int l, int h, node p[]) {
    float pack1 = 0, pack2 = 0, diff1 = 0, diff2 = 0;
    int i, k = 0, j;

    // Caso base: partição com apenas 1 ou 2 elementos
    if ((l + 1) == h || l == h || l > h) {
        if (l == h || l > h)
            return;
        p[h].arr[++(p[h].top)] = 0;
        p[l].arr[++(p[l].top)] = 1;
        return;
    } else {
        // Soma as probabilidades para encontrar o ponto de divisão mais equilibrado
        for (i = l; i <= h - 1; i++)
            pack1 = pack1 + p[i].pro;
        pack2 = pack2 + p[h].pro;
        diff1 = pack1 - pack2;
        if (diff1 < 0)
            diff1 = diff1 * -1;

        j = 2;
        while (j != h - l + 1) {
            k = h - j;
            pack1 = pack2 = 0;
            for (i = l; i <= k; i++)
                pack1 = pack1 + p[i].pro;
            for (i = h; i > k; i--)
                pack2 = pack2 + p[i].pro;
            diff2 = pack1 - pack2;
            if (diff2 < 0)
                diff2 = diff2 * -1;
            if (diff2 >= diff1)
                break;
            diff1 = diff2;
            j++;
        }
        k++;

        // Atribui 1 para o primeiro grupo (menor índice) e 0 para o segundo (maior índice)
        for (i = l; i <= k; i++)
            p[i].arr[++(p[i].top)] = 1;
        for (i = k + 1; i <= h; i++)
            p[i].arr[++(p[i].top)] = 0;

        // Chamadas recursivas para as duas metades
        shannon(l, k, p);
        shannon(k + 1, h, p);
    }
}

// Função para ordenar os símbolos por probabilidade (ordem crescente no vetor)
void sortByProbability(int n, node p[]) {
    int i, j;
    node temp;
    for (j = 1; j <= n - 1; j++) {
        for (i = 0; i < n - 1; i++) {
            if ((p[i].pro) > (p[i + 1].pro)) {
                temp.pro = p[i].pro;
                strcpy(temp.sym, p[i].sym);

                p[i].pro = p[i + 1].pro;
                strcpy(p[i].sym, p[i + 1].sym);

                p[i + 1].pro = temp.pro;
                strcpy(p[i + 1].sym, temp.sym);
            }
        }
    }
}

// Função para exibir os símbolos, probabilidades e códigos gerados
void display(int n, node p[]) {
    int i, j;
    printf("\n\tSimbolo\tProbabilidade\tCodigo");
    for (i = n - 1; i >= 0; i--) {
        printf("\n\t%s\t%.2f\t\t", p[i].sym, p[i].pro);
        for (j = 0; j <= p[i].top; j++)
            printf("%d", p[i].arr[j]);
    }
    printf("\n");
}

int main() {
    int n, i;
    float total = 0;

    printf("=== Algoritmo de Shannon-Fano ===\n");
    printf("Digite o numero de simbolos (ou 0 para usar o exemplo padrao do GeeksforGeeks): ");
    scanf("%d", &n);

    if (n <= 0) {
        n = 5;
        char ch[10];
        float x[] = { 0.22, 0.28, 0.15, 0.30, 0.05 };
        for (i = 0; i < n; i++) {
            sprintf(ch, "%c", 65 + i); // 'A', 'B', 'C', 'D', 'E'
            strcpy(p[i].sym, ch);
            p[i].pro = x[i];
            total += p[i].pro;
        }
    } else {
        for (i = 0; i < n; i++) {
            printf("Digite o simbolo %d: ", i + 1);
            scanf("%9s", p[i].sym);
            printf("Digite a probabilidade (ou frequencia) de %s: ", p[i].sym);
            scanf("%f", &p[i].pro);
            total += p[i].pro;
        }
    }

    // Ordena os símbolos com base em suas probabilidades
    sortByProbability(n, p);

    for (i = 0; i < n; i++)
        p[i].top = -1;

    // Encontra o código de Shannon-Fano
    shannon(0, n - 1, p);

    // Exibe os códigos gerados
    display(n, p);

    return 0;
}
