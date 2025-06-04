#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sintatico.h"
#include "lexico.h"
#include "arquivo.h"

//Primeiros e Seguidores
const char *PRIMEIRO_PROGRAMA[4] = {"CONST", "VAR", "PROCEDURE", ""};
const char *PRIMEIRO_CONSTANTE[2] = {"CONST", ""};
const char *PRIMEIRO_MAIS_CONST[2] = {"SIMB_VIRGULA", ""};
const char *PRIMEIRO_VARIAVEL[2] = {"VAR", ""};

const char *SEGUIDOR_PROGRAMA[1] = {""};
const char *SEGUIDOR_BLOCO[2] = {"SIMB_PONTO", "SIMB_PONT_VIRG"};
const char *SEGUIDOR_DECLARACAO[8] = {"TK_ID", "CALL", "BEGIN", "IF", "WHILE", "SIMB_PONTO", "SIMB_PONT_VIRG", ""};
const char *SEGUIDOR_CONSTANTE[10] = {"VAR", "PROCEDURE", "TK_ID", "CALL", "BEGIN", "IF", "WHILE", "SIMB_PONTO", "SIMB_PONT_VIRG", ""};
const char *SEGUIDOR_MAIS_CONST[1] = {"SIMB_PONT_VIRG"};
const char *SEGUIDOR_VARIAVEL[7] = {"PROCEDURE", "TK_ID", "CALL", "BEGIN", "IF", "WHILE", ""};

const char *PRIMEIRO_MAIS_VAR[2] = {"SIMB_VIRGULA", ""};
const char *PRIMEIRO_PROCEDIMENTO[2] = {"PROCEDURE", ""};
const char *PRIMEIRO_COMANDO[6] = {"TK_ID", "CALL", "BEGIN", "IF", "WHILE", ""};
const char *PRIMEIRO_MAIS_CMD[2] = {"SIMB_PONT_VIRG", ""};
const char *PRIMEIRO_EXPRESSAO[6] = {"SIMB_SUB", "SIMB_SOMA", "TK_ID", "TK_NUM_INT", "SIMB_ABRE_P", ""};
const char *PRIMEIRO_OPERADOR_UNARIO[3] = {"SIMB_SUB", "SIMB_SOMA", ""};

const char *SEGUIDOR_MAIS_VAR[1] = {"SIMB_PONT_VIRG"};
const char *SEGUIDOR_PROCEDIMENTO[8] = {"TK_ID", "CALL", "BEGIN", "IF", "WHILE", "SIMB_PONTO", "SIMB_PONT_VIRG", ""};
const char *SEGUIDOR_COMANDO[4] = {"SIMB_PONTO", "SIMB_PONT_VIRG", "END", ""};
const char *SEGUIDOR_MAIS_CMD[1] = {"END"};
const char *SEGUIDOR_EXPRESSAO[12] = {"SIMB_PONTO", "SIMB_PONT_VIRG", "SIMB_FECHA_P", "THEN", "DO", "TK_ATRIBUICAO", "SIMB_MENOR_MAIOR", "SIMB_MENOR", "SIMB_MENOR_IGUAL", "SIMB_MAIOR", "SIMB_MAIOR_IGUAL", ""};
const char *SEGUIDOR_OPERADOR_UNARIO[3] = {"TK_ID", "TK_NUM_INT", "SIMB_ABRE_P"};

int cont_linha = 1; //armazena a linha atual que está sendo lida do programa

// Implementação dos procedimentos sintáticos (FALTA ADICIONAR TRATAMENTO DOS POSSÍVEIS ERROS)
void ASD(FILE *programa, FILE *output){
    //Declaração das variáveis que serão passadas como parâmetro para a tokerização
    char char_lido;
    char *classe =  calloc(30, sizeof(char*));
    char *token_atual = calloc(100, sizeof(char*));
    
    char_lido = fgetc(programa);
    saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha)); //Lendo o token inicial do programa

    Programa(&char_lido, programa, output, &classe, &token_atual);
    if (char_lido != EOF){
        printf("Erro - não chegou ao fim de arquivo\n");
    } 
    else{
        printf("Sucesso - EOF identificado\n");
    }

    // Desalocação da memória alocada 
    free(classe);
    free(token_atual);
}

void Programa(char *char_lido, FILE *programa, FILE *output, char **classe, char **token_atual){
    // Esta função chama constante, variavel, procedimento e comando
    Constante(char_lido, programa, output, classe, token_atual);
    Variavel(char_lido, programa, output, classe, token_atual);
    Procedimento(char_lido, programa, output, classe, token_atual);
    Comando(char_lido, programa, output, classe, token_atual);

    saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
    if(!strcmp(*classe, "SIMB_PONTO")) { // Tudo certo, finaliza o programa
        // Precisamos tratar dos erros que ocorrem se eu colocar . finalizando o programa
        //mas continuar escrevendo alguma coisa 
        
        printf("Finalizando o programa...\n");
        return; 
    }
    else{
        printf("Erro sintático - programa foi finalizado sem .\n");
    }
    saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha)); //Consumindo o EOF
}


void Constante(char *char_lido, FILE *programa, FILE *output, char **classe, char **token_atual){
    if (!strcmp(*classe, "CONST")){
        while (1){
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            if (!strcmp(*classe, "TK_ID")){
                saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
                if (!strcmp(*classe, "SIMB_IGUAL_IGUAL")){
                    saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
                    if (!strcmp(*classe, "TK_NUM_INT")){
                        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
                        if (strcmp(*classe, "SIMB_VIRGULA")){ //Caso seja diferente de SIMB_VIRGULA, sai do loop e vai buscar o ;
                            break;
                        }
                    }
                }
            }
        }
        if (!strcmp(*classe, "SIMB_PONT_VIRG")){
            printf("Constante Sucesso!\n");
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        }
    }
}

void Variavel(char *char_lido, FILE *programa, FILE *output, char **classe, char **token_atual){
    if (!strcmp(*classe, "VAR")){
        while (1){
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            if (!strcmp(*classe, "TK_ID")){
                saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
                if (strcmp(*classe, "SIMB_VIRGULA")){ //Caso seja diferente de SIMB_VIRGULA, sai do loop e vai buscar o ;
                    break;
                }
            }
        }
        if (!strcmp(*classe, "SIMB_PONT_VIRG")){
            printf("Variável Sucesso!\n");
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        }
    }
}

void Procedimento(char *char_lido, FILE *programa, FILE *output, char **classe, char **token_atual){
    if (!strcmp(*classe, "PROCEDURE")){
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        if (!strcmp(*classe, "TK_ID")){
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            if (!strcmp(*classe, "SIMB_PONT_VIRG")){
                saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));

                //Chamando Bloco
                Constante(char_lido, programa, output, classe, token_atual);
                saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
                Variavel(char_lido, programa, output, classe, token_atual);
                saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
                Procedimento(char_lido, programa, output, classe, token_atual);
                saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
                Comando(char_lido, programa, output, classe, token_atual);

                saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
                if (!strcmp(*classe, "SIMB_PONT_VIRG")){
                    printf("Procedimento Sucesso!\n");
                    saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
                }
            }
        }
    }
}

void Comando(char *char_lido, FILE *programa, FILE *output, char **classe, char **token_atual){
    if (!strcmp(*classe, "TK_ID")){
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        if (!strcmp(*classe, "TK_ATRIBUICAO")){
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            Expressao(char_lido, programa, output, classe, token_atual);
            printf("Comando Sucesso! - Atribuição\n");
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        }
    }
    else if (!strcmp(*classe, "CALL")){
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        if (!strcmp(*classe, "TK_ID")){
            printf("Comando Sucesso! - CALL Procedure\n");
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        }
    }
    else if (!strcmp(*classe, "BEGIN")){
        while (1){
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            Comando(char_lido, programa, output, classe, token_atual);
            if (strcmp(*classe, "SIMB_PONT_VIRG")){ //Caso seja diferente de ;, encerra o ciclo e busca END
                break;
            }
        }
        if (!strcmp(*classe, "END")){
            printf("Comando Sucesso! - BEGIN ... END\n");
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        }

    }
    else if (!strcmp(*classe, "IF")){
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        Condicao(char_lido, programa, output, classe, token_atual);
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        if (!strcmp(*classe, "THEN")){
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            Comando(char_lido, programa, output, classe, token_atual);
            printf("Comando Sucesso! - IF\n");
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        }
    }
    else if (!strcmp(*classe, "WHILE")){
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        if (!strcmp(*classe, "WHILE")){
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            Condicao(char_lido, programa, output, classe, token_atual);
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            if (!strcmp(*classe, "DO")){
                saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
                Comando(char_lido, programa, output, classe, token_atual);
                printf("Comando Sucesso! - WHILE\n");
                saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            }
        }
    }
}

void Expressao(char *char_lido, FILE *programa, FILE *output, char **classe, char **token_atual){
    if (!strcmp(*classe, "SIMB_SOMA") || !strcmp(*classe, "SIMB_SUB") || !strcmp(*classe, "PRIMEIRO DE FATOR")){ //INSERIR PRIMEIRO DE FATOR
        while (1){
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            Fator(char_lido, programa, output, classe, token_atual);
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            Mais_Fator(char_lido, programa, output, classe, token_atual);
            if (strcmp(*classe, "SIMB_SOMA") || strcmp(*classe, "SIMB_SUB")){ //Sem + ou -, encerasse o ciclo
                break;
            }
        }
        printf("Expressao Sucesso!\n");
    }
}

void Fator(char *char_lido, FILE *programa, FILE *output, char **classe, char **token_atual){
    if (!strcmp(*classe, "TK_ID")){
        printf("Fator Sucesso! - ident\n");
    }
    else if (!strcmp(*classe, "TK_NUM_INT")){
        printf("Fator Sucesso! - numero\n");
    }
    else if (!strcmp(*classe, "TK_ABRE_P")){
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        Expressao(char_lido, programa, output, classe, token_atual);
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        if (!strcmp(*classe, "TK_FECHA_P")){
            printf("Fator Sucesso! - parenteses\n");
        }
    }
}

void Mais_Fator(char *char_lido, FILE *programa, FILE *output, char **classe, char **token_atual){
    while (!strcmp(*classe, "SIMB_MULTIPLIC") || !strcmp(*classe, "SIMB_DIV")){
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        Fator(char_lido, programa, output, classe, token_atual);
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
    }
    printf("Mais Fator Sucesso!\n");
    saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
}

void Condicao(char *char_lido, FILE *programa, FILE *output, char **classe, char **token_atual){
    if (!strcmp(*classe, "ODD")){
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        Expressao(char_lido, programa, output, classe, token_atual);
    }
    else if (!strcmp(*classe, "PRIMEIRO DE EXPRESSÃO")){ //INSERIR PRIMEIRO DE EXPRESSÃO!
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        Expressao(char_lido, programa, output, classe, token_atual);

        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        if (!strcmp(*classe, "SIMB_IGUAL_IGUAL") || !strcmp(*classe, "SIMB_MENOR_MAIOR") || !strcmp(*classe, "SIMB_MENOR_IGUAL") || !strcmp(*classe, "SIMB_MAIOR") || !strcmp(*classe, "SIMB_MENOR") || !strcmp(*classe, "SIMB_MAIOR_IGUAL")){
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            Expressao(char_lido, programa, output, classe, token_atual);
        }
    }
}