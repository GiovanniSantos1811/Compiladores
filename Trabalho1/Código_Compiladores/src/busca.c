#include <stdio.h>

// Função de busca em um vetor ordenado
int busca_binaria(int *vetor, int tamanho, int valor) {
    int inicio = 0, fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (vetor[meio] == valor)
            return meio;  // Encontrou o valor e retorna o índice 
        else if (vetor[meio] < valor)
            inicio = meio + 1;
        else
            fim = meio - 1;
    }

    return -1; // Não encontrado
}