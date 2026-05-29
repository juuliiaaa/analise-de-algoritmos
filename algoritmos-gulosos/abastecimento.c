#include <stdio.h>
#include <stdlib.h>

void caminhoneiro(int *p, int n, int C, int *S, int *tamanho_S) {
    *tamanho_S = 0;
    int ultima_parada = p[0];

    for (int i = 1; i < n; i++) {
        if (p[i] - ultima_parada > C) {
            ultima_parada = p[i - 1];
            S[(*tamanho_S)++] = i - 1;
        }
    }
}

int main(void) {

    int p[] = {0, 100, 200, 350, 450, 600, 650, 700};
    int n = 8;
    int C = 200;
    int S[100], tam = 0;

    caminhoneiro(p, n, C, S, &tam);

    printf("Selecao de Paradas\n");
    printf("Posicoes: ");
    for (int i = 0; i < n; i++) printf("%d ", p[i]);
    printf("\nAutonomia: %d km\n", C);
    printf("Partida: km %d | Destino: km %d\n\n", p[0], p[n - 1]);

    if (tam == 0) {
        printf("Nenhuma parada necessaria.\n");
    } else {
        printf("Paradas necessarias (%d posto(s)):\n", tam);
        for (int i = 0; i < tam; i++) {
            printf("  Posto no km %d (indice %d)\n", p[S[i]], S[i]);
        }
    }

    return 0;
}