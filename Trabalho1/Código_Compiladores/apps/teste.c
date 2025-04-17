#include <stdio.h>
#include <stdlib.h>
#include "hash.h"


int main() {

    inserir("danete");

    if (buscar("danete")) {
        printf("A palavra danete foi encontrada!\n");
    } else {
        printf("A palavra danete NAO foi encontrada!\n");
    }


    return 0;
}