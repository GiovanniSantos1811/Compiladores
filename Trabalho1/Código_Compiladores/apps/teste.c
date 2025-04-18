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
    char *token_atual = NULL;
    token_atual = malloc(100*sizeof(char));
    int estado_atual = 0, cont = 0, flag = 0;
    char *classe;
    classe = "TESTE";

    while (char_lido != EOF) { //Fazendo a leitura caractere a caractere do programa
        /*if (flag == 0)
            char_lido = fgetc(programa);
        else
            token_atual[cont++] = char_lido;*/

        // scanf("%d", &flag);
        printf("char_lido: %c | estado_atual: %d | ", char_lido, estado_atual);
        estado_atual = transicao(char_lido, estado_atual);
        printf("novo estado: %d\n", estado_atual);

        if (estado_atual == 0){
            char_lido = fgetc(programa);
        }
        else if (estado_atual >= 0 && estado_atual != 5 && estado_atual != 3) {
            token_atual[cont++] = char_lido;
            char_lido = fgetc(programa);
        }
        else {
            token_atual[cont] = '\0';
            escrever_arquivo(output, token_atual, classe);
            printf("\nESCRITO:|%s|\n\n", token_atual);
            cont = 0;
            estado_atual = 0;
        }

        // if (estado_atual < 0){ //Estado Final
        //     if(cont == 0){
        //         token_atual[cont++] = char_lido;
        //         char_lido = fgetc(programa);
        //     }
        //     token_atual[cont] = '\0'; //Garantindo o caractere terminador de string para o token poder ser printado
        //     escrever_arquivo(output, token_atual, classe);
        //     printf("\nESCRITO:|%s|\n\n", token_atual);
            
        //     cont = 0;
        //     estado_atual = 0;
            
        //     free(token_atual);
        //     token_atual = malloc(100*sizeof(char));
        //     /*if (flag == 0)
        //         flag++;
        //     else   
        //         flag = 0;*/
            
        // }
        // else if (estado_atual != 0){ //Estado intermediário (garantindo que tenha saído do estado inicial)
        //     token_atual[cont++] = char_lido;
        //     char_lido = fgetc(programa);

        //     // printf("token_atual: ");
        //     // for(int i = 0; i < cont; i++){
        //     //     printf("%c", token_atual[i]);
        //     // }
        //     // printf("\n");
        // }
        // else {
        //     char_lido = fgetc(programa);
        // }
    }
    
    fclose(output);
    fclose(programa);
    return 0;
}
