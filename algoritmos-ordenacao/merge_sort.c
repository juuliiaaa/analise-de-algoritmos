#include <stdio.h>
#include <stdlib.h>

void merge(int A[], int p, int q, int r) {
    int n = r - p + 1;
    int *B = (int *)malloc(n * sizeof(int));
    
    if (B == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o vetor auxiliar B.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = p; i <= q; i++) {
        B[i - p] = A[i];
    }
    for (int j = q + 1; j <= r; j++) {
        B[r - (j - (q + 1)) - p] = A[j];
    }

    int i = 0;           
    int j = n - 1;       

    for (int k = p; k <= r; k++) {
        if (B[i] <= B[j]) {
            A[k] = B[i];
            i++;
        } else {
            A[k] = B[j];
            j--;
        }
    }

    free(B);
}

void merge_sort(int A[], int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        merge_sort(A, p, q);
        merge_sort(A, q + 1, r);
        merge(A, p, q, r);
    }
}

void imprimir(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {4, 6, 7, 3, 5, 1, 2, 8};
    int n = sizeof(A) / sizeof(A[0]);

    printf("Antes: ");
    imprimir(A, n);

    merge_sort(A, 0, n - 1);

    printf("Depois: ");
    imprimir(A, n);

    return 0;
}