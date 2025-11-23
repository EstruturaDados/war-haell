#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
    Estrutura do território
*/
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

/*
    Exibe o mapa atual de todos os territórios
*/
void exibirMapa(Territorio* mapa, int total) {
    printf("\n===== ESTADO DO MAPA =====\n");
    for (int i = 0; i < total; i++) {
        printf("Território %d:\n", i);
        printf(" Nome  : %s\n", mapa[i].nome);
        printf(" Cor   : %s\n", mapa[i].cor);
        printf(" Tropas: %d\n", mapa[i].tropas);
        printf("------------------------------\n");
    }
}

/*
    Função para executar o ataque
*/
void atacar(Territorio* atacante, Territorio* defensor) {
    int dadoA = (rand() % 6) + 1;
    int dadoD = (rand() % 6) + 1;

    printf("\n===== ATAQUE =====\n");
    printf("%s (A) rolou %d\n", atacante->nome, dadoA);
    printf("%s (D) rolou %d\n", defensor->nome, dadoD);

    if (dadoA > dadoD) {
        printf(">> O atacante venceu!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
    } else {
        printf(">> O defensor resistiu. Atacante perde 1 tropa.\n");
        atacante->tropas--;
        if (atacante->tropas < 0) atacante->tropas = 0;
    }
}

/*
    Exibe a missão do jogador
*/
void exibirMissao(char* missao) {
    printf("\n===== SUA MISSÃO =====\n");
    printf("%s\n", missao);
    printf("=======================\n");
}

/*
    Sorteia uma missão e copia para a missão do jogador
*/
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes;
    strcpy(destino, missoes[indice]);
}

/*
    Verifica se a missão foi concluída
    (lógica simples para iniciantes)
*/
int verificarMissao(char* missao, Territorio* mapa, int tamanho) {

    if (strcmp(missao, "Conquistar 3 territórios seguidos") == 0) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "azul") == 0) count++;
        }
        return (count >= 3);
    }

    if (strcmp(missao, "Eliminar todas as tropas vermelhas") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelha") == 0 && mapa[i].tropas > 0)
                return 0;
        }
        return 1;
    }

    if (strcmp(missao, "Controlar 2 territórios grandes") == 0) {
        int count = 0;
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas >= 10 && strcmp(mapa[i].cor, "azul") == 0)
                count++;
        }
        return (count >= 2);
    }

    if (strcmp(missao, "Dominar todas as bordas do mapa") == 0) {
        return strcmp(mapa[0].cor, "azul") == 0 &&
               strcmp(mapa[tamanho - 1].cor, "azul") == 0;
    }

    if (strcmp(missao, "Reduzir qualquer território inimigo a 0 tropas") == 0) {
        for (int i = 0; i < tamanho; i++) {
            if (mapa[i].tropas == 0)
                return 1;
        }
    }

    return 0; // caso nenhuma regra seja atendida
}

/*
    Libera memória alocada
*/
void liberarMemoria(Territorio* mapa, char* missao) {
    free(mapa);
    free(missao);
}

/*
    MAIN
*/
int main() {
    srand(time(NULL));

    int total;
    printf("Quantos territórios deseja criar? ");
    scanf("%d", &total);
    getchar();

    // aloca territórios
    Territorio* mapa = (Territorio*) malloc(total * sizeof(Territorio));

    // cadastro dos territórios
    for (int i = 0; i < total; i++) {
        printf("\nCadastro do território %d:\n", i);

        printf("Nome: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Cor: ");
        scanf(" %s", mapa[i].cor);

        printf("Tropas: ");
        scanf("%d", &mapa[i].tropas);
    }

    exibirMapa(mapa, total);

    /*
        Missões pré-definidas
    */
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas vermelhas",
        "Controlar 2 territórios grandes",
        "Dominar todas as bordas do mapa",
        "Reduzir qualquer território inimigo a 0 tropas"
    };

    int totalMissoes = 5;

    /*
        Armazena missão do jogador dinamicamente
    */
    char* missaoJogador = (char*) malloc(100 * sizeof(char));
    atribuirMissao(missaoJogador, missoes, totalMissoes);
    exibirMissao(missaoJogador);

    /*
        Loop principal do jogo
    */
    int opc;
    do {
        printf("\n===== MENU =====\n");
        printf("1 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha: ");
        scanf("%d", &opc);

        if (opc == 1) {
            int at, def;

            exibirMapa(mapa, total);

            printf("Escolha o território atacante: ");
            scanf("%d", &at);

            printf("Escolha o território defensor: ");
            scanf("%d", &def);

            if (at < 0 || at >= total || def < 0 || def >= total) {
                printf("IDs inválidos!\n");
                continue;
            }

            if (strcmp(mapa[at].cor, mapa[def].cor) == 0) {
                printf("Não pode atacar território da mesma cor!\n");
                continue;
            }

            atacar(&mapa[at], &mapa[def]);
            exibirMapa(mapa, total);

            // Verifica missão após cada turno
            if (verificarMissao(missaoJogador, mapa, total)) {
                printf("\n=========================\n");
                printf(" MISSÃO CUMPRIDA! VOCÊ VENCEU!\n");
                printf("=========================\n");
                break;
            }
        }

    } while (opc != 0);

    liberarMemoria(mapa, missaoJogador);
    printf("\nMemória liberada. Fim do jogo.\n");

    return 0;
}
