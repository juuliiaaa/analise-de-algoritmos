#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char   simbolo;     
    int    freq;
    struct No *esq;
    struct No *dir;
} No;

#define MAX_NOS 256

typedef struct {
    No *dados[MAX_NOS];
    int tamanho;
} MinHeap;

static void heap_sobe(MinHeap *h, int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (h->dados[pai]->freq <= h->dados[i]->freq) break;
        No *tmp = h->dados[pai];
        h->dados[pai] = h->dados[i];
        h->dados[i]   = tmp;
        i = pai;
    }
}

static void heap_desce(MinHeap *h, int i) {
    while (1) {
        int menor = i;
        int esq   = 2 * i + 1;
        int dir   = 2 * i + 2;
        if (esq < h->tamanho && h->dados[esq]->freq < h->dados[menor]->freq)
            menor = esq;
        if (dir < h->tamanho && h->dados[dir]->freq < h->dados[menor]->freq)
            menor = dir;
        if (menor == i) break;
        No *tmp = h->dados[menor];
        h->dados[menor] = h->dados[i];
        h->dados[i]     = tmp;
        i = menor;
    }
}

static void insere(MinHeap *h, No *no) {
    h->dados[h->tamanho++] = no;
    heap_sobe(h, h->tamanho - 1);
}

static No *extrai_min(MinHeap *h) {
    No *min = h->dados[0];
    h->dados[0] = h->dados[--h->tamanho];
    heap_desce(h, 0);
    return min;
}

static No *alocar_no(char simbolo, int freq, No *esq, No *dir) {
    No *no = (No *)malloc(sizeof(No));
    if (no == NULL) {
        fprintf(stderr, "Erro crucial: Falha ao alocar memoria para no da arvore.\n");
        exit(EXIT_FAILURE);
    }
    no->simbolo = simbolo;
    no->freq    = freq;
    no->esq     = esq;
    no->dir     = dir;
    return no;
}

No *huffman(char *C, int *freq, int n) {
    MinHeap Q;
    Q.tamanho = 0;

    for (int i = 0; i < n; i++)
        insere(&Q, alocar_no(C[i], freq[i], NULL, NULL));

    for (int i = 1; i <= n - 1; i++) {
        No *x = extrai_min(&Q);
        No *y = extrai_min(&Q);
        
        No *z = alocar_no('\0', x->freq + y->freq, x, y);
        
        insere(&Q, z);
    }

    return extrai_min(&Q);   
}

static void imprime_codigos(No *raiz, char *codigo, int profundidade) {
    if (raiz == NULL) return;
    if (raiz->esq == NULL && raiz->dir == NULL) {
        codigo[profundidade] = '\0';
        printf("  '%c'  freq=%-5d  codigo=%s\n", raiz->simbolo, raiz->freq, codigo);
        return;
    }
    codigo[profundidade] = '0';
    imprime_codigos(raiz->esq, codigo, profundidade + 1);
    codigo[profundidade] = '1';
    imprime_codigos(raiz->dir, codigo, profundidade + 1);
}

static int custo_arvore(No *raiz, int prof) {
    if (raiz == NULL) return 0;
    if (raiz->esq == NULL && raiz->dir == NULL) return raiz->freq * prof;
    return custo_arvore(raiz->esq, prof + 1) + custo_arvore(raiz->dir, prof + 1);
}

static void libera(No *raiz) {
    if (raiz == NULL) return;
    libera(raiz->esq);
    libera(raiz->dir);
    free(raiz);
}

int main(void) {
    char simbolos[] = {'a', 'b', 'c', 'd', 'e', 'f'};
    int  freq[]     = { 45,  13,  12,  16,   9,   5};
    int  n          = 6;

    printf("Codigo de Huffman\n");
    No *raiz = huffman(simbolos, freq, n);

    char codigo[64];
    printf("Codigos gerados:\n");
    imprime_codigos(raiz, codigo, 0);

    printf("\nCusto da arvore B(T) = %d bits\n", custo_arvore(raiz, 0));
    libera(raiz);
    return 0;
}