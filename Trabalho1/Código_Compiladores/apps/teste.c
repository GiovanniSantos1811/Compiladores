#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include "arquivo.h"


// int main() {

//     inserir("danete");

//     if (buscar("danete")) {
//         printf("A palavra danete foi encontrada!\n");
//     } else {
//         printf("A palavra danete NAO foi encontrada!\n");
//     }


//     return 0;
// }

int main() {
    const char *nome_programa = "fatorialsemprocedimento.txt";
    const char *nome_saida = "output.txt";
    remove(nome_saida);

    ler_arquivo_caractere(nome_programa);
    escrever_arquivo(nome_saida, "testando");

    return 0;
}