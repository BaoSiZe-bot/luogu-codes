#include <stdio.h>

struct Edge
{
    int v, p;
} e[1000005], g[1000005];
int ed[500005], hd[500005], cnt, tot;
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
inline void lnk(int u, int v)
{
    g[++tot] = {v, hd[u]};
    hd[u] = tot;
}
inline int swt(int id)
{
    return id & 1 ? id + 1 : id - 1;
}
int dfn[500005], low[500005], pos[500005], gtm, pts;
bool br[500005];
inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline void tarjan(int x, int fe)
{
    dfn[x] = low[x] = ++gtm;
    for (int i = ed[x]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (!dfn[to])
        {
            tarjan(to, i);
            low[x] = min(low[x], low[to]);
            if (low[to] > dfn[x])
                br[i] = br[swt(i)] = 1;
        }
        else if (i ^ swt(fe))
            low[x] = min(low[x], dfn[to]);
    }
}
inline void shrink(int rt)
{
    pos[rt] = pts;
    for (int i = ed[rt]; i; i = e[i].p)
        if (!br[i] && !pos[e[i].v])
            shrink(e[i].v);
}
int d[500005], f[22][500005];
inline void dfs(int ro, int fa)
{
    d[ro] = d[fa] + 1;
    for (int i = 1; i <= 20; ++i)
        f[i][ro] = f[i - 1][f[i - 1][ro]];
    for (int i = hd[ro]; i; i = g[i].p)
    {
        int to = g[i].v;
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
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i, 0);
    for (int i = 1; i <= n; ++i)
        if (!pos[i])
        {
            ++pts;
            shrink(i);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = ed[i]; j; j = e[j].p)
        {
            int to = e[j].v;
            if (pos[i] ^ pos[to])
                lnk(pos[i], pos[to]);
        }
    dfs(1, 0);
    int q;
    scanf("%d", &q);
    while (q--)
    {
        int a, b, lc;
        scanf("%d%d", &a, &b);
        lc = lca(pos[a], pos[b]);
        printf("%d\n", d[pos[a]] + d[pos[b]] - 2 * d[lc]);
    }
    return 0;
}
