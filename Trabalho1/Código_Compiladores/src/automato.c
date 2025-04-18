#include<stdio.h>
#include "automato.h"

int matriz_transicao[NUM_ESTADOS][NUM_SIMBOLOS+2] = { // +2 para considerar uma coluna para Letras e uma para Dígitos
    // Estado 0
    {4, 1, 6, 10, 8, 9, 11, 15, 18, 19, 21, 20, 22, 24, 0, 0, 0, 0},
    
    // Estado 1
    {2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    
    // Estado 2
    {ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO,
     ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO,
     ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO,
     ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO,
     ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO,
     ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO},
    
    // Estado 3
    {TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT,
     TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT,
     TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT},
    
    // Estado 4
    {4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
    
    // Estado 5
    {TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID,
     TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID},
    
    // Estado 6
    {26, 26, 26, 7, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26, 26},
    
    // Estado 7
    {TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO,
     TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO,
     TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO,
     TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO},
    
    // Estado 8
    {SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA,
     SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA,
     SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA},
    
    // Estado 9
    {SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB,
     SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB,
     SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB},

    // Estado 10
    {SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL,
     SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL,
     SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL,
     SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL,
     SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL},

    // Estado 11
    {12, 12, 12, 14, 12, 12, 12, 13, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12},

    // Estado 12
    {SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR,
     SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR,
     SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR},

    // Estado 13
    {SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR,
     SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR,
     SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR,
     SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR,
     SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR},

    // Estado 14
    {SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL,
     SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL,
     SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL,
     SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL,
     SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL},

    // Estado 15
    {16, 16, 16, 17, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16},

    // Estado 16
    {SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR,
     SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR,
     SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR},

    // Estado 17
    {SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL,
     SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL,
     SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL,
     SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL,
     SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL},

    // Estado 18
    {SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG,
     SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG,
     SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG,
     SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG},

    // Estado 19
    {SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA,
     SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA,
     SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA,
     SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA},

    // Estado 20
    {SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P,
     SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P,
     SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P,
     SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P},

    // Estado 21
    {SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P,
     SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P,
     SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P,
     SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P},

    // Estado 22
    {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 22, 22, 22, 22},

    // Estado 23
    {COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO,
     COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO,
     COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO},

    // Estado 24
    {ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO,
     ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO,
     ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO,
     ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO,
     ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO,
     ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO},

    // Estado 25
    {ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO}
};

char simbolos[TAM_VETOR_CARACTERES] = { 
    // ADD: .

    // Letras minusculas (26 letras)
    'a','b','c','d','e','f','g','h','i','j','k','l','m',
    'n','o','p','q','r','s','t','u','v','w','x','y','z',
    
    // Letras maiusculas (26 letras)
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
    
    // Digitos (10 dígitos)
    '0','1','2','3','4','5','6','7','8','9',
    
    // Símbolos especiais (Inicia no ID 62)
    ':', '=', '+', '-', '<', '>', ';', ',', 
    '(', ')', '{', '}', '\'', '\t', '\n', ' '
};

int atribuicao_ID_equivalente(int ID) {
    // Atribuição do ID equivalente na tabela de transição (transformar caractere em numero VÁLIDO da coluna)
    if(ID >= 0 && ID < 52) { // Significa que é uma letra do alfabeto, seja maiúscula ou minúscula
        return 0; // Recebe o ID 0, pois a tabela de transição tem a coluna 0 como LETRAS
    }
    else if(ID >= 52 && ID < 62) { // Significa que é um dígito
        return 1; // Recebe ID 1, equivalente a coluna 1 da tabela de transições
    }
    else if(ID >= 62) { //Significa que é um símbolo
        return ID - 60; // O símbolo começa no ID 2, por isso subtraímos 60.
    }
    return ID;
}

// Função para encontrar o ID do vetor com relação aos caracteres do vetor
int encontrarID(char c) {
    int ID;
    for(int i = 0; i < TAM_VETOR_CARACTERES; i++) {
        if(simbolos[i] == c) {
            ID = atribuicao_ID_equivalente(i); // Retorna o índice do caractere encontrado
            return ID; 
        }
    }
    // ID = atribuicao_ID_equivalente(-19); // Caractere não encontrado
    // return ID; 
    return -19; // Caractere não encontrado
}


// Função de transição de estado
int transicao(char caractere, int estado_atual){
    int id_char = encontrarID(caractere);

    //printf("Coluna: %d\n", id_char);
    //printf("estado: %d\n", matriz_transicao[estado_atual][id_char]);

    int aux = matriz_transicao[estado_atual][id_char]; //Determinando o estado atingido após a transição
    if (matriz_transicao[aux][0] < 0) //Já chegamos em um estado final
        return matriz_transicao[aux][0];

    return aux;

    // return matriz_transicao[estado_atual][id_char]; //Determinando o estado atingido após a transição
}