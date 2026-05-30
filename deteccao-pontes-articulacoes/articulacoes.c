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
int eh_articulacao[MAX_V];
int tempo;
int V;

void inicializar_grafo(int vertices) {
    V = vertices;
    for (int i = 0; i < V; i++) {
        adj[i].cabeca = NULL;
        eh_articulacao[i] = 0;
    }
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

void dfs_articulacoes(int v) {
    tempo++;
    pre[v] = tempo;
    low[v] = pre[v];
    int filhos = 0;

    No *atual = adj[v].cabeca;
    while (atual != NULL) {
        int w = atual->dest;

        if (pre[w] == -1) {
            filhos++;
            pai[w] = v;
            dfs_articulacoes(w);

            if (low[w] < low[v]) low[v] = low[w];

            if (pai[v] != v && low[w] >= pre[v]) {
                eh_articulacao[v] = 1;
            }
        } 
        else if (w != pai[v]) {
            if (pre[w] < low[v]) low[v] = pre[w];
        }
        atual = atual->prox;
    }

    if (pai[v] == v && filhos > 1) {
        eh_articulacao[v] = 1;
    }
}

void analisar_articulacoes() {
    tempo = 0;
    for (int i = 0; i < V; i++) {
        pre[i] = -1;
        pai[i] = -1;
        low[i] = -1;
    }

    for (int i = 0; i < V; i++) {
        if (pre[i] == -1) {
            pai[i] = i;
            dfs_articulacoes(i);
        }
    }

    printf("Analise de Pontos de Articulação\n");
    int encontrou = 0;
    for (int i = 0; i < V; i++) {
        if (eh_articulacao[i]) {
            printf("Vértice de corte (Articulação) detectado: Vértice %d\n", i);
            encontrou = 1;
        }
    }
    if (!encontrou) printf("O grafo não possui pontos de articulação.\n");
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

    analisar_articulacoes();
    return 0;
}