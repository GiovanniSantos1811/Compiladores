#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "arquivo.h"
#include "lexico.h"


int main() {
    preenche_hash();
    char nome_arquivo[256];
    int opcao, resultado = -1;
    // Interface com o usuário
    printf("\n------------------------------------------------------------------------------------\n");
    printf("Bem vindo ao compilador da linguagem PL/0! Aqui fazemos análise léxica e sintática.\n");
    printf("\n------------------------------------------------------------------------------------\n");
    while (resultado == -1){
        printf("Digite o nome do arquivo que deseja realizar o processo de compilação parcial (incluindo a extensão!): ");
        scanf("%s", nome_arquivo);
        while (1){
        printf("Escolha qual análise será feita. Digite 1 para léxica e 2 para sintática: ");
        scanf("%d", &opcao);
        if (opcao == 1){
            resultado = leitura_arquivo_lexico(nome_arquivo);
            break;
        }
        else if (opcao == 2){
            resultado = leitura_arquivo_sintatico(nome_arquivo);
            break;
        }
        else{
            printf("Digite uma das opçõs descritas!\n");
        }
        }
        
    }
    printf("\nProcesso de compilação parcial concluída! Resultado está em output.txt\n");
    
    
    return 0;
}