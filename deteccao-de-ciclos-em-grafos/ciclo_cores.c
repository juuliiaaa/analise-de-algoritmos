#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100

#define BRANCO 0
#define CINZA  1
#define PRETO  2

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

const char *nomeCor(int cor) {
    if (cor == BRANCO) return "BRANCO";
    if (cor == CINZA)  return "CINZA";
    return "PRETO";
}

int tem_arco_de_retorno(Grafo *g, int v, int cor[]) {
    cor[v] = CINZA;
    printf("Vértice %d -> %s\n", v, nomeCor(cor[v]));

    No *w = g->adj[v];
    while (w != NULL) {
        if (cor[w->vertice] == CINZA) {
            printf("Ciclo detectado: arco %d->%d (vértice %d é CINZA)\n",
                   v, w->vertice, w->vertice);
            return 1;
        }
        if (cor[w->vertice] == BRANCO) {
            if (tem_arco_de_retorno(g, w->vertice, cor))
                return 1;
        }
        w = w->proximo;
    }

    cor[v] = PRETO;
    printf("Vértice %d -> %s\n", v, nomeCor(cor[v]));
    return 0;
}

int tem_ciclo(Grafo *g) {
    int cor[MAX_VERTICES];

    for (int v = 0; v < g->V; v++)
        cor[v] = BRANCO;

    for (int v = 0; v < g->V; v++) {
        if (cor[v] == BRANCO) {
            if (tem_arco_de_retorno(g, v, cor))
                return 1;
        }
    }
    return 0;
}

int main(void) {
    printf("Detecção de Ciclos via Coloração\n\n");

    printf("Grafo dos slides\n");
    Grafo *g1 = criarGrafo(6);
    adicionarAresta(g1, 0, 1);
    adicionarAresta(g1, 0, 3);
    adicionarAresta(g1, 1, 4);
    adicionarAresta(g1, 4, 3);
    adicionarAresta(g1, 3, 1);
    adicionarAresta(g1, 0, 2);
    adicionarAresta(g1, 2, 5);
    adicionarAresta(g1, 5, 4);
    printf("Resultado: %s\n\n", tem_ciclo(g1) ? "SIM, possui ciclo" : "NÃO possui ciclo");

    printf("Grafo sem ciclo\n");
    Grafo *g2 = criarGrafo(4);
    adicionarAresta(g2, 0, 1);
    adicionarAresta(g2, 0, 2);
    adicionarAresta(g2, 1, 3);
    adicionarAresta(g2, 2, 3);
    printf("Resultado: %s\n\n", tem_ciclo(g2) ? "SIM, possui ciclo" : "NÃO possui ciclo");

    printf("Grafo com ciclo (0->1->2->0)\n");
    Grafo *g3 = criarGrafo(3);
    adicionarAresta(g3, 0, 1);
    adicionarAresta(g3, 1, 2);
    adicionarAresta(g3, 2, 0);
    printf("Resultado: %s\n", tem_ciclo(g3) ? "SIM, possui ciclo" : "NÃO possui ciclo");

    return 0;
}