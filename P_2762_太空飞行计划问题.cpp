#include <cstdio>
#include <stdio.h>

const int N = 5e5 + 5, M = 1e6 + 5;

struct Edge
{
    int v, w, p;
} e[M];
int ed[N], cnt;
inline void add(int u, int v, int w)
{
    e[cnt] = {v, w, ed[u]};
    ed[u] = cnt++;
    e[cnt] = {u, 0, ed[v]};
    ed[v] = cnt++;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    return 0;
}