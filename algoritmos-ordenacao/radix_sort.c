#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void counting_sort_digito(int A[], int n, int exp) {
    int *B = (int *)malloc(n * sizeof(int));
    int C[10];
    memset(C, 0, sizeof(C));

    for (int j = 0; j < n; j++) {
        int digito = (A[j] / exp) % 10;
        C[digito]++;
    }

    for (int i = 1; i < 10; i++) {
        C[i] += C[i - 1];
    }

    for (int j = n - 1; j >= 0; j--) {
        int digito = (A[j] / exp) % 10;
        B[C[digito] - 1] = A[j];
        C[digito]--;
    }

    for (int i = 0; i < n; i++) {
        A[i] = B[i];
    }

    free(B);
}

void radix_sort(int A[], int n, int d) {
    int exp = 1;
    for (int i = 0; i < d; i++) {
        counting_sort_digito(A, n, exp);
        exp *= 10;
    }
}

void imprimir(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {329, 457, 657, 839, 436, 720, 355};
    int n = sizeof(A) / sizeof(A[0]);
    int d = 3;

    printf("Antes: ");
    imprimir(A, n);

    radix_sort(A, n, d);

    printf("Depois: ");
    imprimir(A, n);

    return 0;
}