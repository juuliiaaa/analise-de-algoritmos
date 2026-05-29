#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    float valor;
    struct No *prox;
} No;

No *inserir_ordenado(No *lista, float valor) {
    No *novo = (No *)malloc(sizeof(No));
    novo->valor = valor;
    novo->prox = NULL;

    if (lista == NULL || valor < lista->valor) {
        novo->prox = lista;
        return novo;
    }

    No *atual = lista;
    while (atual->prox != NULL && atual->prox->valor <= valor) {
        atual = atual->prox;
    }
    novo->prox = atual->prox;
    atual->prox = novo;
    return lista;
}

void bucket_sort(float A[], int n) {
    No **B = (No **)calloc(n, sizeof(No *));

    for (int i = 0; i < n; i++) {
        int idx = (int)(n * A[i]);
        B[idx] = inserir_ordenado(B[idx], A[i]);
    }

    int k = 0;
    for (int i = 0; i < n; i++) {
        No *atual = B[i];
        while (atual != NULL) {
            A[k++] = atual->valor;
            No *tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
    }

    free(B);
}

void imprimir(float A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%.2f ", A[i]);
    }
    printf("\n");
}

int main() {
    float A[] = {0.78f, 0.17f, 0.39f, 0.26f, 0.72f,
                 0.94f, 0.21f, 0.12f, 0.23f, 0.68f};
    int n = sizeof(A) / sizeof(A[0]);

    printf("Antes: ");
    imprimir(A, n);

    bucket_sort(A, n);

    printf("Depois: ");
    imprimir(A, n);

    return 0;
}