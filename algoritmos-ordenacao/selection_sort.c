#include <stdio.h>

void troca(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void selection_sort(int A[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (A[j] < A[min]) {
                min = j;
            }
        }
        troca(&A[i], &A[min]);
    }
}

void imprimir(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {10, 20, 5, 40, 4};
    int n = sizeof(A) / sizeof(A[0]);

    printf("Antes: ");
    imprimir(A, n);

    selection_sort(A, n);

    printf("Depois: ");
    imprimir(A, n);

    return 0;
}