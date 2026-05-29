#include <stdio.h>

void shell_sort(int A[], int n) {
    int h = 1;
    while (h <= n / 90) {
        h = 3 * h + 1;
    }

    while (h > 0) {
        for (int j = h; j < n; j++) {
            int chave = A[j];
            int i = j;
            while (i >= h && A[i - h] > chave) {
                A[i] = A[i - h];
                i -= h;
            }
            A[i] = chave;
        }
        h = h / 3;
    }
}

void imprimir(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {53, 32, 21, 12, 40, 16};
    int n = sizeof(A) / sizeof(A[0]);

    printf("Antes: ");
    imprimir(A, n);

    shell_sort(A, n);

    printf("Depois: ");
    imprimir(A, n);

    return 0;
}