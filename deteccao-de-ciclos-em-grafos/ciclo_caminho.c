#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 100

typedef struct No {
    int vertice;
    struct No *proximo;
} No;

typedef struct {
    int V;
    No *adj[MAX_VERTICES];
} Grafo;

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

void visita(Grafo *g, int v, int visitado[]) {
    visitado[v] = 1;
    No *w = g->adj[v];
    while (w != NULL) {
        if (!visitado[w->vertice])
            visita(g, w->vertice, visitado);
        w = w->proximo;
    }
}

int tem_caminho(Grafo *g, int s, int t) {
    int visitado[MAX_VERTICES];
    memset(visitado, 0, sizeof(visitado));
    visita(g, s, visitado);
    return visitado[t];
}

int tem_ciclo(Grafo *g) {
    for (int v = 0; v < g->V; v++) {
        No *w = g->adj[v];
        while (w != NULL) {
            if (tem_caminho(g, w->vertice, v)) {
                printf("Ciclo detectado: arco %d->%d e caminho de %d de volta a %d\n",
                       v, w->vertice, w->vertice, v);
                return 1;
            }
            w = w->proximo;
        }
    }
    return 0;
}

int main(void) {
    printf("Detecção de Ciclos via tem-caminho\n\n");

    printf("Grafo com ciclo\n");
    Grafo *g1 = criarGrafo(6);
    adicionarAresta(g1, 2, 1);
    adicionarAresta(g1, 1, 5);
    adicionarAresta(g1, 5, 3);
    adicionarAresta(g1, 3, 4);
    adicionarAresta(g1, 4, 2);
    adicionarAresta(g1, 0, 2);
    adicionarAresta(g1, 0, 5);
    printf("Resultado: %s\n\n", tem_ciclo(g1) ? "SIM, possui ciclo" : "NÃO possui ciclo");

    printf("Grafo sem ciclo\n");
    Grafo *g2 = criarGrafo(6);
    adicionarAresta(g2, 0, 2);
    adicionarAresta(g2, 0, 5);
    adicionarAresta(g2, 2, 1);
    adicionarAresta(g2, 5, 3);
    adicionarAresta(g2, 3, 4);
    printf("Resultado: %s\n", tem_ciclo(g2) ? "SIM, possui ciclo" : "NÃO possui ciclo");

    return 0;
}