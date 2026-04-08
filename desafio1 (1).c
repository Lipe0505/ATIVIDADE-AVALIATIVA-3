#include <stdio.h>
#include <stdlib.h>

typedef struct Cliente {
    int id;
    int tempoAtendimento;
} Cliente;

typedef struct No {
    Cliente         dado;
    struct No      *proximo;
} No;

typedef struct {
    No *inicio;
    No *fim;
} Fila;

void inicializar(Fila *f) {
    f->inicio = NULL;
    f->fim    = NULL;
}

int isEmpty(Fila *f) {
    return f->inicio == NULL;
}

void enqueue(Fila *f, Cliente c) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) {
        printf("Erro: memória insuficiente.\n");
        exit(1);
    }
    novo->dado     = c;
    novo->proximo  = NULL;

    if (isEmpty(f)) {
        f->inicio = novo;
        f->fim    = novo;
    } else {
        f->fim->proximo = novo;
        f->fim          = novo;
    }
}

Cliente dequeue(Fila *f) {
    if (isEmpty(f)) {
        printf("Erro: fila vazia.\n");
        exit(1);
    }
    No      *removido = f->inicio;
    Cliente  valor    = removido->dado;
    f->inicio         = removido->proximo;
    if (f->inicio == NULL) f->fim = NULL;
    free(removido);
    return valor;
}

int main(void) {
    Fila fila;
    inicializar(&fila);

    int n;
    printf("Quantos clientes? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Cliente c;
        printf("\n--- Cliente %d ---\n", i + 1);
        printf("ID: ");
        scanf("%d", &c.id);
        printf("Tempo de atendimento (min): ");
        scanf("%d", &c.tempoAtendimento);
        enqueue(&fila, c);
    }

    printf("\n========== SIMULAÇÃO DE ATENDIMENTO ==========\n");
    printf("%-10s %-20s %-15s\n", "Cliente", "Tempo Atendimento", "Tempo Espera");
    printf("----------------------------------------------\n");

    int tempoEspera = 0;

    while (!isEmpty(&fila)) {
        Cliente c = dequeue(&fila);
        printf("%-10d %-20d %-15d\n", c.id, c.tempoAtendimento, tempoEspera);
        tempoEspera += c.tempoAtendimento;
    }

    printf("----------------------------------------------\n");
    printf("Tempo total de atendimento: %d minutos\n", tempoEspera);

    return 0;
}
