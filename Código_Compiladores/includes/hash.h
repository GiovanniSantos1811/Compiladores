#ifndef TABELA_HASH
#define TABELA_HASH

// Estruturas
typedef struct tipo_no No; 

// Funções
void inserir(const char *palavra); // Função para inserir na tabela
int buscar(const char *palavra); // Função para buscar uma palavra na tabela
void liberar_tabela(); // Desalocar memória

#endif