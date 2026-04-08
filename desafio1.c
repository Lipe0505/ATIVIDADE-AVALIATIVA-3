/*
 * Desafio 1
 * Verifica se uma expressão com (, ), {, }, [ e ] está balanceada.
 * Utiliza pilha dinâmica implementada com struct e alocação dinâmica.
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

/* Inicializa a pilha com topo NULL */
void inicializar(Pilha *p) {
    p->topo = NULL;
}

/* Retorna 1 se a pilha estiver vazia, 0 caso contrário */
int isEmpty(Pilha *p) {
    return p->topo == NULL;
}

/* Empilha um caractere */
void push(Pilha *p, char c) {
    No *novo = (No *)malloc(sizeof(No));
    if (!novo) {
        printf("Erro: memória insuficiente.\n");
        exit(1);
    }
    novo->dado     = c;
    novo->proximo  = p->topo;
    p->topo        = novo;
}

/* Desempilha e retorna o caractere do topo.
   Retorna '\0' se a pilha estiver vazia. */
char pop(Pilha *p) {
    if (isEmpty(p)) return '\0';
    No   *removido = p->topo;
    char  valor    = removido->dado;
    p->topo        = removido->proximo;
    free(removido);
    return valor;
}

/* Libera todos os nós restantes na pilha */
void liberar(Pilha *p) {
    while (!isEmpty(p)) pop(p);
}

/* ─── Lógica de Balanceamento ────────────────────────────────────── */

/* Retorna 1 se 'fechamento' corresponde ao 'abertura', 0 caso contrário */
int corresponde(char abertura, char fechamento) {
    return (abertura == '(' && fechamento == ')') ||
           (abertura == '[' && fechamento == ']') ||
           (abertura == '{' && fechamento == '}');
}

/* Retorna 1 se a expressão for balanceada, 0 caso contrário */
int balanceada(const char *expr) {
    Pilha p;
    inicializar(&p);

    for (int i = 0; expr[i] != '\0'; i++) {
        char c = expr[i];

        if (c == '(' || c == '[' || c == '{') {
            push(&p, c);
        } else if (c == ')' || c == ']' || c == '}') {
            if (isEmpty(&p) || !corresponde(pop(&p), c)) {
                liberar(&p);
                return 0;
            }
        }
        /* ignora outros caracteres */
    }

    int resultado = isEmpty(&p); /* válido apenas se a pilha esvaziou */
    liberar(&p);
    return resultado;
}

/* ─── Main ───────────────────────────────────────────────────────── */

int main(void) {
    char expr[256];

    printf("Digite a expressão: ");
    scanf("%255s", expr);

    if (balanceada(expr)) {
        printf("Expressão VÁLIDA: os símbolos estão balanceados.\n");
    } else {
        printf("Expressão INVÁLIDA: os símbolos NÃO estão balanceados.\n");
    }

    return 0;
}
