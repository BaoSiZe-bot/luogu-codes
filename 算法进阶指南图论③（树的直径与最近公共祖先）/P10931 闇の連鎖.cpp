#include <stdio.h>
#include <vector>
std::vector<int> g[100005];
int d[100005], w[100005], f[22][100005];
inline void dfs(int rt, int fa)
{
    f[0][rt] = fa;
    d[rt] = d[fa] + 1;
    for (int i = 1; i <= 20; ++i)
        f[i][rt] = f[i - 1][f[i - 1][rt]];
    for (int i : g[rt])
        if (i != fa)
            dfs(i, rt);
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
inline void sum(int rt)
{
    for (int i : g[rt])
        if (i ^ f[0][rt])
        {
            sum(i);
            w[rt] += w[i];
        }
}
inline void ade(int u, int v)
{
    w[lca(u, v)] -= 2;
    w[u]++;
    w[v]++;
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1, 0);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        ade(u, v);
    }
    sum(1);
    int res = 0;
    for (int i = 2; i <= n; ++i)
        if (!w[i])
            res += m;
        else
            res += (w[i] == 1);
    printf("%d", res);
    return 0;
}
