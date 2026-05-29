#include <stdio.h>

void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int particiona(int A[], int p, int r) {
    int x = A[r];
    int i = p - 1;
    for (int j = p; j <= r - 1; j++) {
        if (A[j] <= x) {
            i++;
            troca(&A[i], &A[j]);
        }
    }
    troca(&A[i + 1], &A[r]);
    return i + 1;
}

void quick_sort(int A[], int p, int r) {
    if (p < r) {
        int q = particiona(A, p, r);
        quick_sort(A, p, q - 1);
        quick_sort(A, q + 1, r);
    }
}

void imprimir(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {2, 8, 7, 1, 3, 5, 6, 4};
    int n = sizeof(A) / sizeof(A[0]);

    printf("Antes: ");
    imprimir(A, n);

    quick_sort(A, 0, n - 1);

    printf("Depois: ");
    imprimir(A, n);

    return 0;
}
