#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct No {
    int vertice;
    struct No *proximo;
} No;

typedef struct {
    int V;
    No *adj[MAX_VERTICES];
} Grafo;

int d[MAX_VERTICES];
int f[MAX_VERTICES];
int tempo;

Grafo *criarGrafo(int V) {
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));
    g->V = V;
    for (int i = 0; i < V; i++)
        g->adj[i] = NULL;
    return g;
}

void adicionarAresta(Grafo *g, int u, int w) {
    No *novo = (No *)malloc(sizeof(No));
    novo->vertice = w;
    novo->proximo = g->adj[u];
    g->adj[u] = novo;
}

int tem_arco_de_retorno(Grafo *g, int v) {
    d[v] = tempo;
    tempo++;

    No *w = g->adj[v];
    while (w != NULL) {
        if (d[w->vertice] == -1) {
            if (tem_arco_de_retorno(g, w->vertice))
                return 1;
        } else if (f[w->vertice] == -1) {
            printf("Arco de retorno: %d -> %d  (d[%d]=%d, f[%d] ainda aberto)\n",
                   v, w->vertice, w->vertice, d[w->vertice], w->vertice);
            return 1;
        }
        w = w->proximo;
    }

    f[v] = tempo;
    tempo++;
    return 0;
}

int tem_ciclo(Grafo *g) {
    tempo = 0;
    for (int v = 0; v < g->V; v++) {
        d[v] = -1;
        f[v] = -1;
    }

    for (int v = 0; v < g->V; v++) {
        if (d[v] == -1) {
            if (tem_arco_de_retorno(g, v))
                return 1;
        }
    }
    return 0;
}

int main(void) {
    printf("Detecção de Ciclos via Arco de Retorno (timestamps)\n\n");

    printf("Grafo com ciclo\n");
    Grafo *g1 = criarGrafo(4);
    adicionarAresta(g1, 0, 1);
    adicionarAresta(g1, 1, 2);
    adicionarAresta(g1, 2, 0);
    adicionarAresta(g1, 2, 3);
    printf("Resultado: %s\n\n", tem_ciclo(g1) ? "SIM, possui ciclo" : "NÃO possui ciclo");

    printf("Grafo sem ciclo\n");
    Grafo *g2 = criarGrafo(4);
    adicionarAresta(g2, 0, 1);
    adicionarAresta(g2, 1, 2);
    adicionarAresta(g2, 2, 3);
    printf("Resultado: %s\n\n", tem_ciclo(g2) ? "SIM, possui ciclo" : "NÃO possui ciclo");

    printf("Grafo com ciclo\n");
    Grafo *g3 = criarGrafo(8);
    adicionarAresta(g3, 0, 5);
    adicionarAresta(g3, 5, 2);
    adicionarAresta(g3, 2, 1);
    adicionarAresta(g3, 5, 7);
    adicionarAresta(g3, 2, 4);
    adicionarAresta(g3, 4, 2);
    adicionarAresta(g3, 3, 6);
    printf("Resultado: %s\n", tem_ciclo(g3) ? "SIM, possui ciclo" : "NÃO possui ciclo");

    return 0;
}