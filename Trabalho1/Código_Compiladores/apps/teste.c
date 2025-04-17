#include <stdio.h>
#include <stdlib.h>
#include "hash.h"


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
    FILE *programa;
    char linha[256];

    programa = fopen("fatorialsemprocedimento.txt", "r");

    if (programa == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    while (fgets(linha, sizeof(linha), programa)) {
        printf("%s", linha);

        // if (reconhecer(linha)) {
        //     printf("Linha pertence a linguagem.\n");
        // } else {
        //     printf("Linha nao pertence a linguagem.\n");
        // }
    }

    fclose(programa);

    return 0;
}