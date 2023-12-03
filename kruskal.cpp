#include <stdio.h>
#include <stdlib.h>

struct Edge {
    int s;
    int e;
    int val;
};

int *unf;

int compareEdges(const void *a, const void *b) {
    return ((struct Edge *)a)->val - ((struct Edge *)b)->val;
}

int Find(int v) {
    if (v == unf[v])
        return v;
    else
        return unf[v] = Find(unf[v]);
}

void Union(int a, int b) {
    a = Find(a);
    b = Find(b);
    if (a != b)
        unf[a] = b;
}

int main() {
    int n, m, a, b, c, cnt = 0, res = 0;
    scanf("%d %d", &n, &m);

    // 메모리 할당 및 초기화
    unf = (int *)malloc(sizeof(int) * (n + 1));
    for (int i = 1; i <= n; i++) {
        unf[i] = i;
    }

    struct Edge *Ed = (struct Edge *)malloc(sizeof(struct Edge) * m);
    for (int i = 0; i < m; i++) {
        scanf("%d %d %d", &a, &b, &c);
        Ed[i].s = a;
        Ed[i].e = b;
        Ed[i].val = c;
    }

    qsort(Ed, m, sizeof(struct Edge), compareEdges);

    for (int i = 0; i < m; i++) {
        int fa = Find(Ed[i].s);
        int fb = Find(Ed[i].e);
        if (fa != fb) {
            res += Ed[i].val;
            Union(Ed[i].s, Ed[i].e);
        }
    }

    printf("%d\n", res);

    // 메모리 해제
    free(unf);
    free(Ed);

    return 0;
}

