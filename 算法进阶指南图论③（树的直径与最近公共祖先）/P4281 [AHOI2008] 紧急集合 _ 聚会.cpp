#include <stdio.h>
struct Edge
{
    int v, p;
} e[1000005];
int ed[500005], cnt;
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
int d[500005], f[22][500005];
inline void dfs(int ro, int fa)
{
    d[ro] = d[fa] + 1;
    for (int i = 1; i <= 20; ++i)
        f[i][ro] = f[i - 1][f[i - 1][ro]];
    for (int i = ed[ro]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (to != fa)
        {
            f[0][to] = ro;
            dfs(to, ro);
        }
    }
}
inline int lca(int u, int v)
{
    if (d[u] < d[v])
        u ^= v ^= u ^= v;
    for (int i = 20; ~i; --i)
    {
        if (d[f[i][u]] >= d[v])
            u = f[i][u];
        if (u == v)
            return u;
    }
    for (int i = 20; ~i; --i)
        if (f[i][u] != f[i][v])
        {
            u = f[i][u];
            v = f[i][v];
        }
    return f[0][u];
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(1, 0);
    while (m--)
    {
        int u, v, w, f1, f2, f3, t;
        scanf("%d%d%d", &u, &v, &w);
        f1 = lca(u, v);
        f2 = lca(u, w);
        f3 = lca(v, w);
        if (f2 == f3)
            t = f1;
        if (f1 == f3)
            t = f2;
        if (f1 == f2)
            t = f3;
        printf("%d %d\n", t, d[u] + d[v] + d[w] - d[f1] - d[f2] - d[f3]);
    }
    return 0;
}
