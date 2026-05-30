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

int tem_ciclo_visita(Grafo *g, int u, int visitado[], int esta_na_pilha[]) {
    visitado[u] = 1;
    esta_na_pilha[u] = 1;

    No *w = g->adj[u];
    while (w != NULL) {
        if (!visitado[w->vertice]) {
            if (tem_ciclo_visita(g, w->vertice, visitado, esta_na_pilha))
                return 1;
        } else if (esta_na_pilha[w->vertice]) {
            printf("Ciclo detectado: arco %d->%d (vértice %d está na pilha)\n",
                   u, w->vertice, w->vertice);
            return 1;
        }
        w = w->proximo;
    }

    esta_na_pilha[u] = 0;
    return 0;
}

int tem_ciclo(Grafo *g) {
    int visitado[MAX_VERTICES]    = {0};
    int esta_na_pilha[MAX_VERTICES] = {0};

    for (int v = 0; v < g->V; v++) {
        if (!visitado[v]) {
            if (tem_ciclo_visita(g, v, visitado, esta_na_pilha))
                return 1;
        }
    }
    return 0;
}

int main(void) {
    printf("Detecção de Ciclos via Pilha de Recursão\n\n");

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

    printf("Grafo maior com ciclo\n");
    Grafo *g3 = criarGrafo(6);
    adicionarAresta(g3, 0, 2);
    adicionarAresta(g3, 0, 5);
    adicionarAresta(g3, 2, 1);
    adicionarAresta(g3, 1, 5);
    adicionarAresta(g3, 5, 3);
    adicionarAresta(g3, 3, 4);
    adicionarAresta(g3, 4, 2);
    printf("Resultado: %s\n", tem_ciclo(g3) ? "SIM, possui ciclo" : "NÃO possui ciclo");

    return 0;
}