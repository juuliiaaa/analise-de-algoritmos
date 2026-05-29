#include <stdio.h>

void insertion_sort(int A[], int n) {
    for (int j = 1; j < n; j++) {
        int chave = A[j];
        int i = j - 1;
        while (i >= 0 && A[i] > chave) {
            A[i + 1] = A[i];
            i--;
        }
        A[i + 1] = chave;
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

    insertion_sort(A, n);

    printf("Depois: ");
    imprimir(A, n);

    return 0;
}
