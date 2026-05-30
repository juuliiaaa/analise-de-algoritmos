#include <stdio.h>

int fib(int n) {
    if (n == 0 || n == 1)
        return n;
    else
        return fib(n - 1) + fib(n - 2);
}

int main(void) {
    int n;
    printf("Digite n: ");
    scanf("%d", &n);
    printf("fib(%d) = %d\n", n, fib(n));
    return 0;
}
