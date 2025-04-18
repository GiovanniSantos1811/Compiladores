#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "arquivo.h"
#include "automato.h"

int main() {
    const char *nome_programa = "teste.txt";
    const char *nome_saida = "output.txt";
    remove(nome_saida);

    FILE *programa = fopen(nome_programa, "r");
    if (programa == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    char char_lido;
    char token_atual[100];
    int estado_atual = 0, cont = 0, flag = 0;

    while (char_lido != EOF) { //Fazendo a leitura caractere a caractere do programa
        if (flag == 0)
            char_lido = fgetc(programa);
        else
            token_atual[cont++] = char_lido;
        //char_lido = fgetc(programa);

        estado_atual = transicao(char_lido, estado_atual);

        if (estado_atual < 0){ //Estado Final
            token_atual[cont] = '\0'; //Garantindo o caractere terminador de string para o token poder ser printado
            cont = 0;
            estado_atual = 0;

            if (flag == 0)
                flag++;
            else   
                flag = 0;
            
            printf("%s\n", token_atual);
        }
        else if(estado_atual != 0){ //Estado intermediário (garantindo que tenha saído do estado inicial)
            token_atual[cont++] = char_lido;
        }
    }
    
    fclose(programa);
    return 0;
}