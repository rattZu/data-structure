#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

// ================= STRUCT =================
// ✔ OK: estrutura correta, atende o projeto
typedef struct {
    int id;
    float peso;
    float volume;
    char origem[50];
    char destino[50];
} Container;

// ================= VARIÁVEIS =================
// ❌ NÃO OK: está usando vetor
// 👉 projeto pede lista duplamente encadeada
// ✔ Solução: criar struct com ponteiros (prox e ant)
Container containers[MAX];
int total = 0;

// ================= FUNÇÕES =================

// Cadastro
// ⚠ PARCIALMENTE OK
// ✔ Funciona
// ❌ Não verifica limite do array
// ❌ Não valida dados
// ✔ Solução: if(total < MAX) e validar valores
void cadastrar() {
    Container c;

    printf("\nID: ");
    scanf("%d", &c.id);

    printf("Peso: ");
    scanf("%f", &c.peso);

    printf("Volume: ");
    scanf("%f", &c.volume);

    printf("Origem: ");
    scanf("%s", c.origem); // ❌ não aceita espaço
    // ✔ solução: usar fgets()

    printf("Destino: ");
    scanf("%s", c.destino); // ❌ não aceita espaço

    containers[total++] = c; // ❌ pode estourar MAX
    printf("Container cadastrado!\n");
}

// Listar
// ✔ OK: funciona corretamente
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
// ✔ OK: atende o requisito
// ⚠ simples (bubble sort), mas serve
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
// ✔ OK: mesma lógica, funciona
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
// ⚠ PARCIALMENTE OK
// ✔ cálculo funciona
// ❌ não usa portos (ABB não existe ainda)
// ❌ não usa fila (transporte real)
// ✔ solução: integrar com fila e árvore depois
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
// ✔ OK: funcionalidade extra (bom ter)
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
// ⚠ PARCIALMENTE OK
// ✔ funciona
// ❌ não verifica limite do array (pode estourar)
// ✔ solução: colocar if(total < MAX)
void carregar() {
    FILE *f = fopen("containers.txt", "r");

    if (!f) return;

    while (fscanf(f, "%d %f %f %s %s",
                  &containers[total].id,
                  &containers[total].peso,
                  &containers[total].volume,
                  containers[total].origem,
                  containers[total].destino) != EOF) {
        total++; // ❌ pode passar do MAX
    }

    fclose(f);
}

// ================= MENU =================
// ✔ OK: menu funcional
// ❌ falta opções das estruturas (fila, pilha, etc)
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

// ================= O QUE FALTA FAZER =================
//
// ❌ Criar LISTA DUPLAMENTE ENCADEADA (obrigatório)
// ❌ Criar FILA (transporte de containers)
// ❌ Criar PILHA (reprocessamento)
// ❌ Criar ÁRVORE BINÁRIA (portos)
// ❌ Criar HISTÓRICO de embarques
//
// ⚠ Ajustes necessários:
// - validar dados (peso, volume)
// - evitar estouro do array (MAX)
// - melhorar leitura de strings (fgets)
//
// ✔ Resumo:
// Código funciona, mas está incompleto para o projeto