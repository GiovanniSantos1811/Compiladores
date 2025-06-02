#include <stdlib.h>
#include "sintatico.h"
#include "lexico.h"
#include <stdio.h>

// Implementação dos procedimentos sintáticos
void ASD(FILE *programa){
    //Declaração das variáveis que serão passadas como parâmetro para a tokerização
    char char_lido;
    char *classe =  calloc(30, sizeof(char*));
    char *token_atual = calloc(100, sizeof(char*));

    identifica_token(&char_lido, programa, &classe, &token_atual); //Lendo o token inicial do programa

    Programa(&char_lido, programa, &classe, &token_atual);

    if (char_lido != EOF){
        printf("Erro - não chegou ao fim de arquivo");
    } 
    else{
        printf("Sucesso");
    }

    // Desalocação da memória alocada 
    free(classe);
    free(token_atual);
}
// void identifica_token(char *char_lido, FILE *programa, char **classe, char **token_atual){
// identifica_token(&char_lido, programa, &classe, &token_atual); //Identifica o par token-classe 

void Programa(char *char_lido, FILE *programa, char **classe, char **token_atual){
    // Esta função chama constante, variavel, procedimento e comando
    Constante(&char_lido, programa, &classe, &token_atual);
    Variavel(&char_lido, programa, &classe, &token_atual);
    Procedimento(&char_lido, programa, &classe, &token_atual);
    Comando(&char_lido, programa, &classe, &token_atual);

    identifica_token(&char_lido, programa, &classe, &token_atual);
    if(classe == SIMB_PONTO) { // Tudo certo, finaliza o programa
        // Precisamos tratar dos erros que ocorrem se eu colocar . finalizando o programa
        //mas continuar escrevendo alguma coisa 
        
        printf("Finalizando o programa...\n");
        return; 
    }
}


void Constante(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Variavel(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Procedimento(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Comando(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Expressao(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Fator(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Mais_Fator(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Condicao(char *char_lido, FILE *programa, char **classe, char **token_atual);