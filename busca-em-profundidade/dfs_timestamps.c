#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

typedef struct No {
    int vertice;
    struct No *proximo;
} No;

typedef struct {
    No *cabeca;
} ListaAdj;

typedef struct {
    int V;
    ListaAdj *adj;
} Grafo;

int visitado[MAX_VERTICES];
int pai[MAX_VERTICES];
int d[MAX_VERTICES];
int f[MAX_VERTICES];
int tempo;

Grafo *criarGrafo(int V) {
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));
    g->V = V;
    g->adj = (ListaAdj *)malloc(V * sizeof(ListaAdj));
    for (int i = 0; i < V; i++)
        g->adj[i].cabeca = NULL;
    return g;
}

void adicionarAresta(Grafo *g, int u, int w) {
    No *novo = (No *)malloc(sizeof(No));
    novo->vertice = w;
    novo->proximo = g->adj[u].cabeca;
    g->adj[u].cabeca = novo;
}

void DFS_visita(Grafo *g, int u) {
    visitado[u] = 1;
    tempo = tempo + 1;
    d[u] = tempo;
    printf("Descoberto vértice %d  (d[%d] = %d)\n", u, u, d[u]);

    No *w = g->adj[u].cabeca;
    while (w != NULL) {
        if (!visitado[w->vertice]) {
            pai[w->vertice] = u;
            DFS_visita(g, w->vertice);
        }
        w = w->proximo;
    }

    tempo = tempo + 1;
    f[u] = tempo;
    printf("Finalizado  vértice %d  (f[%d] = %d)\n", u, u, f[u]);
}

void DFS(Grafo *g) {
    for (int u = 0; u < g->V; u++) {
        visitado[u] = 0;
        d[u] = -1;
        f[u] = -1;
        pai[u] = -1;
    }
    tempo = 0;

    for (int u = 0; u < g->V; u++) {
        if (!visitado[u]) {
            pai[u] = u;
            DFS_visita(g, u);
        }
    }
}

int ehDescendente(int v, int u) {
    /* v descendente de u: d[v] > d[u] && f[v] < f[u] */
    return (d[v] > d[u] && f[v] < f[u]);
}

int main(void) {
    Grafo *g = criarGrafo(8);
    adicionarAresta(g, 0, 5);
    adicionarAresta(g, 5, 2);
    adicionarAresta(g, 2, 1);
    adicionarAresta(g, 5, 7);
    adicionarAresta(g, 3, 4);
    adicionarAresta(g, 3, 6);

    printf("DFS com Timestamps\n\n");
    DFS(g);

    printf("\nTabela de intervalos [d[v], f[v]]\n");
    printf("%-10s %-15s %-15s %-10s\n", "Vértice", "Descoberta d[]", "Finalização f[]", "Pai");
    for (int i = 0; i < g->V; i++)
        printf("%-10d %-15d %-15d %-10d\n", i, d[i], f[i], pai[i]);

    printf("\n--- Verificação de descendência ---\n");
    printf("2 é descendente de 0? %s\n", ehDescendente(2, 0) ? "Sim" : "Não");
    printf("7 é descendente de 5? %s\n", ehDescendente(7, 5) ? "Sim" : "Não");
    printf("4 é descendente de 3? %s\n", ehDescendente(4, 3) ? "Sim" : "Não");
    printf("0 é descendente de 3? %s\n", ehDescendente(0, 3) ? "Sim" : "Não");

    return 0;
}