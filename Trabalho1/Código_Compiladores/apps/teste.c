#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "arquivo.h"
#include "lexico.h"


int main() {
    //------------- Análise Léxica ----------------------
    preenche_hash();
    
    leitura_arquivo_lexico("fatorialsemprocedimento.txt");

    //printf("%d\n", transicao(' ', 0));
    
    return 0;
}
