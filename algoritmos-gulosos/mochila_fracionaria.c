#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int    id;
    double valor;
    double peso;
    double ratio;
} Item;

int cmp_ratio(const void *a, const void *b) {
    const Item *ia = (const Item *)a;
    const Item *ib = (const Item *)b;
    if (ib->ratio > ia->ratio) return  1;
    if (ib->ratio < ia->ratio) return -1;
    return 0;
}

double mochila_fracionaria(Item *itens, int n, double W, double *x) {
    for (int i = 0; i < n; i++) {
        itens[i].ratio = itens[i].valor / itens[i].peso;
        x[i] = 0.0;
    }
    qsort(itens, n, sizeof(Item), cmp_ratio);

    double valor_total = 0.0;
    
    int i = 1; 
    
    while (i <= n && W > 0) {
        if (itens[i - 1].peso <= W) {
            x[i - 1] = 1.0; 
            W = W - itens[i - 1].peso;
            valor_total += itens[i - 1].valor;
        } 
        else {
            x[i - 1] = W / itens[i - 1].peso;
            valor_total += x[i - 1] * itens[i - 1].valor;
            W = 0;
        }
        i = i + 1;
    }

    return valor_total;
}

int main(void) {
    Item itens[] = {
        {1,  60.0, 10.0, 0.0},
        {2, 100.0, 20.0, 0.0},
        {3, 120.0, 30.0, 0.0}
    };
    int n = 3;
    double W = 50.0;
    double x[3];

    double total = mochila_fracionaria(itens, n, W, x);

    printf("Mochila Fracionaria (capacidade=%.1f)\n", W);
    printf("%-6s %-10s %-10s %-12s %-10s\n",
           "Item", "Valor", "Peso", "Valor/Peso", "Fracao");
    for (int i = 0; i < n; i++) {
        printf("%-6d %-10.2f %-10.2f %-12.2f %-10.4f\n",
               itens[i].id, itens[i].valor, itens[i].peso,
               itens[i].ratio, x[i]);
    }
    printf("\nValor total obtido: $%.2f\n", total);

    return 0;
}