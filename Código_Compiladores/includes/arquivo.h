#ifndef ARQUIVO_H
#define ARQUIVO_H

int leitura_arquivo_lexico(const char *nome_arquivo);
void escrever_arquivo(FILE *arquivo, char *conteudoToken, char *conteudoClass);

#endif