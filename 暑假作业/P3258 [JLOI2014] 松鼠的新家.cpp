#include <stdio.h>
template <const int N> struct GR
{
    struct Edge
    {
        int v, p;
    } e[N];
    int ed[N], cnt = 0;
    inline void add(int u, int v)
    {
        e[++cnt] = {v, ed[u]};
        ed[u] = cnt;
    }
};
GR<600005> g;
int d[600005], a[600005], t[600005], f[22][600005], s[600005];
inline void dfs(int x, int fa)
{
    d[x] = d[fa] + 1;
    for (int i = 1; i <= 20; ++i)
        f[i][x] = f[i - 1][f[i - 1][x]];
    for (int i = g.ed[x]; i; i = g.e[i].p)
    {
        int to = g.e[i].v;
        if (to != fa)
        {
            f[0][to] = x;
            dfs(to, x);
        }
    }
}
inline void getsum(int x, int fa)
{
    s[x] = t[x];
    for (int i = g.ed[x]; i; i = g.e[i].p)
    {
        int to = g.e[i].v;
        if (to != fa)
        {
            getsum(to, x);
            s[x] += s[to];
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
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g.add(u, v);
        g.add(v, u);
    }
    dfs(1, 0);
    for (int i = 1; i < n; ++i)
    {
        int u = a[i], v = a[i + 1], lc = lca(u, v);
        ++t[u];
        ++t[v];
        --t[lc];
        --t[f[0][lc]];
    }
    getsum(1, 0);
    for (int i = 1; i <= n; ++i)
        printf("%d\n", s[i] - bool(i ^ a[1]));
    return 0;
}
