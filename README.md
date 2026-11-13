# Algoritmos de Compressão Sem Perdas em C

Implementação de três algoritmos clássicos de compressão de dados sem perdas (*Lossless Data Compression*) em linguagem **C**, utilizando como referência a abordagem algorítmica do [GeeksforGeeks](https://www.geeksforgeeks.org/):

1. **Run-Length Encoding (RLE)** — [`rle.c`](rle.c)
   - Referência: [Run Length Encoding - GeeksforGeeks](https://www.geeksforgeeks.org/problems/run-length-encoding/1)
2. **Algoritmo de Shannon–Fano** — [`shannon_fano.c`](shannon_fano.c)
   - Referência: [Shannon-Fano Algorithm for Data Compression - GeeksforGeeks](https://www.geeksforgeeks.org/dsa/shannon-fano-algorithm-for-data-compression/)
3. **Codificação de Huffman (Huffman Coding)** — [`huffman.c`](huffman.c)
   - Referência: [Huffman Coding | Greedy Algo-3 - GeeksforGeeks](https://www.geeksforgeeks.org/dsa/huffman-coding-greedy-algo-3/)

## Como Compilar e Executar

```bash
# Questão 1: Run-Length Encoding (RLE)
gcc rle.c -o rle
./rle

# Questão 2: Shannon-Fano
gcc shannon_fano.c -o shannon_fano
./shannon_fano

# Questão 3: Huffman Coding
gcc huffman.c -o huffman
./huffman
```
