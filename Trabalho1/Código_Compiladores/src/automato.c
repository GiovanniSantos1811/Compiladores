#include <stdio.h>
#include <string.h>
#include "automato.h"

Estado transicao(Estado estado_atual, char simbolo) {
    switch (estado_atual) {
        case q0:
            if (simbolo == letra) return q4;
            if (simbolo == digito) return q1;
            if (simbolo == ':') return q6;
            if (simbolo == '=') return q10;
            if (simbolo == '+') return q8;
            if (simbolo == '-') return q9;
            if (simbolo == '<') return q11;
            if (simbolo == '>') return q15;
            if (simbolo == ';') return q18;
            if (simbolo == ',') return q19;
            if (simbolo == '(') return q21;
            if (simbolo == ')') return q20;
            if (simbolo == '{') return q22;
            if (simbolo == '}') return q24;
            if (simbolo == '') return q0;
            if (simbolo == '\t') return q0;
            if (simbolo == '\n') return q0;
            break;

        case q1:
            if (simbolo == letra) return q2;
            if (simbolo == digito) return q1;
            if (simbolo == ':') return q3;
            if (simbolo == '=') return q3;
            if (simbolo == '+') return q3;
            if (simbolo == '-') return q3;
            if (simbolo == '<') return q3;
            if (simbolo == '>') return q3;
            if (simbolo == ';') return q3;
            if (simbolo == ',') return q3;
            if (simbolo == '(') return q3;
            if (simbolo == ')') return q3;
            if (simbolo == '{') return q3;
            if (simbolo == '}') return q3;
            if (simbolo == '') return q3;
            if (simbolo == '\t') return q3;
            if (simbolo == '\n') return q3;
            break;
        
        case q2:
            return (-2); // ERRO_NUMERO_MAL_FORMADO
            break;

        case q3:
            return (-3); // TK_NUM_INT
            break;
            
        case q4:
            if (simbolo == letra) return q4;
            if (simbolo == digito) return q4;
            if (simbolo == ':') return q5;
            if (simbolo == '=') return q5;
            if (simbolo == '+') return q5;
            if (simbolo == '-') return q5;
            if (simbolo == '<') return q5;
            if (simbolo == '>') return q5;
            if (simbolo == ';') return q5;
            if (simbolo == ',') return q5;
            if (simbolo == '(') return q5;
            if (simbolo == ')') return q5;
            if (simbolo == '{') return q5;
            if (simbolo == '}') return q5;
            if (simbolo == '') return q5;
            if (simbolo == '\t') return q5;
            if (simbolo == '\n') return q5;
            break;

        case q5:
            return (-4); // TK_ID
            break;
                
        case q6:
            if (simbolo == letra) return q26;
            if (simbolo == digito) return q26;
            if (simbolo == ':') return q26;
            if (simbolo == '=') return q7;
            if (simbolo == '+') return q26;
            if (simbolo == '-') return q26;
            if (simbolo == '<') return q26;
            if (simbolo == '>') return q26;
            if (simbolo == ';') return q26;
            if (simbolo == ',') return q26;
            if (simbolo == '(') return q26;
            if (simbolo == ')') return q26;
            if (simbolo == '{') return q26;
            if (simbolo == '}') return q26;
            if (simbolo == '') return q26;
            if (simbolo == '\t') return q26;
            if (simbolo == '\n') return q26;
            break;
    }
    return (-1); // Estado inválido
}

int reconhecer(const char *entrada) {
    Estado estado = q0;

    for (int i = 0; i < strlen(entrada); i++) {
        char simbolo = entrada[i];
        if (simbolo != 'a' && simbolo != 'b') {
            printf("Símbolo inválido: %c\n", simbolo);
            return 0;
        }
        estado = transicao(estado, simbolo);
    }

    return estado == q2;
}