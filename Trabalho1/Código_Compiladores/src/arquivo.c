#include<stdlib.h>
#include<stdio.h>

// void ler_arquivo_caractere(const char *nome_arquivo) {
//     FILE *arquivo = fopen(nome_arquivo, "r");
//     if (arquivo == NULL) {
//         perror("Erro ao abrir o arquivo");
//         return;
//     }

//     char c;
//     while ((c = fgetc(arquivo)) != EOF) {
//         printf("%c", c);
//     }

//     fclose(arquivo);
// }

void escrever_arquivo(const char *nome_arquivo, const char *conteudoToken, const char *conteudoClass) {
    FILE *arquivo = fopen(nome_arquivo, "w"); 
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        return;
    }

    fputs(conteudoToken, arquivo);
    fputs(", ", arquivo);
    fputs(conteudoClass, arquivo);
    fclose(arquivo);
}
