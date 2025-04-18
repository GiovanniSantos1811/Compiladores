#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "arquivo.h"
#include "automato.h"

int main() {
    const char *nome_programa = "fatorialsemprocedimento.txt";
    const char *nome_output = "output.txt";
    remove(nome_output);

    FILE *programa = fopen(nome_programa, "r");
    if (programa == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    FILE *output = fopen(nome_output, "w");
    if (output == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    char char_lido = fgetc(programa);
    char *classe, *token_atual = NULL;
    classe = "TESTE"; // AJUSTAR
    token_atual = malloc(100*sizeof(char));
    int estado_atual = 0, cont = 0;

    while (char_lido != EOF) { //Fazendo a leitura caractere a caractere do programa
        printf("char_lido: %c | estado_atual: %d | ", char_lido, estado_atual);
        estado_atual = transicao(char_lido, estado_atual);
        printf("novo estado: %d\n", estado_atual);

        if (estado_atual == 0){
            char_lido = fgetc(programa);
        }
        else if (estado_atual >= 0 && estado_atual != 5 && estado_atual != 3 && estado_atual != 16 && estado_atual != 12) { // AJUSTAR
        // else if (estado_atual >= 0) {
            token_atual[cont++] = char_lido;
            char_lido = fgetc(programa);
        }
        else {
            token_atual[cont] = '\0';
            escrever_arquivo(output, token_atual, classe);
            printf("\nESCRITO:|%s|\n\n", token_atual);
            cont = 0;
            estado_atual = 0;
            free(token_atual);
            token_atual = malloc(100*sizeof(char));
        }
    }

    if (estado_atual == 26){ // AJUSTAR
        token_atual[cont] = '\0';
        escrever_arquivo(output, token_atual, classe);
    } else {
        printf("Erro de Finalização do Programa.\n");
    }

    fclose(output);
    fclose(programa);
    return 0;
}