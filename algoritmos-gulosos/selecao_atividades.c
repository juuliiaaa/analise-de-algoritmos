#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    int s;
    int t;
} Atividade;

int cmp_termino(const void *a, const void *b) {
    const Atividade *a_ptr = (const Atividade *)a;
    const Atividade *b_ptr = (const Atividade *)b;
    return a_ptr->t - b_ptr->t;
}

void seleciona_atividades(Atividade *ativ, int n, int *A, int *tamanho_A) {
    qsort(ativ, n, sizeof(Atividade), cmp_termino);

    *tamanho_A = 0;
    
    A[(*tamanho_A)++] = 1; 
    
    int j = 1; 

    for (int i = 2; i <= n; i++) {
        if (ativ[i - 1].s >= ativ[j - 1].t) {
            /* Linha 6-7: então A <- A U {i}; j <- i */
            A[(*tamanho_A)++] = i;
            j = i;
        }
    }
}

int main(void) {
    Atividade ativ[] = {
        { 1,  0,  6}, { 2,  1,  4}, { 3,  3,  5}, { 4,  3,  8},
        { 5,  4,  7}, { 6,  5,  9}, { 7,  6, 10}, { 8,  8, 11},
        { 9,  8, 12}, {10,  2, 13}, {11, 12, 14}
    };
    int n = 11;
    int A[100], tam = 0;

    seleciona_atividades(ativ, n, A, &tam);

    printf("Selecao de Atividades\n");
    printf("Atividades selecionadas (%d no total):\n", tam);
    for (int i = 0; i < tam; i++) {
        int idx = A[i] - 1;
        printf("  Atividade %d  [%d, %d)\n",
               ativ[idx].id, ativ[idx].s, ativ[idx].t);
    }

    return 0;
}