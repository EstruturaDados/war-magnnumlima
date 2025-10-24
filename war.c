#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// 
typedef struct {
    char nome[30];   
    char cor[10];    
    int tropas;      
} Territorio;

// FUNÇÕES 

// cadastrar os territórios
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

// exibir todos os territórios
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

// ataque entre dois territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n=== ATAQUE ENTRE TERRITÓRIOS ===\n");
    printf("%s (%s) atacando %s (%s)\n",
           atacante->nome, atacante->cor, defensor->nome, defensor->cor);

    // dados (1 a 6)
    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("Dado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    // resultado do ataque
    if (dadoAtacante > dadoDefensor) {
        printf("➡ O atacante venceu o combate!\n");

        
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = atacante->tropas / 2; // metade das tropas passam
        atacante->tropas -= defensor->tropas / 2; // atacante perde um pouco também

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

// -- PROGRAMA PRINCIPAL --
int main() {
    srand(time(NULL)); // inicializa gerador de números aleatórios

    int n;
    printf("=== SISTEMA WAR ESTRUTURADO ===\n");
    printf("Quantos territórios deseja cadastrar? ");
    scanf("%d", &n);


    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memória!\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, n);

    // Exibição inicial
    exibirTerritorios(mapa, n);

    // ataque
    int atacante, defensor;
    printf("\nEscolha o território atacante (1 a %d): ", n);
    scanf("%d", &atacante);
    printf("Escolha o território defensor (1 a %d): ", n);
    scanf("%d", &defensor);

    // Validação das escolhas
    if (atacante < 1 || atacante > n || defensor < 1 || defensor > n || atacante == defensor) {
        printf("Escolhas inválidas! O ataque não pode ser realizado.\n");
    } else if (strcmp(mapa[atacante - 1].cor, mapa[defensor - 1].cor) == 0) {
        printf("Não é possível atacar um território do mesmo exército!\n");
    } else {
        atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
    }

    // Exibição dos resultados
    exibirTerritorios(mapa, n);


    printf("\nFim da simulação.\n");
    return 0;
}