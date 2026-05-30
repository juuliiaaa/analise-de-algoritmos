#include <stdio.h>
#include <stdlib.h>

int *memo;

int fib(int n) {
    if (memo[n] != -1)
        return memo[n];

    if (n == 0 || n == 1)
        memo[n] = n;
    else
        memo[n] = fib(n - 1) + fib(n - 2);

    return memo[n];
}

int main(void) {
    int n;
    printf("Digite n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Por favor, digite um numero inteiro maior ou igual a zero.\n");
        return 1;
    }

    memo = (int *)malloc((n + 1) * sizeof(int));
    if (memo == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    for (int i = 0; i <= n; i++)
        memo[i] = -1;

    printf("fib(%d) = %d\n", n, fib(n));

    free(memo);
    return 0;
}