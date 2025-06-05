#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sintatico.h"
#include "lexico.h"
#include "arquivo.h"
#include <stdbool.h>

//Primeiros e Seguidores (Importante ressaltar que "" está sendo usado como caractere sentinela, assim, nesse caso, o lambda não está mapeado aqui)
char *PRIMEIRO_PROGRAMA[4] = {"CONST", "VAR", "PROCEDURE", ""};
char *PRIMEIRO_CONSTANTE[2] = {"CONST", ""};
char *PRIMEIRO_MAIS_CONST[2] = {"SIMB_VIRGULA", ""};
char *PRIMEIRO_VARIAVEL[2] = {"VAR", ""};
char *PRIMEIRO_MAIS_VAR[2] = {"SIMB_VIRGULA", ""};
char *PRIMEIRO_PROCEDIMENTO[2] = {"PROCEDURE", ""};
char *PRIMEIRO_COMANDO[6] = {"TK_ID", "CALL", "BEGIN", "IF", "WHILE", ""};
char *PRIMEIRO_MAIS_CMD[2] = {"SIMB_PONT_VIRG", ""};
char *PRIMEIRO_EXPRESSAO[6] = {"SIMB_SUB", "SIMB_SOMA", "TK_ID", "TK_NUM_INT", "SIMB_ABRE_P", ""};
char *PRIMEIRO_OPERADOR_UNARIO[3] = {"SIMB_SUB", "SIMB_SOMA", ""};
char *PRIMEIRO_TERMO[4] = {"TK_ID", "TK_NUM_INT", "SIMB_ABRE_P", ""};
char *PRIMEIRO_MAIS_TERMOS[3] = {"SIMB_SUB", "SIMB_SOMA", ""};
char *PRIMEIRO_FATOR[4] = {"TK_ID", "TK_NUM_INT", "SIMB_ABRE_P", ""};
char *PRIMEIRO_MAIS_FATORES[3] = {"SIMB_MULTIPLIC", "SIMB_DIV", ""};
char *PRIMEIRO_CONDICAO[4] = {"ODD", "SIMB_SUB", "SIMB_SOMA", ""};
char *PRIMEIRO_RELACIONAL[7] = {"SIMB_IGUAL_IGUAL", "SIMB_MENOR_MAIOR", "SIMB_MENOR", "SIMB_MENOR_IGUAL", "SIMB_MAIOR", "SIMB_MAIOR_IGUAL", ""};

char *SEGUIDOR_PROGRAMA[1] = {""};
char *SEGUIDOR_BLOCO[3] = {"SIMB_PONTO", "SIMB_PONT_VIRG", ""};
char *SEGUIDOR_DECLARACAO[8] = {"TK_ID", "CALL", "BEGIN", "IF", "WHILE", "SIMB_PONTO", "SIMB_PONT_VIRG", ""};
char *SEGUIDOR_CONSTANTE[10] = {"VAR", "PROCEDURE", "TK_ID", "CALL", "BEGIN", "IF", "WHILE", "SIMB_PONTO", "SIMB_PONT_VIRG", ""};
char *SEGUIDOR_MAIS_CONST[2] = {"SIMB_PONT_VIRG", ""};
char *SEGUIDOR_VARIAVEL[7] = {"PROCEDURE", "TK_ID", "CALL", "BEGIN", "IF", "WHILE", ""};
char *SEGUIDOR_MAIS_VAR[2] = {"SIMB_PONT_VIRG", ""};
char *SEGUIDOR_PROCEDIMENTO[8] = {"TK_ID", "CALL", "BEGIN", "IF", "WHILE", "SIMB_PONTO", "SIMB_PONT_VIRG", ""};
char *SEGUIDOR_COMANDO[4] = {"SIMB_PONTO", "SIMB_PONT_VIRG", "END", ""};
char *SEGUIDOR_MAIS_CMD[2] = {"END", ""};
char *SEGUIDOR_EXPRESSAO[12] = {"SIMB_PONTO", "SIMB_PONT_VIRG", "SIMB_FECHA_P", "THEN", "DO", "TK_ATRIBUICAO", "SIMB_MENOR_MAIOR", "SIMB_MENOR", "SIMB_MENOR_IGUAL", "SIMB_MAIOR", "SIMB_MAIOR_IGUAL", ""};
char *SEGUIDOR_OPERADOR_UNARIO[4] = {"TK_ID", "TK_NUM_INT", "SIMB_ABRE_P", ""};
char *SEGUIDOR_TERMO[14] = {"SIMB_SUB", "SIMB_SOMA", "SIMB_PONTO", "SIMB_PONT_VIRG", "SIMB_FECHA_P", "THEN", "DO", "SIMB_IGUAL_IGUAL", "SIMB_MENOR_MAIOR", "SIMB_MENOR", "SIMB_MENOR_IGUAL", "SIMB_MAIOR", "SIMB_MAIOR_IGUAL", ""};
char *SEGUIDOR_MAIS_TERMOS[12] = {"SIMB_PONTO", "SIMB_PONT_VIRG", "SIMB_FECHA_P", "THEN", "DO", "SIMB_IGUAL_IGUAL", "SIMB_MENOR_MAIOR", "SIMB_MENOR", "SIMB_MENOR_IGUAL", "SIMB_MAIOR", "SIMB_MAIOR_IGUAL", ""};
char *SEGUIDOR_FATOR[16] = {"SIMB_MULTIPLIC", "SIMB_DIV", "SIMB_SUB", "SIMB_SOMA", "SIMB_PONTO", "SIMB_PONT_VIRG", "SIMB_FECHA_P", "THEN", "DO", "SIMB_IGUAL_IGUAL", "SIMB_MENOR_MAIOR", "SIMB_MENOR", "SIMB_MENOR_IGUAL", "SIMB_MAIOR", "SIMB_MAIOR_IGUAL", ""};
char *SEGUIDOR_MAIS_FATORES[14] = {"SIMB_SUB", "SIMB_SOMA", "SIMB_PONTO", "SIMB_PONT_VIRG", "SIMB_FECHA_P", "THEN", "DO", "SIMB_IGUAL_IGUAL", "SIMB_MENOR_MAIOR", "SIMB_MENOR", "SIMB_MENOR_IGUAL", "SIMB_MAIOR", "SIMB_MAIOR_IGUAL", ""};
char *SEGUIDOR_CONDICAO[3] = {"THEN", "DO", ""};
char *SEGUIDOR_RELACIONAL[6] = {"SIMB_SUB", "SIMB_SOMA", "TK_ID", "TK_NUM_INT", "SIMB_ABRE_P", ""};

//------------------ Variáveis globais ----------------------
int cont_linha = 1; //armazena a linha atual que está sendo lida do programa
char mensagem1[256], mensagem2[256]; //armazena as msgs de erro
//Análise léxica
char char_lido, *classe, *token_atual;
char *ERROS_LEXICOS[5] = {"ERRO_NUMERO_MAL_FORMADO", "ERRO_ATRIB_MAL_FORMADO", "SIMB_NAO_IDENTIFICADO", "ERRO_COMENT_MAL_FORMADO", ""};

//------------------ Funções auxiliares ------------------
bool pertence(char *classe, char *conj[]) {
    for (int i = 0; conj[i][0] != '\0'; i++) {
        if (strcmp(conj[i], classe) == 0) {
            return true;
        }
    }
    return false;
}

char **uniao(char **conj1, char **conj2) {
    static char *resultado[64]; // capacidade máxima fixa
    int k = 0;

    for (int i = 0; conj1[i][0] != '\0'; i++) {
        resultado[k++] = (char *)conj1[i];  // casting só para compatibilidade
    }

    for (int i = 0; conj2[i][0] != '\0'; i++) {
        int duplicado = 0;
        for (int j = 0; j < k; j++) {
            if (strcmp(resultado[j], conj2[i]) == 0) {
                duplicado = 1;
                break;
            }
        }
        if (!duplicado) {
            resultado[k++] = (char *)conj2[i];
        }
    }

    resultado[k] = ""; // sentinela
    return resultado;
}

void erro(FILE *programa, FILE *output, char **S){ //Implementação do Modo Pânico
    while (!pertence(classe, S)){
        printf("Modo pânico / ");
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        if (char_lido == EOF)
            break;
    }
}

int leitura_sintatica(FILE *programa, FILE *output, char *classe_goal, char *erro1, char *erro2, char *seg_loc[], char *seg_pai[]){ //Função para modularização do código de tratamento de erros sintáticos/léxicos
    printf("Objetivo: %s / Entra: %s / ", classe_goal, classe);
    if (pertence(classe, ERROS_LEXICOS)){ //Não misturar erros léxicos com sintáticos
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        printf("Sai1: %s\n", classe);
        return 0; //Continua com a execução do procedimento que chamou essa função
    }
    if (!strcmp(classe, classe_goal)){
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        printf("Sai2: %s\n", classe);
        return 0; //Continua com a execução do procedimento que chamou essa função
    }
    else{ //ERRO
        char msg_ini[256];
        snprintf(msg_ini, sizeof(msg_ini), "Erro sintático na linha %d: %s", cont_linha, erro1);
        saida_sintatico(output, msg_ini); //Escrevendo a msg de erro no arquivo de saída

        erro(programa, output, uniao(seg_loc, seg_pai)); //Fazendo união do seguidor local com o seguidor do pai
        if (pertence(classe, SEGUIDOR_CONSTANTE)){ //Consumiu o procedimento inteiro
            snprintf(msg_ini, sizeof(msg_ini), "Erro sintático na linha %d: %s", cont_linha, erro2);
            saida_sintatico(output, msg_ini); //Escrevendo a msg de erro no arquivo de saída
            printf("Consumiu Procedimento / Sai3: %s\n", classe);
            return 1; //Interrompendo o procedimento que chamou essa função
        }
        printf("Sai4: %s\n", classe);
        return 0; //Continua com a execução do procedimento que chamou essa função
    }
}

//------------------ Implementação dos procedimentos sintáticos ------------------
void ASD(FILE *programa, FILE *output){
    //Alocação de memória para as variáveis da análise léxica
    classe = calloc(30, sizeof(char*));
    token_atual = calloc(100, sizeof(char*));
    
    char_lido = fgetc(programa);
    saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha)); //Lendo o token inicial do programa
    Programa(programa, output);

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

void Programa(FILE *programa, FILE *output){
    // Esta função chama constante, variavel, procedimento e comando
    Constante(programa, output);
    Variavel(programa, output);
    /*Procedimento(programa, output);
    Comando(programa, output);*/

    if(!strcmp(classe, "SIMB_PONTO")) { // Tudo certo, finaliza o programa
        // Precisamos tratar dos erros que ocorrem se eu colocar . finalizando o programa
        //mas continuar escrevendo alguma coisa 
        
        printf("Finalizando o programa...\n");
        return; 
    }
    else{
        printf("Erro sintático - programa foi finalizado sem .\n");
    }
    saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha)); //Consumindo o EOF
}


void Constante(FILE *programa, FILE *output){
    char *seguidor_local[10];
    if (!strcmp(classe, "CONST")){
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        while (1){
            // Identificação ident
            //Preparando possíveis msgs de erro sintático
            snprintf(mensagem1, sizeof(mensagem1), "identificador esperado, mas recebeu-se %s", token_atual);
            snprintf(mensagem2, sizeof(mensagem2), "símbolo '=' esperado");
            //Organizando seguidor(es) local(is)
            seguidor_local[0] = "SIMB_IGUAL_IGUAL";
            seguidor_local[1] = "";
            //Fazendo a identificação e verificando erros - aplicando modo pânico caso necessário
            if (leitura_sintatica(programa, output, "TK_ID", mensagem1, mensagem2, seguidor_local, SEGUIDOR_CONSTANTE))
                return; //Modo pânico consumiu o procedimento inteiro

            // Identificação '='
            snprintf(mensagem1, sizeof(mensagem1), "símbolo '=' esperado entre a constante e o número");
            snprintf(mensagem2, sizeof(mensagem2), "número inteiro esperado, recebeu-se %s", token_atual);
            seguidor_local[0] = "TK_NUM_INT";
            seguidor_local[1] = "";
            if (leitura_sintatica(programa, output, "SIMB_IGUAL_IGUAL", mensagem1, mensagem2, seguidor_local, SEGUIDOR_CONSTANTE))
                return; //Modo pânico consumiu o procedimento inteiro
            
            // Identificação número inteiro
            snprintf(mensagem1, sizeof(mensagem1), "número inteiro esperado, recebeu-se %s no lugar", token_atual);
            snprintf(mensagem2, sizeof(mensagem2), "símbolo ';' esperado");
            seguidor_local[0] = "SIMB_VIRGULA";
            seguidor_local[1] = "SIMB_PONT_VIRG";
            seguidor_local[2] = "TK_ID"; //Adição artificial de TK_ID como seguidor para possibilitar a identificação de ausência de vírgula
            seguidor_local[3] = "";
            if (leitura_sintatica(programa, output, "TK_NUM_INT", mensagem1, mensagem2, seguidor_local, SEGUIDOR_CONSTANTE))
                return; //Modo pânico consumiu o procedimento inteiro

            //Caso não achou número e chegou aqui - token é virgula, ponto e vírgula ou ident // Caso achou - token é vírgula ou ponto e vírgula, se não for é caractere estranho
            if (!strcmp(classe, "SIMB_PONT_VIRG")){ // Sai do ciclo e encerra o procedimento
                printf("Constante Sucesso!\n");
                saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
                return;
            }
            if(!strcmp(classe, "TK_ID")){ //ERRO - leu ident mesmo não tendo vírgula nenhuma
                snprintf(mensagem1, sizeof(mensagem1), "Erro sintático na linha %d: ausência de ',' separando as constantes", cont_linha);
                saida_sintatico(output, mensagem1); //Escrevendo a msg de erro no arquivo de saída
            }
            else if (!strcmp(classe, "SIMB_VIRGULA")){ //Leu a vírgula, continua com a análise de CONSTANTE
                saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
            } 
            else{ //ERRO - leu um símbolo estranho que não é a vírgula
                snprintf(mensagem1, sizeof(mensagem1), "Erro sintático na linha %d: símbolo estranho no contexto (%s) ...", cont_linha, token_atual);
                saida_sintatico(output, mensagem1); //Escrevendo a msg de erro no arquivo de saída
                
                erro(programa, output, SEGUIDOR_CONSTANTE); //Modo pânico consumindo o procedimento inteiro
                printf("\nFinar: %s\n", classe);
                if (char_lido != EOF){
                    snprintf(mensagem1, sizeof(mensagem1), "...Continuando a análise sintática na linha %d e no símbolo %s", cont_linha, token_atual);
                    saida_sintatico(output, mensagem1); //Escrevendo a msg de erro no arquivo de saída
                }
            }
        }
    }
}

void Variavel(FILE *programa, FILE *output){
    char *seguidor_local[10];
    if (!strcmp(classe, "VAR")){
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        while (1){
            // Identificação ident
            //Preparando possíveis msgs de erro sintático
            snprintf(mensagem1, sizeof(mensagem1), "identificador esperado, mas recebeu-se %s", token_atual);
            snprintf(mensagem2, sizeof(mensagem2), "símbolo '=' esperado");
            //Organizando seguidor(es) local(is)
            seguidor_local[0] = "SIMB_VIRGULA";
            seguidor_local[1] = "SIMB_PONT_VIRG";
            seguidor_local[2] = "TK_ID"; //Adição artificial
            seguidor_local[3] = "";
            //Fazendo a identificação e verificando erros - aplicando modo pânico caso necessário
            if (leitura_sintatica(programa, output, "TK_ID", mensagem1, mensagem2, seguidor_local, SEGUIDOR_CONSTANTE))
                return; //Modo pânico consumiu o procedimento inteiro

            //Chegou aqui - último token lido foi uma vírgula, um ponto e vírgula ou um identificador
            if (!strcmp(classe, "SIMB_PONT_VIRG")){ // Sai do ciclo e encerra o procedimento
                printf("Constante Sucesso!\n");
                saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
                return;
            }
            if(!strcmp(classe, "TK_ID")){ //ERRO - leu ident mesmo não tendo vírgula nenhuma
                snprintf(mensagem1, sizeof(mensagem1), "Erro sintático na linha %d: ausência de ',' separando as variáveis", cont_linha);
                saida_sintatico(output, mensagem1); //Escrevendo a msg de erro no arquivo de saída
            }
            else if (!strcmp(classe, "SIMB_VIRGULA")){ //Leu a vírgula, continua com a análise de CONSTANTE
                saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
            } 
            else{ //ERRO - leu um símbolo estranho que não é a vírgula
                snprintf(mensagem1, sizeof(mensagem1), "Erro sintático na linha %d: símbolo estranho no contexto (%s) ...", cont_linha, token_atual);
                saida_sintatico(output, mensagem1); //Escrevendo a msg de erro no arquivo de saída
                
                erro(programa, output, SEGUIDOR_CONSTANTE); //Modo pânico consumindo o procedimento inteiro
                printf("\nFinar: %s\n", classe);
                if (char_lido != EOF){
                    snprintf(mensagem1, sizeof(mensagem1), "...Continuando a análise sintática na linha %d e no símbolo %s", cont_linha, token_atual);
                    saida_sintatico(output, mensagem1); //Escrevendo a msg de erro no arquivo de saída
                }
            }
        }
    }
}

void Procedimento(FILE *programa, FILE *output){
    if (!strcmp(classe, "PROCEDURE")){
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        if (!strcmp(classe, "TK_ID")){
            saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
            if (!strcmp(classe, "SIMB_PONT_VIRG")){
                saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));

                //Chamando Bloco
                Constante(programa, output);
                saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
                Variavel(programa, output);
                saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
                Procedimento(programa, output);
                saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
                Comando(programa, output);

                saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
                if (!strcmp(classe, "SIMB_PONT_VIRG")){
                    printf("Procedimento Sucesso!\n");
                    saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
                }
            }
        }
    }
}

void Comando(FILE *programa, FILE *output){
    if (!strcmp(classe, "TK_ID")){
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        if (!strcmp(classe, "TK_ATRIBUICAO")){
            saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
            Expressao(programa, output);
            printf("Comando Sucesso! - Atribuição\n");
            saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        }
    }
    else if (!strcmp(classe, "CALL")){
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        if (!strcmp(classe, "TK_ID")){
            printf("Comando Sucesso! - CALL Procedure\n");
            saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        }
    }
    else if (!strcmp(classe, "BEGIN")){
        while (1){
            saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
            Comando(programa, output);
            if (strcmp(classe, "SIMB_PONT_VIRG")){ //Caso seja diferente de ;, encerra o ciclo e busca END
                break;
            }
        }
        if (!strcmp(classe, "END")){
            printf("Comando Sucesso! - BEGIN ... END\n");
            saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        }

    }
    else if (!strcmp(classe, "IF")){
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        Condicao(programa, output);
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        if (!strcmp(classe, "THEN")){
            saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
            Comando(programa, output);
            printf("Comando Sucesso! - IF\n");
            saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        }
    }
    else if (!strcmp(classe, "WHILE")){
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        if (!strcmp(classe, "WHILE")){
            saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
            Condicao(programa, output);
            saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
            if (!strcmp(classe, "DO")){
                saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
                Comando(programa, output);
                printf("Comando Sucesso! - WHILE\n");
                saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
            }
        }
    }
}

void Expressao(FILE *programa, FILE *output){
    if (!strcmp(classe, "SIMB_SOMA") || !strcmp(classe, "SIMB_SUB") || pertence(classe, PRIMEIRO_FATOR)){
        while (1){
            saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
            Fator(programa, output);
            saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
            Mais_Fator(programa, output);
            if (strcmp(classe, "SIMB_SOMA") || strcmp(classe, "SIMB_SUB")){ //Sem + ou -, encerasse o ciclo
                break;
            }
        }
        printf("Expressao Sucesso!\n");
    }
}

void Fator(FILE *programa, FILE *output){
    if (!strcmp(classe, "TK_ID")){
        printf("Fator Sucesso! - ident\n");
    }
    else if (!strcmp(classe, "TK_NUM_INT")){
        printf("Fator Sucesso! - numero\n");
    }
    else if (!strcmp(classe, "TK_ABRE_P")){
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        Expressao(programa, output);
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        if (!strcmp(classe, "TK_FECHA_P")){
            printf("Fator Sucesso! - parenteses\n");
        }
    }
}

void Mais_Fator(FILE *programa, FILE *output){
    while (!strcmp(classe, "SIMB_MULTIPLIC") || !strcmp(classe, "SIMB_DIV")){
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        Fator(programa, output);
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
    }
    printf("Mais Fator Sucesso!\n");
    saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
}

void Condicao(FILE *programa, FILE *output){
    if (!strcmp(classe, "ODD")){
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        Expressao(programa, output);
    }
    else if (pertence(classe, PRIMEIRO_EXPRESSAO)){
        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        Expressao(programa, output);

        saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
        if (!strcmp(classe, "SIMB_IGUAL_IGUAL") || !strcmp(classe, "SIMB_MENOR_MAIOR") || !strcmp(classe, "SIMB_MENOR_IGUAL") || !strcmp(classe, "SIMB_MAIOR") || !strcmp(classe, "SIMB_MENOR") || !strcmp(classe, "SIMB_MAIOR_IGUAL")){
            saida_sintatico(output, obtem_token_e_erro(&char_lido, programa, &classe, &token_atual, &cont_linha));
            Expressao(programa, output);
        }
    }
}