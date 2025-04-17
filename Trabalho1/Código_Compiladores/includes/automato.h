#ifndef AUTOMATO_H
#define AUTOMATO_H

#define NUM_ESTADOS 26
#define NUM_SIMBOLOS 18 //52 letras, 10 digitos, 16 simbolos (:	 =	 +	-	<	>	;	,	(	)	{	}	'	\t	\n .)

#define ERRO_NUMERO_MAL_FORMADO -1
#define TK_NUM_INT -2
#define TK_ID -3
#define TK_ATRIBUICAO -4
#define SIMB_SOMA -5
#define SIMB_SUB -6
#define SIMB_IGUAL_IGUAL -7
#define SIMB_MENOR -8
#define SIMB_MENOR_MAIOR -9
#define SIMB_MENOR_IGUAL -10
#define SIMB_MAIOR -11
#define SIMB_MAIOR_IGUAL -11
#define SIMB_PONT_VIRG -12
#define SIMB_VIRGULA -13
#define SIMB_FECHA_P -14
#define SIMB_ABRE_P -15
#define COMENTARIO -16
#define ERRO_IDENT_MAL_FORMADO -17
#define ERRO_ATRIB_MAL_FORMADO -18

int transicao[NUM_ESTADOS][NUM_SIMBOLOS];

#endif