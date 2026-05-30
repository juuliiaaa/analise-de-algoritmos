#include <stdio.h>

int fib(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int anterior2 = 0;
    int anterior1 = 1;
    int atual = 0;

    for (int i = 2; i <= n; i++) {
        atual = anterior1 + anterior2;
        anterior2 = anterior1;
        anterior1 = atual;
    }

    return atual;
}

int main(void) {
    int n;
    printf("Digite n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Entrada invalida.\n");
        return 1;
    }
    
    printf("fib(%d) = %d\n", n, fib(n));
    return 0;
}