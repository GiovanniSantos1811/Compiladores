#ifndef AUTOMATO_H
#define AUTOMATO_H

typedef enum {q0, q1, q2, q3, q4, q5, q6, q7, q8, q9, 
    q10, q11, q12, q13, q14, q15, q16, q17, 
    q18, q19, q20, q21, q22, q23, q24, q25} Estados;

Estado transicao(Estado estado_atual, char simbolo);
int reconhecer(const char *entrada);

#endif