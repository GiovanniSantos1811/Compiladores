#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_TABELA 22  // Estamos trabalhando com um fator de carga de 50% (vamos inserir 11 palavras com um vetor de 20)

// Estrutura de um nó da lista ligada
typedef struct tipo_no {
    char *palavra;
    struct tipo_no *prox;
} No;

// Tabela hash
No *tabela[TAM_TABELA];

// Função hash djb2 (uma função já criada que funciona bem para strings)
unsigned int hash(const char* str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;  // hash * 33 + c
    return hash % TAM_TABELA;
}

// Inserir uma palavra na tabela
void inserir(const char *palavra) { // Insere na cabeça da lista
    unsigned int indice = hash(palavra);
    
    // Verifica se a palavra já existe
    No *atual = tabela[indice];
    while (atual != NULL) { // Percorrendo a lista até o final
        if (strcmp(atual->palavra, palavra) == 0) 
            return;  // Palavra já existe, não insere de novo
        atual = atual->prox;
    }

    // Cria novo nó
    No *novo = malloc(sizeof(No));
    novo->palavra = strdup(palavra);  // duplica a string
    novo->prox = tabela[indice];
    tabela[indice] = novo;
}

// Buscar uma palavra na tabela
int buscar(const char *palavra) {
    unsigned int indice = hash(palavra);
    No *atual = tabela[indice];
    while (atual != NULL) {
        if (strcmp(atual->palavra, palavra) == 0)
            return 1;  // Encontrou
        atual = atual->prox;
    }
    return 0;  // Não encontrou
}

// Liberar memória da tabela
void liberar_tabela() {
    for (int i = 0; i < TAM_TABELA; i++) {
        No *atual = tabela[i];
        while (atual != NULL) {
            No *temp = atual;
            atual = atual->prox;
            free(temp->palavra);
            free(temp);
        }
    }
}