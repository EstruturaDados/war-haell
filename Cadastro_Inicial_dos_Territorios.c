#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Struct Territorio:
    Armazena nome, cor do exército e quantidade de tropas
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/*
    Função para exibir todos os territórios
*/
void exibirMapa(Territorio* mapa, int total) {
    printf("\n===== ESTADO ATUAL DO MAPA =====\n");
    for (int i = 0; i < total; i++) {
        printf("Território %d:\n", i);
        printf("  Nome : %s\n", mapa[i].nome);
        printf("  Cor  : %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
        printf("--------------------------------\n");
    }
}

/*
    Função de ataque:
    - Gera um valor aleatório de 1 a 6 para atacante e defensor
    - Atualiza tropas e dono do território conforme resultado
*/
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoAtacante = (rand() % 6) + 1;  
    int dadoDefensor = (rand() % 6) + 1;

    printf("\n===== ATAQUE =====\n");
    printf("Atacante (%s) rolou: %d\n", atacante->nome, dadoAtacante);
    printf("Defensor  (%s) rolou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf(">> O atacante venceu!\n");

        strcpy(defensor->cor, atacante->cor);   // muda o dono
        defensor->tropas = atacante->tropas / 2; // metade das tropas do atacante

        printf("Território %s agora pertence ao exército %s!\n",
               defensor->nome, defensor->cor);

    } else {
        printf(">> O defensor resistiu! O atacante perdeu 1 tropa.\n");
        atacante->tropas--;

        if (atacante->tropas < 0)
            atacante->tropas = 0;
    }
}

/*
    Libera memória alocada dinamicamente
*/
void liberarMemoria(Territorio* mapa) {
    free(mapa);
}

/*
    Função principal
*/
int main() {
    srand(time(NULL)); // garante aleatoriedade

    int total;
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &total);
    getchar(); // limpa o ENTER do buffer

    // Alocação dinâmica do vetor de territórios
    Territorio* mapa = (Territorio*) malloc(total * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro dos territórios
    for (int i = 0; i < total; i++) {
        printf("\nCadastro do território %d\n", i);

        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor do exército: ");
        scanf(" %s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    // Exibe o mapa após cadastro
    exibirMapa(mapa, total);

    // Loop de ataque
    int opcao;
    do {
        printf("\n===== MENU DE AÇÃO =====\n");
        printf("1 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int idAtacante, idDefensor;

            exibirMapa(mapa, total);

            printf("\nEscolha o número do território ATACANTE: ");
            scanf("%d", &idAtacante);

            printf("Escolha o número do território DEFENSOR: ");
            scanf("%d", &idDefensor);

            // Validações básicas
            if (idAtacante < 0 || idAtacante >= total ||
                idDefensor < 0 || idDefensor >= total) {
                printf("IDs inválidos!\n");
                continue;
            }

            if (strcmp(mapa[idAtacante].cor, mapa[idDefensor].cor) == 0) {
                printf("Não é possível atacar um território da mesma cor!\n");
                continue;
            }

            if (mapa[idAtacante].tropas <= 0) {
                printf("O atacante não possui tropas suficientes!\n");
                continue;
            }

            atacar(&mapa[idAtacante], &mapa[idDefensor]);
            exibirMapa(mapa, total);
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    printf("Memória liberada. Programa encerrado.\n");

    return 0;
}
