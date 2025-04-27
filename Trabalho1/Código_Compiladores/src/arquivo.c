#include <stdlib.h>
#include <stdio.h>

#include "arquivo.h"
#include "lexico.h"

void escrever_arquivo(FILE *arquivo, char *conteudoToken, char *conteudoClass) {
    fputs(conteudoToken, arquivo);
    fputs(", ", arquivo);
    fputs(conteudoClass, arquivo);
    fputs("\n", arquivo);
}

int leitura_arquivo_lexico(const char *nome_arquivo){
    const char *nome_programa = nome_arquivo;
    const char *nome_output = "output.txt";
    remove(nome_output);

    //Verificando a abertura adequada do arquivo do código e a criação do de saída 
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
    char *classe, *token_atual;
    classe = calloc(30, sizeof(char));
    token_atual = calloc(100, sizeof(char));

    while (char_lido != EOF) { //Realizar a leitura até o fim do arquivo
        identifica_token(&char_lido, programa, &classe, &token_atual); //Identifica o par token-classe 

        escrever_arquivo(output, token_atual, classe); //Escreve o par token-classe no arquivo de saída
    }

    free(classe);
    free(token_atual);

    fclose(output);
    fclose(programa);
}


