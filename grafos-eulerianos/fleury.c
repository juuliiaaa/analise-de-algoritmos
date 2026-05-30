#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXV 100
#define BRANCO 0
#define CINZA  1
#define PRETO  2

int adj[MAXV][MAXV];
int V;

int eh_conexo(void)
{
    int cor[MAXV];
    int pilha[MAXV];
    int topo = -1;
    int contador = 0;
    int total_com_aresta = 0;

    memset(cor, BRANCO, sizeof(cor));

    for (int u = 0; u < V; u++) {
        for (int w = 0; w < V; w++) {
            if (adj[u][w] > 0) { total_com_aresta++; break; }
        }
    }

    int inicio = -1;
    for (int u = 0; u < V; u++) {
        for (int w = 0; w < V; w++) {
            if (adj[u][w] > 0) { inicio = u; break; }
        }
        if (inicio != -1) break;
    }

    if (inicio == -1) return 1;

    pilha[++topo] = inicio;
    cor[inicio] = CINZA;
    contador = 1;

    while (topo >= 0) {
        int v = pilha[topo--];
        for (int w = 0; w < V; w++) {
            if (adj[v][w] > 0 && cor[w] == BRANCO) {
                pilha[++topo] = w;
                cor[w] = CINZA;
                contador++;
            }
        }
        cor[v] = PRETO;
    }

    return (contador == total_com_aresta);
}

int eh_ponte(int v, int w)
{

    int grau_v = 0;
    for (int u = 0; u < V; u++) grau_v += adj[v][u];
    if (grau_v == 1) return 0;

    adj[v][w]--;
    adj[w][v]--;

    int conexo = eh_conexo();

    /* Reinsere a aresta */
    adj[v][w]++;
    adj[w][v]++;

    return !conexo;
}


void mostra_trilha_euleriana(int v)
{
    printf("%d ", v);

    int tem_aresta = 0;
    for (int w = 0; w < V; w++)
        if (adj[v][w] > 0) { tem_aresta = 1; break; }

    if (!tem_aresta) return;

    for (int w = 0; w < V; w++) {
        if (adj[v][w] > 0) {
            if (!eh_ponte(v, w)) {
                adj[v][w]--;
                adj[w][v]--;
                mostra_trilha_euleriana(w);
                return;
            }
        }
    }

    for (int w = 0; w < V; w++) {
        if (adj[v][w] > 0) {
            adj[v][w]--;
            adj[w][v]--;
            mostra_trilha_euleriana(w);
            return;
        }
    }
}

void fleury(void)
{
    int impares[MAXV], n_impares = 0;
    for (int u = 0; u < V; u++) {
        int grau = 0;
        for (int w = 0; w < V; w++) grau += adj[u][w];
        if (grau % 2 != 0) impares[n_impares++] = u;
    }

    if (n_impares > 2) {
        printf("Não existe trilha de Euler (mais de 2 vértices de grau ímpar).\n");
        return;
    }

    int v0;
    if (n_impares == 0) {
        v0 = 0;
    } else {
        v0 = impares[0];
    }

    printf("Trilha euleriana (Fleury): ");
    mostra_trilha_euleriana(v0);
    printf("\n");
}

int main(void)
{
 
    V = 5;
    memset(adj, 0, sizeof(adj));

    adj[0][1]++; adj[1][0]++;
    adj[1][2]++; adj[2][1]++;
    adj[2][3]++; adj[3][2]++;
    adj[3][0]++; adj[0][3]++;
    adj[0][2]++; adj[2][0]++;
    adj[2][4]++; adj[4][2]++;
    adj[4][3]++; adj[3][4]++;
    adj[4][1]++; adj[1][4]++;

    fleury();

    return 0;
}