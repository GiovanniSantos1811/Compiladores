#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"
#include "hash.h"
#include <string.h>

int matriz_transicao[NUM_ESTADOS][NUM_SIMBOLOS+3] = { // +3 para considerar uma coluna para Letras, uma para Dígitos e uma para caracteres estrangeiros à linguagem
    // Estado 0
    {4, 1, 6, 10, 8, 9, 11, 15, 18, 19, 21, 20, 22, 29, 0, 0, 0, 0, 25, 26, 27, 0, 28},
    
    // Estado 1
    {2, 1, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
    
    // Estado 2
    {ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO,
     ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO, ERRO_NUMERO_MAL_FORMADO,
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
     TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT, TK_NUM_INT},
    
    // Estado 4
    {4, 4, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5},
    
    // Estado 5
    {TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID
     TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID, TK_ID},
    
    // Estado 6
    {24, 24, 24, 7, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24, 24},
    
    // Estado 7
    {TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO,
     TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO,
     TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO,
     TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO,
     TK_ATRIBUICAO, TK_ATRIBUICAO, TK_ATRIBUICAO},
    
    // Estado 8
    {SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA,
     SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA,
     SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, 
     SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA, SIMB_SOMA},
    
    // Estado 9
    {SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB,
     SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB,
     SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB,
     SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB, SIMB_SUB},

    // Estado 10
    {SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL,
     SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL,
     SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL,
     SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL,
     SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL,
     SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL, SIMB_IGUAL_IGUAL},

    // Estado 11
    {12, 12, 12, 14, 12, 12, 12, 13, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12},

    // Estado 12
    {SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR,
     SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR,
     SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR,
     SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR, SIMB_MENOR},

    // Estado 13
    {SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR,
     SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR,
     SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR,
     SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR,
     SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR,
     SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR, SIMB_MENOR_MAIOR},

    // Estado 14
    {SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL,
     SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL,
     SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL,
     SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL,
     SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL,
     SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL, SIMB_MENOR_IGUAL},

    // Estado 15
    {16, 16, 16, 17, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16},

    // Estado 16
    {SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR,
     SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR,
     SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR,
     SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR, SIMB_MAIOR},

    // Estado 17
    {SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL,
     SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL,
     SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL,
     SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL,
     SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL,
     SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL, SIMB_MAIOR_IGUAL},

    // Estado 18
    {SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG,
     SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG,
     SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG,
     SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG,
     SIMB_PONT_VIRG, SIMB_PONT_VIRG, SIMB_PONT_VIRG},

    // Estado 19
    {SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA,
     SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA,
     SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA,
     SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA,
     SIMB_VIRGULA, SIMB_VIRGULA, SIMB_VIRGULA},

    // Estado 20
    {SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P,
     SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P,
     SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P,
     SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P,
     SIMB_FECHA_P, SIMB_FECHA_P, SIMB_FECHA_P},

    // Estado 21
    {SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P,
     SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P,
     SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P,
     SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P,
     SIMB_ABRE_P, SIMB_ABRE_P, SIMB_ABRE_P},

    // Estado 22
    {22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 22, 23, 22, 22, 29, 22, 22, 22, 22, 29, 22},

    // Estado 23
    {COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO,
     COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO,
     COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, 
     COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO, COMENTARIO},

    // Estado 24
    {ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO,
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO, 
     ERRO_ATRIB_MAL_FORMADO, ERRO_ATRIB_MAL_FORMADO},

    // Estado 25
    {SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO,
     SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO,
     SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO,
     SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO, SIMB_PONTO},

    // Estado 26
    {SIMB_MULTIPLIC, SIMB_MULTIPLIC, SIMB_MULTIPLIC, SIMB_MULTIPLIC, SIMB_MULTIPLIC,
     SIMB_MULTIPLIC, SIMB_MULTIPLIC, SIMB_MULTIPLIC, SIMB_MULTIPLIC, SIMB_MULTIPLIC,
     SIMB_MULTIPLIC, SIMB_MULTIPLIC, SIMB_MULTIPLIC, SIMB_MULTIPLIC, SIMB_MULTIPLIC,
     SIMB_MULTIPLIC, SIMB_MULTIPLIC, SIMB_MULTIPLIC, SIMB_MULTIPLIC, SIMB_MULTIPLIC,
     SIMB_MULTIPLIC, SIMB_MULTIPLIC, SIMB_MULTIPLIC},

    // Estado 27
    {SIMB_DIV, SIMB_DIV, SIMB_DIV, SIMB_DIV, SIMB_DIV, SIMB_DIV,
     SIMB_DIV, SIMB_DIV, SIMB_DIV, SIMB_DIV, SIMB_DIV, SIMB_DIV,
     SIMB_DIV, SIMB_DIV, SIMB_DIV, SIMB_DIV, SIMB_DIV, SIMB_DIV,
     SIMB_DIV, SIMB_DIV, SIMB_DIV, SIMB_DIV, SIMB_DIV},
    
     // Estado 28
    {SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO,
     SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO,
     SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO,
     SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO, SIMB_NAO_IDENTIFICADO},

    // Estado 29
    {ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO,
     ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO,
     ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO,
     ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO,
     ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO, ERRO_COMENT_MAL_FORMADO}
};

char simbolos[TAM_VETOR_CARACTERES] = { 
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
    '(', ')', '{', '}', '\'', '\t', '\n', ' ', '.', '*', '/', EOF
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

    //Caso chegar nessa parte, significa que o caractere lido não pertence ao alfabeto da gramática
    return (NUM_SIMBOLOS+3)-1; //Última coluna da tabela de transições (não está mapeada no vetor de símbolos, já que o símbolo é estrangeiro)
}


// Função de transição de estado
int transicao(char caractere, int estado_atual){
    int coluna_char;
    
    coluna_char = encontrarID(caractere);
    
    int aux = matriz_transicao[estado_atual][coluna_char]; //Determinando o estado atingido após a transição
    if (matriz_transicao[aux][0] < 0) //Já chegamos em um estado final
        return matriz_transicao[aux][0];

    return aux;
}

//------------------- Identificação dos tokens --------------------
char *estados_finais[] = { // Vetor de strings para armazenar os estados finais
    "ERRO_NUMERO_MAL_FORMADO",
    "TK_NUM_INT",
    "TK_ID",
    "TK_ATRIBUICAO",
    "SIMB_SOMA",
    "SIMB_SUB",
    "SIMB_IGUAL_IGUAL",
    "SIMB_MENOR",
    "SIMB_MENOR_MAIOR",
    "SIMB_MENOR_IGUAL",
    "SIMB_MAIOR",
    "SIMB_MAIOR_IGUAL",
    "SIMB_PONT_VIRG",
    "SIMB_VIRGULA",
    "SIMB_FECHA_P",
    "SIMB_ABRE_P",
    "COMENTARIO",
    "ERRO_ATRIB_MAL_FORMADO",
    "SIMB_PONTO",
    "SIMB_MULTIPLIC",
    "SIMB_DIV",
    "SIMB_NAO_IDENTIFICADO", // Referente a um estado que não existe, isto é, o autômato não reconhece o caractere
    "ERRO_COMENT_MAL_FORMADO"
};

// Função que retorna a classe do token 
char *retorna_classe(int valor_estado_final) {
    int indice = (valor_estado_final * (-1)) - 1; 
    
    return estados_finais[indice];
}

// Função que identifica um token e sua classe
int identifica_token(char *char_lido, FILE *programa, char **classe, char **token_atual, int *cont_linha){
    // Variáveis locais que auxiliarão no processo
    int estado_atual = 0, cont = 0, indice_hash;
    char token[100];
    
    // Processo de identificação
    while (1){ //Realizando a leitura até chegar em um estado final -> identificação completa
        estado_atual = transicao(*char_lido, estado_atual);

        if (estado_atual == 0){ //Estado inicial
            if (*char_lido == EOF)
                break;
            if (*char_lido == '\n') //Atualizando a linha atual
                (*cont_linha)++;
            *char_lido = fgetc(programa);
        }
        else if (estado_atual > 0) { //Estado intermediário
            token[cont++] = *char_lido;
            *char_lido = fgetc(programa);
        }
        else { //Estado final
            if (cont > 0){ //Chegou em um estado final passando por pelo menos um estado intermediário
                //Análise dos tokens que são símbolos + erro de formação de número
                if ((token[0] == ':' && *char_lido == '=') || token[0] == '{' || (token[0] == '>' && *char_lido == '=') || (token[0] == '<' && (*char_lido == '>' || *char_lido == '=')) || estado_atual == -1){ 
                    token[cont++] = *char_lido;
                    if (*char_lido == '\n') //Atualizando a linha atual
                        (*cont_linha)++;
                    *char_lido = fgetc(programa); //Garantindo que não vá ler o caractere final duas vezes
                }
                token[cont] = '\0';

                //Determinação da classe
                indice_hash = buscar(token);
                if (indice_hash > 0) { //Significa que a palavra buscada na hash está lá, então é uma palavra reservada
                    strcpy(*classe, token);
                }
                else
                    strcpy(*classe, retorna_classe(estado_atual)); //Passando a classe desse token por referência
                //strcpy(*classe, "TESTE 1");
            }
            else{ //Armazenando vírgulas, pontos, etc. (não tem estado intermediário, vai direto do inicial pro final)
                token[0] = *char_lido;
                token[1] = '\0';
                *char_lido = fgetc(programa); //Garantindo que não fique fazendo transição com caractere repetido

                strcpy(*classe, retorna_classe(estado_atual)); //Passando a classe desse token por referência
                //strcpy(*classe, "TESTE 2");
            }
            //printf("Estado: %d, lexema: %s\n", estado_atual, token);
            if (token[cont-1] == '\n' || token[cont-1] == EOF){ //Token truncado para desconsiderar quebras de linhas indevidas no comentario ao escrever no output
                token[cont-1] = '\0';
            }

            //Como chegou em um estado final, a identificação desse token está completa
            strcpy(*token_atual, token); //Passando o token atual por referência
            //printf("Token: %s, Classe: %s\n", *token_atual, *classe);

            //Consumindo os comentários para não passar isso pro Sintático
            if (strcmp(*classe, "COMENTARIO")){ //Diferente de comentário, então sai da identificação já
                break; //Parando a identificação
            }
            estado_atual = 0;
            cont = 0;
            strcpy(*token_atual, "");
        }
    }

    return estado_atual;
}

char *obtem_token_e_erro(char *char_lido, FILE *programa, char **classe, char **token_atual, int *cont_linha){ //Utilizado pelo sintático
    int estado_final = identifica_token(char_lido, programa, classe, token_atual, cont_linha);
    //Vericando se o estado final atingido corresponde a um erro e gerando o log do erro léxico
    static char mensagem[256];
    if (estado_final == ERRO_COMENT_MAL_FORMADO){
        snprintf(mensagem, sizeof(mensagem), "Erro Léxico na linha %d: Comentário mal formado (%s) ...", *cont_linha, *token_atual);
        return mensagem;
    }
    if (estado_final == SIMB_NAO_IDENTIFICADO){
        snprintf(mensagem, sizeof(mensagem), "Erro Léxico na linha %d: Caractere inválido (%s) ...", *cont_linha, *token_atual);
        return mensagem;
    }
    if (estado_final == ERRO_ATRIB_MAL_FORMADO){
        snprintf(mensagem, sizeof(mensagem), "Erro Léxico na linha %d: Atribuição mal formada (%s), esperado (:=) ...", *cont_linha, *token_atual);
        return mensagem;
    }
    if (estado_final == ERRO_NUMERO_MAL_FORMADO){
        snprintf(mensagem, sizeof(mensagem), "Erro Léxico na linha %d: Número inteiro mal formado (%s) ...", *cont_linha, *token_atual);
        return mensagem;
    }

    return NULL; //Sem erros na tokerização
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