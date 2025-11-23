#include <stdio.h>
#include <string.h>

/*
  Programa: Cadastro Inicial dos Territórios
  Objetivo: Demonstrar uso de struct e vetor estático (5 elementos).
  Struct Territorio possui: nome (30), cor (10) e tropas (int).
*/

/* Definição da struct Territorio */
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/* Função auxiliar para limpar o buffer de entrada (stdin) */
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* descarta caracteres até o fim da linha */
    }
}

int main() {
    Territorio territorios[5]; /* vetor estático para 5 territórios */
    int i;

    printf("Cadastro de 5 territórios\n");
    printf("------------------------\n");

    for (i = 0; i < 5; i++) {
        printf("\nTerritório %d\n", i + 1);
        printf("------------\n");

        /* Leitura do nome: permitir espaços no nome */
        printf("Digite o NOME do território (max 29 caracteres): ");
        /* O espaço antes do %29[^\n] faz o scanf ignorar espaços e quebras anteriores */
        scanf(" %29[^\n]", territorios[i].nome);
        limpar_buffer(); /* remove a quebra de linha pendente (se houver) */

        /* Leitura da cor do exército: uma palavra (sem espaços) */
        printf("Digite a COR do exército dominante (ex: vermelho): ");
        /* usamos %9s para limitar e evitar overflow */
        scanf(" %9s", territorios[i].cor);
        limpar_buffer();

        /* Leitura do número de tropas */
        printf("Digite o NUMERO de tropas (inteiro): ");
        while (scanf("%d", &territorios[i].tropas) != 1) {
            /* se entrada inválida, avisar e solicitar novamente */
            printf("Entrada inválida. Digite um número inteiro para tropas: ");
            limpar_buffer();
        }
        limpar_buffer();

        printf("-> Território %d cadastrado com sucesso!\n", i + 1);
    }

    /* Exibição organizada dos dados de todos os territórios */
    printf("\n\nEstado atual do mapa (Todos os territórios):\n");
    printf("===========================================\n");
    for (i = 0; i < 5; i++) {
        printf("Território %d:\n", i + 1);
        printf("  Nome : %s\n", territorios[i].nome);
        printf("  Cor  : %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("-------------------------------------------\n");
    }

    return 0;
}
