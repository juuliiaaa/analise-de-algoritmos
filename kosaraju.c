#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    int destino;
    struct No *prox;
} No;

typedef struct {
    int V;
    No **adj;
} Grafo;

Grafo *criarGrafo(int V) {
    Grafo *g = (Grafo *)malloc(sizeof(Grafo));
    g->V = V;
    g->adj = (No **)calloc(V, sizeof(No *));
    return g;
}

void adicionarAresta(Grafo *g, int u, int v) {
    No *novo = (No *)malloc(sizeof(No));
    novo->destino = v;
    novo->prox = g->adj[u];
    g->adj[u] = novo;
}

void liberarGrafo(Grafo *g) {
    for (int i = 0; i < g->V; i++) {
        No *cur = g->adj[i];
        while (cur) {
            No *tmp = cur;
            cur = cur->prox;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}

Grafo *transporGrafo(Grafo *g) {
    Grafo *gt = criarGrafo(g->V);
    for (int u = 0; u < g->V; u++) {
        for (No *cur = g->adj[u]; cur != NULL; cur = cur->prox) {
            adicionarAresta(gt, cur->destino, u);
        }
    }
    return gt;
}

void dfs1(Grafo *g, int u, int *visitado, int *pilha, int *topo) {
    visitado[u] = 1;
    for (No *cur = g->adj[u]; cur != NULL; cur = cur->prox) {
        if (!visitado[cur->destino]) {
            dfs1(g, cur->destino, visitado, pilha, topo);
        }
    }
    pilha[(*topo)++] = u;
}

void dfs2(Grafo *gt, int u, int *visitado, int *componente, int numComp) {
    visitado[u] = 1;
    componente[u] = numComp;
    for (No *cur = gt->adj[u]; cur != NULL; cur = cur->prox) {
        if (!visitado[cur->destino]) {
            dfs2(gt, cur->destino, visitado, componente, numComp);
        }
    }
}

void kosaraju(Grafo *g, const char **nomeVertices) {
    int V = g->V;

    int *visitado = (int *)calloc(V, sizeof(int));
    int *pilha    = (int *)malloc(V * sizeof(int));
    int  topo     = 0;

    for (int v = 0; v < V; v++) {
        if (!visitado[v]) {
            dfs1(g, v, visitado, pilha, &topo);
        }
    }

    Grafo *gt = transporGrafo(g);

    memset(visitado, 0, V * sizeof(int));
    int *componente = (int *)malloc(V * sizeof(int));
    int  numComp    = 0;

    for (int i = topo - 1; i >= 0; i--) {
        int v = pilha[i];
        if (!visitado[v]) {
            dfs2(gt, v, visitado, componente, numComp);
            numComp++;
        }
    }

    printf("Número de Componentes Fortemente Conexos: %d\n\n", numComp);
    for (int c = 0; c < numComp; c++) {
        printf("SCC %d: { ", c + 1);
        for (int v = 0; v < V; v++) {
            if (componente[v] == c) {
                if (nomeVertices) {
                    printf("%s ", nomeVertices[v]);
                } else {
                    printf("%d ", v);
                }
            }
        }
        printf("}\n");
    }

    free(visitado);
    free(pilha);
    free(componente);
    liberarGrafo(gt);
}

int main(void) {

    const int V = 8;
    const char *nomes[] = {"a", "b", "c", "d", "e", "f", "g", "h"};

    Grafo *g = criarGrafo(V);

    adicionarAresta(g, 0, 1);
    adicionarAresta(g, 0, 4);
    adicionarAresta(g, 1, 4);
    adicionarAresta(g, 1, 2);
    adicionarAresta(g, 2, 3);
    adicionarAresta(g, 3, 2);
    adicionarAresta(g, 3, 7);
    adicionarAresta(g, 4, 0);
    adicionarAresta(g, 4, 5);
    adicionarAresta(g, 5, 6);
    adicionarAresta(g, 6, 5);
    adicionarAresta(g, 6, 7);

    printf("Algoritmo de Kosaraju\n\n");
    kosaraju(g, nomes);

    liberarGrafo(g);
    return 0;
}