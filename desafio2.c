#include <stdio.h>
#include <stdlib.h>

typedef struct Documento {
    int id;
    int paginas;
    int prioridade;
} Documento;

typedef struct No {
    Documento   dado;
    struct No  *proximo;
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

void enqueue(Fila *f, Documento d) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) {
        printf("Erro: memória insuficiente.\n");
        exit(1);
    }
    novo->dado     = d;
    novo->proximo  = NULL;

    if (isEmpty(f) || d.prioridade > f->fim->dado.prioridade) {
        if (isEmpty(f)) f->inicio = novo;
        else            f->fim->proximo = novo;
        f->fim = novo;
        return;
    }

    No *anterior = NULL;
    No *atual    = f->inicio;

    while (atual != NULL && atual->dado.prioridade <= d.prioridade) {
        anterior = atual;
        atual    = atual->proximo;
    }

    novo->proximo = atual;
    if (anterior == NULL) {
        f->inicio = novo;
    } else {
        anterior->proximo = novo;
    }
    if (atual == NULL) {
        f->fim = novo;
    }
}

Documento dequeue(Fila *f) {
    if (isEmpty(f)) {
        printf("Erro: fila vazia.\n");
        exit(1);
    }
    No        *removido = f->inicio;
    Documento  valor    = removido->dado;
    f->inicio           = removido->proximo;
    if (f->inicio == NULL) f->fim = NULL;
    free(removido);
    return valor;
}

int main(void) {
    Fila fila;
    inicializar(&fila);

    int n;
    printf("Quantos documentos? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        Documento d;
        printf("\n--- Documento %d ---\n", i + 1);
        printf("ID: ");
        scanf("%d", &d.id);
        printf("Número de páginas: ");
        scanf("%d", &d.paginas);
        printf("Prioridade (menor = mais urgente): ");
        scanf("%d", &d.prioridade);
        enqueue(&fila, d);
    }

    printf("\n========== ORDEM DE IMPRESSÃO ==========\n");
    printf("%-5s %-10s %-10s %-12s\n",
           "Ord.", "Doc. ID", "Páginas", "Prioridade");
    printf("----------------------------------------\n");

    int ordem = 1;
    while (!isEmpty(&fila)) {
        Documento d = dequeue(&fila);
        printf("%-5d %-10d %-10d %-12d\n",
               ordem++, d.id, d.paginas, d.prioridade);
    }

    return 0;
}
