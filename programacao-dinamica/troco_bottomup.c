#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main(void) {
    int T, n;

    printf("Digite o valor do troco T: ");
    scanf("%d", &T);

    printf("Digite o numero de tipos de moeda: ");
    scanf("%d", &n);

    int *M = (int *)malloc(n * sizeof(int));

    printf("Digite os valores das moedas: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &M[i]);

    int *troco = (int *)malloc((T + 1) * sizeof(int));

    for (int i = 1; i <= T; i++)
        troco[i] = INT_MAX;

    troco[0] = 0;

    for (int i = 1; i <= T; i++) {
        for (int j = 0; j < n; j++) {
            if (i >= M[j] && troco[i - M[j]] != INT_MAX) {
                int candidato = troco[i - M[j]] + 1;
                if (candidato < troco[i])
                    troco[i] = candidato;
            }
        }
    }

    if (troco[T] == INT_MAX)
        printf("Não é possível dar o troco de %d com as moedas fornecidas.\n", T);
    else
        printf("Mínimo de moedas para o troco %d = %d\n", T, troco[T]);

    free(M);
    free(troco);
    return 0;
}