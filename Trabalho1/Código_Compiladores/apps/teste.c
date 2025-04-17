#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "arquivo.h"
#include "automato.h"

// int main() {

//     inserir("danete");

//     if (buscar("danete")) {
//         printf("A palavra danete foi encontrada!\n");
//     } else {
//         printf("A palavra danete NAO foi encontrada!\n");
//     }


//     return 0;
// }

int main() {
    const char *nome_programa = "fatorialsemprocedimento.txt";
    const char *nome_saida = "output.txt";
    remove(nome_saida);

    // ler_arquivo_caractere(nome_programa);
    // escrever_arquivo(nome_saida, "testando");

    FILE *programa = fopen(nome_programa, "r");
    if (programa == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    char char_prox = fgetc(programa);
    char *token_atual;
    int estado_atual = 0;

    while (char_prox != EOF) {
        printf("prox caractere: %c\n", char_prox);
        estado_atual = transicao(char_prox, estado_atual);
        if(estado_atual < 0){

        } else {
            // coloca o char_prox no final do token_atual

        }
    }
    
    fclose(programa);
    return 0;
}