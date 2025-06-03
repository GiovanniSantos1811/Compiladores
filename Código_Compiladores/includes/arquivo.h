#ifndef ARQUIVO_H
#define ARQUIVO_H

int leitura_arquivo_lexico(const char *nome_arquivo);
void saida_lexico(FILE *arquivo, char *conteudoToken, char *conteudoClass);

void saida_sintatico(FILE *arquivo, char *msg);
int leitura_arquivo_sintatico(const char *nome_arquivo);

#endif