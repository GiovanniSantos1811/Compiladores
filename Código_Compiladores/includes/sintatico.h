#ifndef SINTATICO_H
#define SINTATICO_H

//Procedimentos Sintáticos
void ASD(FILE *programa, FILE *output); //Inicia a análise sintática descendente preditiva recursiva
void Programa(FILE *programa, FILE *output);
void Constante(FILE *programa, FILE *output);
void Variavel(FILE *programa, FILE *output);
void Procedimento(FILE *programa, FILE *output);
void Comando(FILE *programa, FILE *output);
void Expressao(FILE *programa, FILE *output, int modo);
int Fator(FILE *programa, FILE *output, int modo);
void Mais_Fator(FILE *programa, FILE *output, int modo);
void Condicao(FILE *programa, FILE *output);

#endif