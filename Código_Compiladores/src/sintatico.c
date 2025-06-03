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

// void Bloco(char *char_lido, FILE *programa, char **classe, char **token_atual){
//     Constante(char_lido, programa, classe, token_atual);
//     identifica_token(char_lido, programa, classe, token_atual);
//     Variavel(char_lido, programa, classe, token_atual);
//     identifica_token(char_lido, programa, classe, token_atual);
//     Procedimento(char_lido, programa, classe, token_atual);
//     /*identifica_token(char_lido, programa, classe, token_atual);
//     Comando(char_lido, programa, classe, token_atual);*/
// }

void Programa(char *char_lido, FILE *programa, char **classe, char **token_atual){
    // Esta função chama constante, variavel, procedimento e comando
    Constante(char_lido, programa, classe, token_atual);
    identifica_token(char_lido, programa, classe, token_atual);
    Variavel(char_lido, programa, classe, token_atual);
    identifica_token(char_lido, programa, classe, token_atual);
    Procedimento(char_lido, programa, classe, token_atual);
    identifica_token(char_lido, programa, classe, token_atual);
    Comando(char_lido, programa, classe, token_atual);

    identifica_token(char_lido, programa, classe, token_atual);
    if(!strcmp(*classe, "SIMB_PONTO")) { // Tudo certo, finaliza o programa
        // Precisamos tratar dos erros que ocorrem se eu colocar . finalizando o programa
        //mas continuar escrevendo alguma coisa 
        
        printf("Finalizando o programa...\n");
        return; 
    }
    else{
        printf("Erro sintático - programa foi finalizado sem .\n");
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

void Variavel(char *char_lido, FILE *programa, char **classe, char **token_atual){
    if (!strcmp(*classe, "VAR")){
        while (1){
            identifica_token(char_lido, programa, classe, token_atual);
            if (!strcmp(*classe, "TK_ID")){
                identifica_token(char_lido, programa, classe, token_atual);
                if (strcmp(*classe, "SIMB_VIRGULA")){ //Caso seja diferente de SIMB_VIRGULA, sai do loop e vai buscar o ;
                    break;
                }
            }
        }
        if (!strcmp(*classe, "SIMB_PONT_VIRG")){
            printf("Variável Sucesso!\n");
        }
    }
}

void Procedimento(char *char_lido, FILE *programa, char **classe, char **token_atual){
    if (!strcmp(*classe, "PROCEDURE")){
        identifica_token(char_lido, programa, classe, token_atual);
        if (!strcmp(*classe, "TK_ID")){
            identifica_token(char_lido, programa, classe, token_atual);
            if (!strcmp(*classe, "SIMB_PONT_VIRG")){
                Bloco(char_lido, programa, classe, token_atual);
                identifica_token(char_lido, programa, classe, token_atual);
                if (!strcmp(*classe, "SIMB_PONT_VIRG")){
                    printf("Procedimento Sucesso!\n");
                }
            }
        }
    }
}

void Comando(char *char_lido, FILE *programa, char **classe, char **token_atual){
    if (!strcmp(*classe, "TK_ID")){
        identifica_token(char_lido, programa, classe, token_atual);
        if (!strcmp(*classe, "TK_ATRIBUICAO")){
            identifica_token(char_lido, programa, classe, token_atual);
            Expressao(char_lido, programa, classe, token_atual);
            printf("Comando Sucesso! - Atribuição\n");
        }
    }
    else if (!strcmp(*classe, "CALL")){
        identifica_token(char_lido, programa, classe, token_atual);
        if (!strcmp(*classe, "TK_ID")){
            printf("Comando Sucesso! - CALL Procedure\n");
        }
    }
    else if (!strcmp(*classe, "BEGIN")){
        while (1){
            identifica_token(char_lido, programa, classe, token_atual);
            Comando(char_lido, programa, classe, token_atual);
            identifica_token(char_lido, programa, classe, token_atual);
            if (strcmp(*classe, "SIMB_PONT_VIRG")){ //Caso seja diferente de ;, encerra o ciclo e busca END
                break;
            }
        }
        if (!strcmp(*classe, "END")){
            printf("Comando Sucesso! - BEGIN ... END\n");
        }

    }
    else if (!strcmp(*classe, "IF")){
        identifica_token(char_lido, programa, classe, token_atual);
        Condicao(char_lido, programa, classe, token_atual);
        identifica_token(char_lido, programa, classe, token_atual);
        if (!strcmp(*classe, "THEN")){
            identifica_token(char_lido, programa, classe, token_atual);
            Comando(char_lido, programa, classe, token_atual);
            printf("Comando Sucesso! - IF\n");
        }
    }
    else if (!strcmp(*classe, "WHILE")){
        identifica_token(char_lido, programa, classe, token_atual);
        if (!strcmp(*classe, "WHILE")){
            identifica_token(char_lido, programa, classe, token_atual);
            Condicao(char_lido, programa, classe, token_atual);
            identifica_token(char_lido, programa, classe, token_atual);
            if (!strcmp(*classe, "DO")){
                identifica_token(char_lido, programa, classe, token_atual);
                Comando(char_lido, programa, classe, token_atual);
                printf("Comando Sucesso! - WHILE\n");
            }
        }
    }
}

void Expressao(char *char_lido, FILE *programa, char **classe, char **token_atual){
    if (!strcmp(*classe, "SIMB_SOMA") || !strcmp(*classe, "SIMB_SUB") || !strcmp(*classe, "PRIMEIRO DE FATOR")){ //INSERIR PRIMEIRO DE FATOR
        while (1){
            identifica_token(char_lido, programa, classe, token_atual);
            Fator(char_lido, programa, classe, token_atual);
            identifica_token(char_lido, programa, classe, token_atual);
            Mais_Fator(char_lido, programa, classe, token_atual);
            identifica_token(char_lido, programa, classe, token_atual);
            if (strcmp(*classe, "SIMB_SOMA") || strcmp(*classe, "SIMB_SUB")){ //Sem + ou -, encerasse o ciclo
                break;
            }
        }
        printf("Expressao Sucesso!\n");
    }
}

void Fator(char *char_lido, FILE *programa, char **classe, char **token_atual){
    if (!strcmp(*classe, "TK_ID")){
        printf("Fator Sucesso! - ident\n");
    }
    else if (!strcmp(*classe, "TK_NUM_INT")){
        printf("Fator Sucesso! - numero\n");
    }
    else if (!strcmp(*classe, "TK_ABRE_P")){
        identifica_token(char_lido, programa, classe, token_atual);
        Expressao(char_lido, programa, classe, token_atual);
        identifica_token(char_lido, programa, classe, token_atual);
        if (!strcmp(*classe, "TK_FECHA_P")){
            printf("Fator Sucesso! - parenteses\n");
        }
    }
}

void Mais_Fator(char *char_lido, FILE *programa, char **classe, char **token_atual){
    while (!strcmp(*classe, "SIMB_MULTIPLIC") || !strcmp(*classe, "SIMB_DIV")){
        identifica_token(char_lido, programa, classe, token_atual);
        Fator(char_lido, programa, classe, token_atual);
        identifica_token(char_lido, programa, classe, token_atual);
    }
    printf("Mais Fator Sucesso!\n");
}

void Condicao(char *char_lido, FILE *programa, char **classe, char **token_atual){
    if (!strcmp(*classe, "ODD")){
        identifica_token(char_lido, programa, classe, token_atual);
        Expressao(char_lido, programa, classe, token_atual);
    }
    else if (!strcmp(*classe, "PRIMEIRO DE EXPRESSÃO")){ //INSERIR PRIMEIRO DE EXPRESSÃO!
        identifica_token(char_lido, programa, classe, token_atual);
        Expressao(char_lido, programa, classe, token_atual);

        identifica_token(char_lido, programa, classe, token_atual);
        if (!strcmp(*classe, "SIMB_IGUAL_IGUAL") || !strcmp(*classe, "SIMB_MENOR_MAIOR") || !strcmp(*classe, "SIMB_MENOR_IGUAL") || !strcmp(*classe, "SIMB_MAIOR") || !strcmp(*classe, "SIMB_MENOR") || !strcmp(*classe, "SIMB_MAIOR_IGUAL")){
            identifica_token(char_lido, programa, classe, token_atual);
            Expressao(char_lido, programa, classe, token_atual);
        }
    }
}