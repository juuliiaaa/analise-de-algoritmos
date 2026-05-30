#include <stdio.h>
#include <stdlib.h>

#define MAX_V 20

typedef struct No {
    int dest;
    struct No *prox;
} No;

typedef struct {
    No *cabeca;
} ListaAdj;

ListaAdj adj[MAX_V];
int pre[MAX_V];
int low[MAX_V];
int pai[MAX_V];
int tempo;
int V;

void inicializar_grafo(int vertices) {
    V = vertices;
    for (int i = 0; i < V; i++)
        adj[i].cabeca = NULL;
}

void adicionar_aresta(int u, int v) {
    No *novo1 = (No *)malloc(sizeof(No));
    novo1->dest = v;
    novo1->prox = NULL;
    if (adj[u].cabeca == NULL) adj[u].cabeca = novo1;
    else {
        No *atual = adj[u].cabeca;
        while (atual->prox != NULL) atual = atual->prox;
        atual->prox = novo1;
    }
    No *novo2 = (No *)malloc(sizeof(No));
    novo2->dest = u;
    novo2->prox = NULL;
    if (adj[v].cabeca == NULL) adj[v].cabeca = novo2;
    else {
        No *atual = adj[v].cabeca;
        while (atual->prox != NULL) atual = atual->prox;
        atual->prox = novo2;
    }
}

void dfs_pontes(int v) {
    tempo++;
    pre[v] = tempo;
    low[v] = pre[v];

    No *atual = adj[v].cabeca;
    while (atual != NULL) {
        int w = atual->dest;

        if (pre[w] == -1) {
            pai[w] = v;
            dfs_pontes(w);

            if (low[w] < low[v]) low[v] = low[w];

            if (low[w] > pre[v]) {
                printf("  Ponte encontrada: (%d, %d)\n", v, w);
            }
        } 
        else if (w != pai[v]) {
            if (pre[w] < low[v]) low[v] = pre[w];
        }
        atual = atual->prox;
    }
}

void detectar_pontes() {
    tempo = 0;
    for (int i = 0; i < V; i++) {
        pre[i] = -1;
        pai[i] = -1;
        low[i] = -1;
    }

    printf("Analise de Pontes\n");
    for (int i = 0; i < V; i++) {
        if (pre[i] == -1) {
            pai[i] = i;
            dfs_pontes(i);
        }
    }
}

int main(void) {

    inicializar_grafo(6);

    adicionar_aresta(0, 1);
    adicionar_aresta(0, 2);
    adicionar_aresta(1, 2);
    adicionar_aresta(2, 3);
    adicionar_aresta(3, 4);
    adicionar_aresta(3, 5);
    adicionar_aresta(4, 5);

    detectar_pontes();

    printf("Tabela de Verificacao (pre / low):\n");
    for (int i = 0; i < V; i++) {
        printf("  Vertice %d -> pre: %d | low: %d\n", i, pre[i], low[i]);
    }
    return 0;
}