#include <stdlib.h>
#include <stdio.h>

#include "arquivo.h"
#include "lexico.h"
#include "sintatico.h"

//------------------------ Léxico -------------------------------------
void saida_lexico(FILE *arquivo, char *conteudoToken, char *conteudoClass) {
    fputs(conteudoToken, arquivo);
    fputs(", ", arquivo);
    fputs(conteudoClass, arquivo);
    fputs("\n", arquivo);
}

int leitura_arquivo_lexico(const char *nome_arquivo){ //Função que realiza a identificação dos tokens do programa como um todo (fins didáticos apenas)

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
    int cont_linha = 1;

    while (1) { //Realizar a leitura do arquivo
        identifica_token(&char_lido, programa, &classe, &token_atual, &cont_linha); //Identifica o par token-classe 

        if (char_lido != EOF) //Garantindo que não leu o fim de arquivo e não vai gerar um token-classe repetido
            saida_lexico(output, token_atual, classe); //Escreve o par token-classe no arquivo de saída
        else
            break;
    }

    free(classe);
    free(token_atual);

    fclose(output);
    fclose(programa);

    return 0;
}

//------------------------------ Sintático -----------------------------------
int saida_sintatico(FILE *arquivo, char *msg){
    if (msg != NULL){
        fputs(msg, arquivo);
        fputs("\n", arquivo);
        return 1; //Indica que houve algum erro
    }
    return 0;
}

int leitura_arquivo_sintatico(const char *nome_arquivo){
    const char *nome_programa = nome_arquivo;
    const char *nome_output = "output.txt";
    remove(nome_output);

    //Verificando a abertura adequada do arquivo do código e a criação do de saída 
    FILE *programa = fopen(nome_programa, "r");
    if (programa == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    FILE *output = fopen(nome_output, "w+");
    if (output == NULL) {
        perror("Erro ao abrir o arquivo saída");
        return -1;
    }

    ASD(programa, output); //Fazendo a análise sintática descendente preditiva recursiva 

    //Verificando se foi escrito algo no arquivo de saída - caso não tenha sido, compilação foi um sucesso
    if (fgetc(output) == EOF){ //Não leu nada - compilação foi um sucesso
        saida_sintatico(output, "Compilação foi um sucesso");
    }

    fclose(output);
    fclose(programa);

    return 0;
}
