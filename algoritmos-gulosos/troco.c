#include <stdio.h>
#include <stdlib.h>

void ordena_decrescente(int *moedas, int m) {
    for (int i = 0; i < m - 1; i++) {
        for (int j = 0; j < m - 1 - i; j++) {
            if (moedas[j] < moedas[j + 1]) {
                int tmp = moedas[j];
                moedas[j] = moedas[j + 1];
                moedas[j + 1] = tmp;
            }
        }
    }
}

int troco(int *C, int m, int valor, int *S, int *tamanho_S) {
    ordena_decrescente(C, m);

    int soma = 0;
    *tamanho_S = 0;
    int c_disponivel[m];
    int c_tam = m;

    for (int i = 0; i < m; i++)
        c_disponivel[i] = C[i];

    int i = 0;
    while (i < c_tam && soma < valor) {
        int m_atual = c_disponivel[i];
        if (soma + m_atual <= valor) {
            soma += m_atual;
            S[(*tamanho_S)++] = m_atual;
        } else {
            i++;
        }
    }

    return (soma == valor) ? 1 : 0;
}

int main(void) {
    {
        int moedas[] = {1, 2, 5};
        int m = 3, valor = 12;
        int S[100], tam = 0;

        printf("Exemplo 1: valor=%d, moedas={1,2,5}\n", valor);
        if (troco(moedas, m, valor, S, &tam)) {
            printf("Solucao encontrada com %d moeda(s): ", tam);
            for (int i = 0; i < tam; i++) printf("%d ", S[i]);
            printf("\n\n");
        } else {
            printf("Nao existe solucao.\n\n");
        }
    }

    {
        int moedas[] = {1, 4, 6};
        int m = 3, valor = 8;
        int S[100], tam = 0;

        printf("Exemplo 2: valor=%d, moedas={1,4,6}\n", valor);
        if (troco(moedas, m, valor, S, &tam)) {
            printf("Solucao gulosa com %d moeda(s): ", tam);
            for (int i = 0; i < tam; i++) printf("%d ", S[i]);
            printf("\n");
            printf("(Atencao: solucao otima seria {4,4} com apenas 2 moedas)\n\n");
        } else {
            printf("Nao existe solucao.\n\n");
        }
    }

    return 0;
}
