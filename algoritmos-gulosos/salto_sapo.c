#include <stdio.h>
#include <stdlib.h>

void salto_sapo(int *p, int n, int delta, int *u, int *tamanho_u) {
    *tamanho_u = 0;
    
    u[(*tamanho_u)++] = p[1 - 1]; 
    
    int ultima_pos = p[1 - 1];

    for (int i = 2; i <= n; i++) {
        if (p[i - 1] - ultima_pos > delta) {
            ultima_pos = p[(i - 1) - 1];
            u[(*tamanho_u)++] = p[(i - 1) - 1];
        }
    }

    u[(*tamanho_u)++] = p[n - 1];
}

int main(void) {
    int p[] = {1, 2, 3, 5, 6, 7};
    int n = 6, delta = 2;
    int u[100], tam = 0;

    salto_sapo(p, n, delta, u, &tam);

    printf("Salto do Sapo: delta=%d\n", delta);
    printf("Sequencia de pedras visitadas: ");
    for (int i = 0; i < tam; i++) printf("%d ", u[i]);
    printf("\nNumero total de posicoes na sequencia: %d\n", tam);

    return 0;
}