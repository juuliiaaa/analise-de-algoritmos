#include <stdio.h>
#include <stdlib.h>

void counting_sort(int A[], int B[], int n, int k) {
    int *C = (int *)calloc(k + 1, sizeof(int));
    
    if (C == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória para o vetor de contagem C.\n");
        exit(EXIT_FAILURE);
    }

    for (int j = 0; j < n; j++) {
        C[A[j]]++;
    }

    for (int i = 2; i <= k; i++) {
        C[i] = C[i] + C[i - 1];
    }

    for (int j = n - 1; j >= 0; j--) {
        B[C[A[j]] - 1] = A[j];
        C[A[j]]--;
    }

    free(C);
}

void imprimir(int A[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main() {
    int A[] = {2, 5, 3, 1, 2, 3, 1, 5, 3, 1};
    int n = sizeof(A) / sizeof(A[0]);
    int k = 5; 
    int B[10];

    printf("Antes: ");
    imprimir(A, n);

    counting_sort(A, B, n, k);

    printf("Depois: ");
    imprimir(B, n);

    return 0;
}