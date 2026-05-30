#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

int num[MAX];
int memo[MAX];
int n;

int lis(int i) {
    if (memo[i] != -1)
        return memo[i];

    if (i == 0) {
        memo[i] = 1;
        return 1;
    }

    int melhor = 1;
    for (int j = 0; j < i; j++) {
        if (num[j] < num[i]) {
            int candidato = lis(j) + 1;
            if (candidato > melhor)
                melhor = candidato;
        }
    }

    memo[i] = melhor;
    return memo[i];
}

int main(void) {
    printf("Digite o tamanho da sequencia: ");
    scanf("%d", &n);

    printf("Digite os %d elementos: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &num[i]);
        memo[i] = -1;
    }

    int resposta = 0;
    for (int i = 0; i < n; i++) {
        int val = lis(i);
        if (val > resposta)
            resposta = val;
    }

    printf("Tamanho da LIS = %d\n", resposta);
    return 0;
}