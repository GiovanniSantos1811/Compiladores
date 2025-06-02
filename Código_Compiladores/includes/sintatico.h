#ifndef SINTATICO_H
#define SINTATICO_H

//Procedimentos Sintáticos
void ASD(FILE *programa); //Inicia a análise sintática descendente preditiva recursiva
void Programa(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Constante(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Variavel(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Procedimento(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Comando(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Expressao(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Fator(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Mais_Fator(char *char_lido, FILE *programa, char **classe, char **token_atual);
void Condicao(char *char_lido, FILE *programa, char **classe, char **token_atual);

#endif