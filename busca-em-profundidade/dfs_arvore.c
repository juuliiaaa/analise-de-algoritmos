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
    printf("Visitando vértice %d (pai: %d)\n", u, pai[u]);

    No *w = g->adj[u].cabeca;
    while (w != NULL) {
        if (!visitado[w->vertice]) {
            pai[w->vertice] = u;
            DFS_visita(g, w->vertice);
        }
        w = w->proximo;
    }
}

void DFS(Grafo *g) {
    for (int u = 0; u < g->V; u++) {
        visitado[u] = 0;
        pai[u] = -1;
    }

    for (int u = 0; u < g->V; u++) {
        if (!visitado[u]) {
            pai[u] = u;
            DFS_visita(g, u);
        }
    }
}

int imprimirCaminho(int origem, int destino) {
    if (pai[destino] == -1) {
        printf("Não existe caminho de %d para %d\n", origem, destino);
        return 0;
    }

    int caminho[MAX_VERTICES];
    int tamanho = 0;
    int atual = destino;

    while (atual != pai[atual]) {
        caminho[tamanho++] = atual;
        atual = pai[atual];
        if (tamanho > MAX_VERTICES) break;
    }
    caminho[tamanho++] = atual;

    if (atual != origem) {
        printf("Não existe caminho de %d para %d\n", origem, destino);
        return 0;
    }

    printf("Caminho de %d até %d: ", origem, destino);
    for (int i = tamanho - 1; i >= 0; i--) {
        printf("%d", caminho[i]);
        if (i > 0) printf(" -> ");
    }
    printf("\n");
    return 1;
}

int main(void) {
    Grafo *g = criarGrafo(6);
    adicionarAresta(g, 0, 1);
    adicionarAresta(g, 0, 4);
    adicionarAresta(g, 4, 1);
    adicionarAresta(g, 4, 5);
    adicionarAresta(g, 5, 1);
    adicionarAresta(g, 2, 0);
    adicionarAresta(g, 2, 4);
    adicionarAresta(g, 2, 3);
    adicionarAresta(g, 3, 4);
    adicionarAresta(g, 3, 5);

    printf("DFS com Arborescência\n");
    DFS(g);

    printf("\nVetor pai[]\n");
    for (int i = 0; i < g->V; i++)
        printf("pai[%d] = %d\n", i, pai[i]);

    printf("\nCaminhos\n");
    imprimirCaminho(0, 5);
    imprimirCaminho(0, 1);
    imprimirCaminho(2, 3);

    return 0;
}
