#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int main(void) {
    int num[MAX];
    int dp[MAX];
    int n;

    printf("Digite o tamanho da sequencia: ");
    scanf("%d", &n);

    printf("Digite os %d elementos: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &num[i]);

    for (int i = 0; i < n; i++)
        dp[i] = 1;

    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (num[j] < num[i]) {
                int candidato = dp[j] + 1;
                if (candidato > dp[i])
                    dp[i] = candidato;
            }
        }
    }

    int resposta = 0;
    for (int i = 0; i < n; i++) {
        if (dp[i] > resposta)
            resposta = dp[i];
    }

    printf("Tamanho da LIS = %d\n", resposta);
    return 0;
}