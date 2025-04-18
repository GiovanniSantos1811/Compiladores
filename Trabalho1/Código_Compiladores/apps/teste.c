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
    token_atual = calloc(100, sizeof(char));
    int estado_atual = 0, cont = 0;

    while (char_lido != EOF) { //Fazendo a leitura caractere a caractere do programa
        //printf("char_lido: %c | estado_atual: %d | ", char_lido, estado_atual);
        estado_atual = transicao(char_lido, estado_atual);
        //printf("novo estado: %d\n", estado_atual);

        if (estado_atual == 0){ //Estado inicial
            char_lido = fgetc(programa);
        }
        else if (estado_atual > 0) { //Estado intermediário
            token_atual[cont++] = char_lido;
            char_lido = fgetc(programa);
        }
        else { //Estado final
            if (cont > 0){ //Adicionando o caracter terminador nos tokens de palavras
                token_atual[cont] = '\0';
            }
            else{ //Armazenando vírgulas, pontos, etc. (não tem estado intermediário, vai direto do inicial pro final)
                token_atual[0] = char_lido;
                token_atual[1] = '\0';
                char_lido = fgetc(programa);
            }
            //escrever_arquivo(output, token_atual, classe);
            printf("\nESCRITO:|%s|\n\n", token_atual);
            
            cont = 0;
            estado_atual = 0;
            free(token_atual);
            token_atual = calloc(100, sizeof(char));
        }
    }

    if (transicao(char_lido, estado_atual) < 0){
        token_atual[cont] = '\0';
        escrever_arquivo(output, token_atual, classe);
        printf("\nESCRITO:|%s|\n\n", token_atual);
    } else {
        printf("Erro de Finalização do Programa.\n");
    }

    fclose(output);
    fclose(programa);
    return 0;
}


/*int main() {
    
    int a = transicao('}', 22);
    printf("Estado atual: %d\n", a);

    return 0; 
}*/