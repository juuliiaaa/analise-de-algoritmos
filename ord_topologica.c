#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 20

#define BRANCO 0
#define CINZA  1
#define PRETO  2

typedef struct No {
    int        vertice;
    struct No *prox;
} No;

typedef struct {
    No *cabeca;
} ListaAdj;

typedef struct {
    int dados[MAX_VERTICES];
    int topo;
} Pilha;

ListaAdj grafo[MAX_VERTICES];
int      n_vertices;

int cor[MAX_VERTICES];
int tempo_inicio[MAX_VERTICES];
int tempo_fim[MAX_VERTICES];
int tempo;

char *nomes[MAX_VERTICES];

Pilha pilha;

void pilha_inicializar(Pilha *p) {
    p->topo = -1;
}

void pilha_empilhar(Pilha *p, int v) {
    p->dados[++(p->topo)] = v;
}

int pilha_desempilhar(Pilha *p) {
    return p->dados[(p->topo)--];
}

int pilha_vazia(Pilha *p) {
    return p->topo == -1;
}

void inicializar_grafo(int n) {
    n_vertices = n;
    for (int i = 0; i < n; i++)
        grafo[i].cabeca = NULL;
}

void adicionar_arco(int u, int v) {
    No *novo = (No *)malloc(sizeof(No));
    novo->vertice = v;
    novo->prox    = grafo[u].cabeca;
    grafo[u].cabeca = novo;
}

void dfs_visita(int u) {
    tempo++;
    tempo_inicio[u] = tempo;
    cor[u] = CINZA;

    No *adj = grafo[u].cabeca;
    while (adj != NULL) {
        int v = adj->vertice;
        if (cor[v] == BRANCO)
            dfs_visita(v);
        adj = adj->prox;
    }

    cor[u] = PRETO;
    tempo++;
    tempo_fim[u] = tempo;
    pilha_empilhar(&pilha, u);
}

void ordenacao_topologica(void) {
    for (int u = 0; u < n_vertices; u++)
        cor[u] = BRANCO;

    tempo = 0;
    pilha_inicializar(&pilha);

    for (int u = 0; u < n_vertices; u++)
        if (cor[u] == BRANCO)
            dfs_visita(u);
}

int main(void) {

    nomes[0] = "camisa";  nomes[1] = "gravata"; nomes[2] = "paletó";
    nomes[3] = "cinto";   nomes[4] = "calças";  nomes[5] = "cuecas";
    nomes[6] = "sapatos"; nomes[7] = "meias";   nomes[8] = "relógio";

    inicializar_grafo(9);

    adicionar_arco(0, 1);
    adicionar_arco(0, 3);
    adicionar_arco(1, 2);
    adicionar_arco(3, 2);
    adicionar_arco(5, 4);
    adicionar_arco(5, 6);
    adicionar_arco(4, 6);
    adicionar_arco(7, 6);

    ordenacao_topologica();

    printf("Tempos de inicio e fim (d/f):\n");
    for (int i = 0; i < n_vertices; i++)
        printf("  %-10s  %2d/%2d\n", nomes[i], tempo_inicio[i], tempo_fim[i]);

    printf("\nOrdenacao topologica:\n  ");
    while (!pilha_vazia(&pilha)) {
        int v = pilha_desempilhar(&pilha);
        printf("%s", nomes[v]);
        if (!pilha_vazia(&pilha)) printf(" -> ");
    }
    printf("\n");

    return 0;
}