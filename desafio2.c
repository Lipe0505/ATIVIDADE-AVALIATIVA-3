/*
 * Desafio 2
 * Inverte uma string utilizando uma pilha dinâmica.
 *
 * Restrições atendidas:
 *  - Sem funções prontas para inverter string (sem strrev).
 *  - Sem vetor auxiliar para armazenar a string invertida.
 *  - Manipulação apenas via operações da pilha (push/pop).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ─── Estrutura da Pilha ─────────────────────────────────────────── */

typedef struct No {
    char    dado;
    struct No *proximo;
} No;

typedef struct {
    No *topo;
} Pilha;

/* ─── Operações da Pilha ─────────────────────────────────────────── */

void inicializar(Pilha *p) {
    p->topo = NULL;
}

int isEmpty(Pilha *p) {
    return p->topo == NULL;
}

void push(Pilha *p, char c) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) {
        printf("Erro: memória insuficiente.\n");
        exit(1);
    }
    novo->dado    = c;
    novo->proximo = p->topo;
    p->topo       = novo;
}

char pop(Pilha *p) {
    if (isEmpty(p)) return '\0';
    No   *removido = p->topo;
    char  valor    = removido->dado;
    p->topo        = removido->proximo;
    free(removido);
    return valor;
}

/* ─── Main ───────────────────────────────────────────────────────── */

int main(void) {
    char original[256];
    Pilha p;

    printf("Digite a string: ");
    scanf("%255[^\n]", original);

    inicializar(&p);

    /* Empilha cada caractere da string original */
    for (int i = 0; original[i] != '\0'; i++) {
        push(&p, original[i]);
    }

    /* Desempilha imprimindo — a ordem LIFO produz a string invertida */
    printf("String invertida: ");
    while (!isEmpty(&p)) {
        printf("%c", pop(&p));
    }
    printf("\n");

    return 0;
}
