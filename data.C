#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// ================= STRUCT =================
typedef struct {
    int id;
    float peso;
    float volume;
    char origem[50];
    char destino[50];
} Container;

// ================= VARIÁVEIS =================
Container containers[MAX];
int total = 0;

// ================= FUNÇÕES =================

// Cadastro
void cadastrar() {
    Container c;

    printf("\nID: ");
    scanf("%d", &c.id);

    printf("Peso: ");
    scanf("%f", &c.peso);

    printf("Volume: ");
    scanf("%f", &c.volume);

    printf("Origem: ");
    scanf("%s", c.origem);

    printf("Destino: ");
    scanf("%s", c.destino);

    containers[total++] = c;
    printf("Container cadastrado!\n");
}

// Listar
void listar() {
    printf("\n=== LISTA DE CONTAINERS ===\n");
    for (int i = 0; i < total; i++) {
        printf("ID:%d | Peso:%.2f | Volume:%.2f | %s -> %s\n",
               containers[i].id,
               containers[i].peso,
               containers[i].volume,
               containers[i].origem,
               containers[i].destino);
    }
}

// Ordenar por peso
void ordenarPeso() {
    for (int i = 0; i < total-1; i++) {
        for (int j = 0; j < total-i-1; j++) {
            if (containers[j].peso > containers[j+1].peso) {
                Container temp = containers[j];
                containers[j] = containers[j+1];
                containers[j+1] = temp;
            }
        }
    }
    printf("Ordenado por peso!\n");
}

// Ordenar por volume
void ordenarVolume() {
    for (int i = 0; i < total-1; i++) {
        for (int j = 0; j < total-i-1; j++) {
            if (containers[j].volume > containers[j+1].volume) {
                Container temp = containers[j];
                containers[j] = containers[j+1];
                containers[j+1] = temp;
            }
        }
    }
    printf("Ordenado por volume!\n");
}

// Simulação de custo e tempo
void calcularRota() {
    int distancia;
    float custo, tempo;

    printf("\nDistância da rota (km): ");
    scanf("%d", &distancia);

    for (int i = 0; i < total; i++) {
        custo = containers[i].peso * 0.5 + distancia * 0.2;
        tempo = distancia / 60.0;

        printf("\nContainer %d:", containers[i].id);
        printf("\nCusto estimado: %.2f", custo);
        printf("\nTempo estimado: %.2f horas\n", tempo);
    }
}

// Salvar em arquivo
void salvar() {
    FILE *f = fopen("containers.txt", "w");

    for (int i = 0; i < total; i++) {
        fprintf(f, "%d %.2f %.2f %s %s\n",
                containers[i].id,
                containers[i].peso,
                containers[i].volume,
                containers[i].origem,
                containers[i].destino);
    }

    fclose(f);
    printf("Dados salvos!\n");
}

// Carregar arquivo
void carregar() {
    FILE *f = fopen("containers.txt", "r");

    if (!f) return;

    while (fscanf(f, "%d %f %f %s %s",
                  &containers[total].id,
                  &containers[total].peso,
                  &containers[total].volume,
                  containers[total].origem,
                  containers[total].destino) != EOF) {
        total++;
    }

    fclose(f);
}

// ================= MENU =================
void menu() {
    int op;

    do {
        printf("\n===== SISTEMA DE ROTEAMENTO =====\n");
        printf("1. Cadastrar container\n");
        printf("2. Listar containers\n");
        printf("3. Ordenar por peso\n");
        printf("4. Ordenar por volume\n");
        printf("5. Simular rota (custo/tempo)\n");
        printf("6. Salvar dados\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &op);

        switch (op) {
            case 1: cadastrar(); break;
            case 2: listar(); break;
            case 3: ordenarPeso(); break;
            case 4: ordenarVolume(); break;
            case 5: calcularRota(); break;
            case 6: salvar(); break;
        }

    } while (op != 0);
}

int main() {
    carregar();
    menu();
    return 0;
}