#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sintatico.h"
#include "lexico.h"

// Implementação dos procedimentos sintáticos (FALTA ADICIONAR TRATAMENTO DOS POSSÍVEIS ERROS)
void ASD(FILE *programa){
    //Declaração das variáveis que serão passadas como parâmetro para a tokerização
    char char_lido;
    char *classe =  calloc(30, sizeof(char*));
    char *token_atual = calloc(100, sizeof(char*));
    
    char_lido = fgetc(programa);
    identifica_token(&char_lido, programa, &classe, &token_atual); //Lendo o token inicial do programa

    Programa(&char_lido, programa, &classe, &token_atual);
    if (char_lido != EOF){
        printf("Erro - não chegou ao fim de arquivo\n");
    } 
    else{
        printf("Sucesso\n");
    }

    // Desalocação da memória alocada 
    free(classe);
    free(token_atual);
}

void Programa(char *char_lido, FILE *programa, char **classe, char **token_atual){
    // Esta função chama constante, variavel, procedimento e comando
    Constante(char_lido, programa, classe, token_atual);
    /*Variavel(char_lido, programa, classe, token_atual);
    Procedimento(char_lido, programa, classe, token_atual);
    Comando(char_lido, programa, classe, token_atual);*/

    identifica_token(char_lido, programa, classe, token_atual);
    if(!strcmp(*classe, "SIMB_PONTO")) { // Tudo certo, finaliza o programa
        // Precisamos tratar dos erros que ocorrem se eu colocar . finalizando o programa
        //mas continuar escrevendo alguma coisa 
        
        printf("Finalizando o programa...\n");
        return; 
    }
    identifica_token(char_lido, programa, classe, token_atual); //Consumindo o EOF
}


void Constante(char *char_lido, FILE *programa, char **classe, char **token_atual){
    if (!strcmp(*classe, "CONST")){
        while (1){
            identifica_token(char_lido, programa, classe, token_atual);
            if (!strcmp(*classe, "TK_ID")){
                identifica_token(char_lido, programa, classe, token_atual);
                if (!strcmp(*classe, "SIMB_IGUAL_IGUAL")){
                    identifica_token(char_lido, programa, classe, token_atual);
                    if (!strcmp(*classe, "TK_NUM_INT")){
                        identifica_token(char_lido, programa, classe, token_atual);
                        if (strcmp(*classe, "SIMB_VIRGULA")){ //Caso seja diferente de SIMB_VIRGULA, sai do loop e vai buscar o ;
                            break;
                        }
                    }
                }
            }
        }
        if (!strcmp(*classe, "SIMB_PONT_VIRG")){
            printf("Constante Sucesso!\n");
        }
    }
}

void Variavel(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Procedimento(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Comando(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Expressao(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Fator(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Mais_Fator(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Condicao(char *char_lido, FILE *programa, char **classe, char **token_atual);