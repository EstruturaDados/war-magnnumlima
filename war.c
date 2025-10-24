#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


// ESTRUTURA DE DADOS

typedef struct {
    char nome[30];   // Nome do território
    char cor[10];    // Cor do exército
    int tropas;      // Quantidade de tropas
} Territorio;


// FUNÇÕES AUXILIARES


// cadastrar territórios
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do território %d:\n", i + 1);

        printf("Digite o nome do território: ");
        scanf(" %[^\n]", mapa[i].nome);

        printf("Digite a cor do exército: ");
        scanf(" %[^\n]", mapa[i].cor);

        printf("Digite a quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
    }
}

// exibir territórios
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== TERRITÓRIOS ATUAIS ===\n");
    for (int i = 0; i < n; i++) {
        printf("\nTerritório %d:\n", i + 1);
        printf("Nome: %s\n", mapa[i].nome);
        printf("Cor: %s\n", mapa[i].cor);
        printf("Tropas: %d\n", mapa[i].tropas);
        printf("-------------------------\n");
    }
}

// ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== ATAQUE ENTRE TERRITÓRIOS ===\n");
    printf("%s (%s) atacando %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("➡ O atacante venceu o combate!\n");
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2;
        atacante->tropas -= defensor->tropas / 2;
        printf("O território %s agora pertence ao exército %s!\n",
               defensor->nome, defensor->cor);
    } else {
        printf("❌ O defensor resistiu ao ataque!\n");
        if (atacante->tropas > 1)
            atacante->tropas -= 1;
        else
            printf("O atacante está com tropas mínimas!\n");
    }
}

 
// MISSÕES


// missão aleatória a um jogador
void atribuirMissao(char* destino, char* missoes[], int totalMissoes) {
    int indice = rand() % totalMissoes; // Sorteia uma missão
    strcpy(destino, missoes[indice]);   // Copia para o jogador
}

// missão de um jogador
void exibirMissao(char* missao, int jogador) {
    printf("\n🎯 Missão do Jogador %d: %s\n", jogador, missao);
}

// Verificar missao
int verificarMissao(char* missao, Territorio* mapa, int tamanho, char* corJogador) {
    int contador = 0;

    if (strstr(missao, "Conquistar 3 territórios")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0)
                contador++;
        }
        if (contador >= 3)
            return 1; // Missão cumprida
    } else if (strstr(missao, "Eliminar cor vermelha")) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, "vermelho") == 0)
                return 0; // Ainda existe exército vermelho
        }
        return 1;
    }

    return 0; // Missão ainda não foi cumprida
}


// PROGRAMA PRINCIPAL

int main() {
    srand(time(NULL)); // Inicializa gerador de números aleatórios

    int n;
    printf("=== SISTEMA WAR ESTRUTURADO COM MISSÕES ===\n");
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);

    // dinâmica dos territórios
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória para o mapa!\n");
        return 1;
    }

    // Cadastro de territórios
    cadastrarTerritorios(mapa, n);
    exibirTerritorios(mapa, n);

    // missões disponíveis
    char* missoes[] = {
        "Conquistar 3 territórios seguidos",
        "Eliminar todas as tropas da cor vermelha",
        "Controlar metade do mapa",
        "Manter pelo menos 5 territórios",
        "Ter um total de 20 tropas no mapa"
    };
    int totalMissoes = 5;

    // missões dos jogadores
    char* missaoJogador1 = (char*) malloc(100 * sizeof(char));
    char* missaoJogador2 = (char*) malloc(100 * sizeof(char));

    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    // Exibe as missões
    exibirMissao(missaoJogador1, 1);
    exibirMissao(missaoJogador2, 2);

    // turnos de ataque
    int atacante, defensor;
    char continuar = 's';
    int vencedor = 0;

    while (continuar == 's' && !vencedor) {
        exibirTerritorios(mapa, n);

        printf("\nEscolha o território atacante (1 a %d): ", n);
        scanf("%d", &atacante);
        printf("Escolha o território defensor (1 a %d): ", n);
        scanf("%d", &defensor);

        if (atacante < 1 || atacante > n || defensor < 1 || defensor > n || atacante == defensor) {
            printf("Escolhas inválidas! O ataque não pode ser realizado.\n");
        } else if (strcmp(mapa[atacante - 1].cor, mapa[defensor - 1].cor) == 0) {
            printf("Não é possível atacar um território do mesmo exército!\n");
        } else {
            atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
        }

        // missões após o ataque
        if (verificarMissao(missaoJogador1, mapa, n, "azul")) {
            printf("\n🎉 O Jogador 1 (azul) cumpriu sua missão: %s\n", missaoJogador1);
            vencedor = 1;
        } else if (verificarMissao(missaoJogador2, mapa, n, "verde")) {
            printf("\n🎉 O Jogador 2 (verde) cumpriu sua missão: %s\n", missaoJogador2);
            vencedor = 2;
        }

        if (!vencedor) {
            printf("\nDeseja continuar o jogo? (s/n): ");
            scanf(" %c", &continuar);
        }
    }

    if (vencedor)
        printf("\n🏆 Parabéns! O Jogador %d venceu o jogo!\n", vencedor);
    else
        printf("\nJogo encerrado sem vencedor.\n");

    printf("\nFim da simulação.\n");
    return 0;
}
