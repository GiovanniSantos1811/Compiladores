#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "arquivo.h"
#include "lexico.h"


int main() {
    //------------- Análise Sintática chamando a Análise Léxica e mostrando os erros sintáticos e léxicos ----------------------
    preenche_hash();
    
    leitura_arquivo_lexico("fatorialcomprocedimento.txt");
    
    return 0;
}