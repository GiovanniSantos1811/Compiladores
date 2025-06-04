#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "sintatico.h"
#include "lexico.h"
#include "arquivo.h"
#include <stdbool.h>

//Primeiros e Seguidores (Importante ressaltar que "" está sendo usado como caractere sentinela, sendo, nesse caso, o lambda não mapeado aqui)
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
char *PRIMEIRO_FATOR[4] = {"TK_ID", "TK_NUM_INT", "SIMB_ABRE_P", ""};

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

//Variáveis globais
int cont_linha = 1; //armazena a linha atual que está sendo lida do programa
static char mensagem[256]; //armazena as msgs de erro

//Funções auxiliares
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

void erro(char *char_lido, FILE *programa, FILE *output, char **classe, char **token_atual, char **S){ //Implementação do Modo Pânico
    while (!pertence(*classe, S)){
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        printf("classe: %s\n", *classe);
        if (*char_lido == EOF)
            break;
    }
}

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
    /*Variavel(char_lido, programa, output, classe, token_atual);
    Procedimento(char_lido, programa, output, classe, token_atual);
    Comando(char_lido, programa, output, classe, token_atual);*/

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
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        while (1){
            if (!strcmp(*classe, "TK_ID")){
                saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            }
            else{ //ERRO
                snprintf(mensagem, sizeof(mensagem), "Erro sintático na linha %d: identificador esperado, mas recebeu-se %s", cont_linha, *token_atual);
                saida_sintatico(output, mensagem); //Escrevendo a msg de erro no arquivo de saída

                char *seguidor_local[2] = {"SIMB_IGUAL_IGUAL", ""};
                erro(char_lido, programa, output, classe, token_atual, uniao(seguidor_local, SEGUIDOR_CONSTANTE)); //Fazendo união do seguidor local com o seguidor do pai
                if (pertence(*classe, SEGUIDOR_CONSTANTE)){ //Consumiu o procedimento inteiro
                    snprintf(mensagem, sizeof(mensagem), "Erro sintático na linha %d: símbolo '=' esperado", cont_linha);
                    saida_sintatico(output, mensagem); //Escrevendo a msg de erro no arquivo de saída
                    return; //Interrompendo o procedimento
                }
            }

            if (!strcmp(*classe, "SIMB_IGUAL_IGUAL")){
                saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            }
            else{ //ERRO
                snprintf(mensagem, sizeof(mensagem), "Erro sintático na linha %d: símbolo '=' esperado", cont_linha);
                saida_sintatico(output, mensagem); //Escrevendo a msg de erro no arquivo de saída

                char *seguidor_local[2] = {"TK_NUM_INT", ""};
                erro(char_lido, programa, output, classe, token_atual, uniao(seguidor_local, SEGUIDOR_CONSTANTE));
                if (pertence(*classe, SEGUIDOR_CONSTANTE)){ //Consumiu o procedimento inteiro
                    snprintf(mensagem, sizeof(mensagem), "Erro sintático na linha %d: número inteiro esperado, recebeu-se %s", cont_linha, *token_atual);
                    saida_sintatico(output, mensagem); //Escrevendo a msg de erro no arquivo de saída
                    return; //Interrompendo o procedimento
                }
            }

            if (!strcmp(*classe, "TK_NUM_INT")){
                saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));   
            }
            else{ //ERRO
                snprintf(mensagem, sizeof(mensagem), "Erro sintático na linha %d: número inteiro esperado, recebeu-se %s no lugar", cont_linha, *token_atual);
                saida_sintatico(output, mensagem); //Escrevendo a msg de erro no arquivo de saída
                
                char *seguidor_local[4] = {"SIMB_VIRGULA", "SIMB_PONT_VIRG", "TK_ID", ""};
                erro(char_lido, programa, output, classe, token_atual, uniao(seguidor_local, SEGUIDOR_CONSTANTE)); //Adição artificial de TK_ID commo seguidor local, para permitir a identificação da ausência de vírgula
                if (pertence(*classe, SEGUIDOR_CONSTANTE)){ //Consumiu o procedimento inteiro
                    snprintf(mensagem, sizeof(mensagem), "Erro sintático na linha %d: símbolo ';' esperado", cont_linha);
                    saida_sintatico(output, mensagem); //Escrevendo a msg de erro no arquivo de saída
                    return; //Interrompendo o procedimento
                }
            }
            
            //Chegou aqui - último token lido foi uma vírgula, um ponto e vírgula ou um identificador
            if (!strcmp(*classe, "SIMB_PONT_VIRG")){ // Sai do ciclo e encerra o procedimento
                printf("Constante Sucesso!\n");
                saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
                return;
            }
            if (!strcmp(*classe, "SIMB_VIRGULA")){ // Lê uma virgula, então consome o próximo token e continua no loop
                saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            }
            else{ // ERRO - Leu um ident sem vírgula antes
                snprintf(mensagem, sizeof(mensagem), "Erro sintático na linha %d: ausência de ',' separando as constantes", cont_linha);
                saida_sintatico(output, mensagem); //Escrevendo a msg de erro no arquivo de saída
            }
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
    if (!strcmp(*classe, "SIMB_SOMA") || !strcmp(*classe, "SIMB_SUB") || pertence(*classe, PRIMEIRO_FATOR)){
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
    else if (pertence(*classe, PRIMEIRO_EXPRESSAO)){
        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        Expressao(char_lido, programa, output, classe, token_atual);

        saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
        if (!strcmp(*classe, "SIMB_IGUAL_IGUAL") || !strcmp(*classe, "SIMB_MENOR_MAIOR") || !strcmp(*classe, "SIMB_MENOR_IGUAL") || !strcmp(*classe, "SIMB_MAIOR") || !strcmp(*classe, "SIMB_MENOR") || !strcmp(*classe, "SIMB_MAIOR_IGUAL")){
            saida_sintatico(output, obtem_token_e_erro(char_lido, programa, classe, token_atual, &cont_linha));
            Expressao(char_lido, programa, output, classe, token_atual);
        }
    }
}