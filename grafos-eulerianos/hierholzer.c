#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXV 100

int adj[MAXV][MAXV];
int V;

typedef struct {
    int dados[MAXV * MAXV];
    int topo;
} Pilha;

void pilha_init(Pilha *p)          { p->topo = -1; }
int  pilha_vazia(Pilha *p)         { return p->topo < 0; }
void pilha_empilha(Pilha *p, int v){ p->dados[++(p->topo)] = v; }
int  pilha_desempilha(Pilha *p)    { return p->dados[(p->topo)--]; }
int  pilha_topo(Pilha *p)          { return p->dados[p->topo]; }

typedef struct {
    int *dados;
    int tamanho;
    int capacidade;
} Trilha;

void trilha_init(Trilha *t) {
    t->capacidade = 16;
    t->tamanho = 0;
    t->dados = malloc(t->capacidade * sizeof(int));
}

void trilha_insere(Trilha *t, int v) {
    if (t->tamanho == t->capacidade) {
        t->capacidade *= 2;
        t->dados = realloc(t->dados, t->capacidade * sizeof(int));
    }
    t->dados[t->tamanho++] = v;
}

void trilha_free(Trilha *t) { free(t->dados); }

void hierholzer(int v_inicio)
{
    Pilha  pilha;
    Trilha trilha;

    pilha_init(&pilha);
    trilha_init(&trilha);

    pilha_empilha(&pilha, v_inicio);

    while (!pilha_vazia(&pilha)) {
        int u = pilha_topo(&pilha);

        int achou = 0;
        for (int w = 0; w < V; w++) {
            if (adj[u][w] > 0) {
                adj[u][w]--;
                adj[w][u]--;
                /* Adiciona w à pilha */
                pilha_empilha(&pilha, w);
                achou = 1;
                break;
            }
        }

        if (!achou) {
            pilha_desempilha(&pilha);
            trilha_insere(&trilha, u);
        }
    }

    printf("Trilha euleriana (Hierholzer): ");
    for (int i = trilha.tamanho - 1; i >= 0; i--) {
        printf("%d", trilha.dados[i]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");

    trilha_free(&trilha);
}

int escolhe_vertice_inicial(void)
{
    int impares[MAXV], n_impares = 0;
    for (int u = 0; u < V; u++) {
        int grau = 0;
        for (int w = 0; w < V; w++) grau += adj[u][w];
        if (grau % 2 != 0) impares[n_impares++] = u;
    }

    if (n_impares > 2) {
        printf("Não existe trilha de Euler (mais de 2 vértices de grau ímpar).\n");
        return -1;
    }

    if (n_impares == 0) {
        return 0;
    }

    return impares[0];
}

int main(void) {
    V = 6;
    memset(adj, 0, sizeof(adj));

    adj[0][1]++; adj[1][0]++;
    adj[1][2]++; adj[2][1]++;
    adj[2][3]++; adj[3][2]++;
    adj[3][0]++; adj[0][3]++;
    adj[1][4]++; adj[4][1]++;
    adj[4][2]++; adj[2][4]++;
    adj[2][5]++; adj[5][2]++;
    adj[5][1]++; adj[1][5]++;
    adj[4][5]++; adj[5][4]++;

    int v0 = escolhe_vertice_inicial();
    if (v0 == -1) return 1;

    hierholzer(v0);

    return 0;
}