#include <stdio.h>
#include <stdlib.h>

// Altura máxima da Árvore de Huffman
#define MAX_TREE_HT 100

// Nó da Árvore de Huffman
struct MinHeapNode {
    char data;                          // Caractere de entrada
    unsigned freq;                      // Frequência do caractere
    struct MinHeapNode *left, *right;   // Filhos esquerdo e direito
};

// Min-Heap: coleção de nós da árvore de Huffman (fila de prioridade)
struct MinHeap {
    unsigned size;                      // Tamanho atual da min-heap
    unsigned capacity;                  // Capacidade da min-heap
    struct MinHeapNode** array;         // Array de ponteiros para os nós
};

// Função utilitária para alocar um novo nó da árvore
struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Função utilitária para criar uma min-heap de dada capacidade
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Função utilitária para trocar dois nós da min-heap
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Função padrão minHeapify para manter a propriedade de heap mínima
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < (int)minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
        smallest = left;

    if (right < (int)minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Verifica se o tamanho da heap é 1
int isSizeOne(struct MinHeap* minHeap) {
    return (minHeap->size == 1);
}

// Extrai o nó de menor valor (frequência) da heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Insere um novo nó na min-heap
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = minHeapNode;
}

// Constrói a min-heap
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    int i;
    for (i = (n - 1) / 2; i >= 0; --i)
        minHeapify(minHeap, i);
}

// Imprime um array de tamanho n (usado para exibir o código binário)
void printArr(int arr[], int n) {
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

// Verifica se o nó é uma folha
int isLeaf(struct MinHeapNode* root) {
    return !(root->left) && !(root->right);
}

// Cria uma min-heap de capacidade igual a size e insere todos os caracteres
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; ++i)
        minHeap->array[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}

// Função principal que constrói a Árvore de Huffman
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode *left, *right, *top;

    // Passo 1: Cria uma min-heap com capacidade igual a size
    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    // Itera enquanto o tamanho da heap não for 1
    while (!isSizeOne(minHeap)) {
        // Passo 2: Extrai os dois itens de menor frequência da min-heap
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        // Passo 3: Cria um novo nó interno com frequência igual à soma das
        // frequências dos dois nós. '$' é um valor especial para nós internos.
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    // Passo 4: O nó restante é o nó raiz e a árvore está completa
    return extractMin(minHeap);
}

// Imprime os códigos de Huffman a partir da raiz da Árvore de Huffman
void printCodes(struct MinHeapNode* root, int arr[], int top) {
    // Atribui 0 para a aresta esquerda e faz chamada recursiva
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    // Atribui 1 para a aresta direita e faz chamada recursiva
    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    // Se for um nó folha, contém um dos caracteres de entrada:
    // imprime o caractere e seu código armazenado em arr[]
    if (isLeaf(root)) {
        printf("%c: ", root->data);
        printArr(arr, top);
    }
}

// Função principal que constrói a Árvore de Huffman e imprime os códigos
void HuffmanCodes(char data[], int freq[], int size) {
    // Constrói a Árvore de Huffman
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);

    // Imprime os códigos usando a árvore construída
    int arr[MAX_TREE_HT], top = 0;
    printf("\nCodigos de Huffman gerados:\n");
    printCodes(root, arr, top);
}

int main() {
    int size;

    printf("=== Algoritmo de Codificacao de Huffman ===\n");
    printf("Digite a quantidade de caracteres (ou 0 para usar o exemplo padrao do GeeksforGeeks): ");
    scanf("%d", &size);

    if (size <= 0) {
        char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
        int freq[] = { 5, 9, 12, 13, 16, 45 };
        size = sizeof(arr) / sizeof(arr[0]);
        HuffmanCodes(arr, freq, size);
    } else {
        char arr[100];
        int freq[100];
        for (int i = 0; i < size; i++) {
            printf("Digite o caractere %d: ", i + 1);
            scanf(" %c", &arr[i]);
            printf("Digite a frequencia de '%c': ", arr[i]);
            scanf("%d", &freq[i]);
        }
        HuffmanCodes(arr, freq, size);
    }

    return 0;
}
