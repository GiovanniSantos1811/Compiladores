#include <stdio.h>
#include "lexico.h"
#include "hash.h"
#include <string.h>

int matriz_transicao[NUM_ESTADOS][NUM_SIMBOLOS+2] = { // +2 para considerar uma coluna para Letras e uma para Dígitos
    // Estado 0
    {4, 1, 6, 10, 8, 9, 11, 15, 18, 19, 21, 20, 22, 24, 0, 0, 0, 0, 26, 0},
    
    // Estado 1
    {2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    
    // Estado 2
    {ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO,
     ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO,
     ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO,
     ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO,
     ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO,
     ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO,
     ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO},
    
    // Estado 3
    {TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT,
     TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT,
     TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT,
     TK_NUM_INT, TK_NUM_INT},
    
    // Estado 4
    {4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
    
    // Estado 5
    {TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID,
     TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID},
    
    // Estado 6
    {25, 25, 25, 7, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25},
    
    // Estado 7
    {TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO,
     TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO,
     TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO,
     TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO},
    
    // Estado 8
    {SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA,
     SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA,
     SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, 
     SIMB_SOMA, SIMB_SOMA},
    
    // Estado 9
    {SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB,
     SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB,
     SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB,
     SIMB_SUB, SIMB_SUB},

    // Estado 10
    {SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL,
     SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL,
     SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL,
     SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL,
     SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL},

    // Estado 11
    {12, 12, 12, 14, 12, 12, 12, 13, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12},

    // Estado 12
    {SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR,
     SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR,
     SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR,
     SIMB_MENOR, SIMB_MENOR},

    // Estado 13
    {SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR,
     SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR,
     SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR,
     SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR,
     SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR},

    // Estado 14
    {SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL,
     SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL,
     SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL,
     SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL,
     SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL},

    // Estado 15
    {16, 16, 16, 17, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16},

    // Estado 16
    {SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR,
     SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR,
     SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR,
     SIMB_MAIOR, SIMB_MAIOR},

    // Estado 17
    {SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL,
     SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL,
     SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL,
     SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL,
     SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL},

    // Estado 18
    {SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG,
     SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG,
     SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG,
     SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG},

    // Estado 19
    {SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA,
     SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA,
     SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA,
     SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA},

    // Estado 20
    {SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P,
     SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P,
     SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P,
     SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P},

    // Estado 21
    {SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P,
     SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P,
     SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P,
     SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P},

    // Estado 22
    {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 22, 22, 22, 22, 22, 22},

    // Estado 23
    {COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO,
     COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO,
     COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, 
     COMENTARIO, COMENTARIO},

    // Estado 24
    {ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO,
     ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO,
     ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO,
     ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO,
     ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO,
     ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO,
     ERRO_IDENT_MAL_FORMADO, ERRO_IDENT_MAL_FORMADO},

    // Estado 25
    {ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO},

    // Estado 26
    {SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO,
     SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO,
     SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO,
     SIMB_PONTO, SIMB_PONTO}
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
    '(', ')', '{', '}', '\'', '\t', '\n', ' ', '.', EOF
};

// Vetor com os estados finais, inseridos em ordem crescente (facilita a busca)
int estados_finais[QTD_ESTADOS_FINAIS] = {2, 3, 5, 7, 8, 9, 10, 12, 13, 14, 16, 17, 18, 19, 
20, 21, 23, 24, 25, 26};

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
    return -1; // Caractere não encontrado
}


// Função de transição de estado
int transicao(char caractere, int estado_atual){
    int coluna_char;
    
    coluna_char = encontrarID(caractere);

    // Vamos testar o id_char para verificar que o caractere existe no alfabeto do analisador léxico
    if(coluna_char < 0) {
        // Significa que o caractere não foi encontrado, então é estado 24 (erro genérico)
        return matriz_transicao[24][0]; // Coluna é indiferente
    }
    
    //printf("Coluna: %d\n", coluna_char);
    //printf("estado: %d\n", matriz_transicao[estado_atual][coluna_char]);
    int aux = matriz_transicao[estado_atual][coluna_char]; //Determinando o estado atingido após a transição
    if (matriz_transicao[aux][0] < 0) //Já chegamos em um estado final
        return matriz_transicao[aux][0];

    return aux;
}

// Função que identifica um token e sua classe
void identifica_token(char *char_lido, FILE *programa, char **classe, char **token_atual){
    // Variáveis locais que auxiliarão no processo
    int estado_atual = 0, cont = 0;
    char token[100];
    
    // Processo de identificação
    while (1){ //Realizando a leitura até chegar em um estado final -> identificação completa
        estado_atual = transicao(*char_lido, estado_atual);

        if (estado_atual == 0){ //Estado inicial
            *char_lido = fgetc(programa);
        }
        else if (estado_atual > 0) { //Estado intermediário
            token[cont++] = *char_lido;
            *char_lido = fgetc(programa);
        }
        else { //Estado final
            if (cont > 0){ //Chegou em um estado final passando por pelo menos um estado intermediário
                if (token[0] == ':'){ //Garantindo que vá incluir o = no símbolo de atribuição depois do caractere :
                    token[cont++] = *char_lido;
                    *char_lido = fgetc(programa); //Garantindo que não vá ler o caractere : duas vezes
                }
                token[cont] = '\0';

                //PRECISA VERIFICAR NA TABELA HASH SE É PALAVRA RESERVADA OU NÃO
                strcpy(*classe, "TESTE1"); //Passando a classe desse token por referência
                
            }
            else{ //Armazenando vírgulas, pontos, etc. (não tem estado intermediário, vai direto do inicial pro final)
                token[0] = *char_lido;
                token[1] = '\0';
                *char_lido = fgetc(programa); //Garantindo que não fique fazendo transição com caractere repetido

                strcpy(*classe, "TESTE2"); //Passando a classe desse token por referência
                
                //SÓ VERIFICAR A QUAL CLASSE PERTENCE ANTES DE ESCREVER NO ARQUIVO (DÁ PRA MONTAR UM VETOR DE CORRESPONDÊNCIA COM OS DEFINES LÁ PRA VERIFICAR ISSO)
            }
            //printf("Estado: %d, token: %s\n", estado_atual, token);
            //Como chegou em um estado final, a identificação desse token está completa
            strcpy(*token_atual, token); //Passando o token atual por referência
            
            break; //Parando a identificação
        }
    }
}

//-------------------- Tabela Hash ---------------
void preenche_hash(){
    inserir("CONST");
    inserir("VAR");
    inserir("PROCEDURE");
    inserir("CALL");
    inserir("BEGIN");
    inserir("END");
    inserir("IF");
    inserir("THEN");
    inserir("WHILE");
    inserir("DO");
    inserir("ODD");
}