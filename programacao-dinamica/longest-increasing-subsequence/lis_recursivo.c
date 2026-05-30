#include <stdio.h>

#define MAX 1000

int num[MAX];
int n;

int lis(int i) {
    if (i == 0)
        return 1;

    int melhor = 1;

    for (int j = 0; j < i; j++) {
        if (num[j] < num[i]) {
            int candidato = lis(j) + 1;
            if (candidato > melhor)
                melhor = candidato;
        }
    }
    return melhor;
}

int main(void) {
    printf("Digite o tamanho da sequencia: ");
    if (scanf("%d", &n) != 1 || n <= 0 || n > MAX) {
        printf("Tamanho invalido.\n");
        return 1;
    }

    printf("Digite os %d elementos: ", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &num[i]);

    int resposta = 0;
    for (int i = 0; i < n; i++) {
        int val = lis(i);
        if (val > resposta)
            resposta = val;
    }

    printf("Tamanho da LIS = %d\n", resposta);
    return 0;
}