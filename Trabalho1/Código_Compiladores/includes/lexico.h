#ifndef AUTOMATO_H
#define AUTOMATO_H

#include <stdlib.h>

// Constantes
#define NUM_ESTADOS 30
#define NUM_SIMBOLOS 20 //20 simbolos (: = + - < > ; , ( ) { } ' \t \n espaço . * / EOF)
#define TAM_VETOR_CARACTERES 62+NUM_SIMBOLOS // 52 (a-zA-Z) letras + 10 dígitos + NUM_SIMBOLOS
#define QTD_ESTADOS_FINAIS 23 // Quantidade de estados finais

// Especificação dos estados finais
#define ERRO_NUMERO_MAL_FORMADO -1
#define TK_NUM_INT -2
#define TK_ID -3
#define TK_ATRIBUICAO -4
#define SIMB_SOMA -5
#define SIMB_SUB -6
#define SIMB_IGUAL_IGUAL -7
#define SIMB_MENOR -8
#define SIMB_MENOR_MAIOR -9
#define SIMB_MENOR_IGUAL -10
#define SIMB_MAIOR -11
#define SIMB_MAIOR_IGUAL -12
#define SIMB_PONT_VIRG -13
#define SIMB_VIRGULA -14
#define SIMB_FECHA_P -15
#define SIMB_ABRE_P -16
#define COMENTARIO -17
#define ERRO_ATRIB_MAL_FORMADO -18
#define SIMB_PONTO -19
#define SIMB_MULTIPLIC -20
#define SIMB_DIV -21
#define SIMB_NAO_IDENTIFICADO -22
#define ERRO_COMENT_MAL_FORMADO -23

// Matrizes e vetores
int matriz_transicao[NUM_ESTADOS][NUM_SIMBOLOS+3];
char simbolos[TAM_VETOR_CARACTERES];


// Funções
int atribuicao_ID_equivalente(int ID);
int encontrarID(char c);
int transicao(char caractere, int estado_atual); 

void identifica_token(char *char_lido, FILE *programa, char **classe, char **token_atual);

// Funções relativas ao hash
void preenche_hash(); //Preenche a tabela hash com as palavras reservadas


#endif