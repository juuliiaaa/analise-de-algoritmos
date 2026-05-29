#include <stdio.h>

void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void desce_heap(int A[], int n, int i) {
    while (2 * i <= n) {
        int f = 2 * i; /* Filho esquerdo */
        
        if (f < n && A[(f + 1) - 1] > A[f - 1]) {
            f = f + 1;
        }
        
        if (A[i - 1] < A[f - 1]) {
            troca(&A[i - 1], &A[f - 1]);
            i = f;
        } else {
            break;
        }
    }
}

void constroi_heap(int A[], int n) {
    for (int i = n / 2; i >= 1; i--) {
        desce_heap(A, n, i);
    }
}

void heap_sort(int A[], int n) {
    constroi_heap(A, n);
    for (int i = n; i >= 2; i--) {
        troca(&A[1 - 1], &A[i - 1]);
        desce_heap(A, i - 1, 1);
    }
}

void imprimir(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {20, 15, 17, -2, 8, 11, 3, 9, 29, 1};
    int n = sizeof(A) / sizeof(A[0]);

    printf("Antes: ");
    imprimir(A, n);

    heap_sort(A, n);

    printf("Depois: ");
    imprimir(A, n);

    return 0;
}