#include <stdio.h>
using ll = long long;
#define int ll
struct Edge
{
    int v, p;
} e[1000005];
int ed[1000005], cnt;
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
inline int min(int a, int b)
{
    return a < b ? a : b;
}
ll sz[1000005], ct[1000005]; // size and contribution
bool f[1000005];
int dfn[1000005], low[1000005], gtm, n, m;
inline void tarjan(int x)
{
    dfn[x] = low[x] = ++gtm;
    sz[x] = 1;
    int flg = 0, tot = 0;
    for (int i = ed[x]; i; i = e[i].p)

    {
        int to = e[i].v;
        if (!dfn[to])
        {
            tarjan(to);
            low[x] = min(low[x], low[to]);
            sz[x] += sz[to];
            if (low[to] >= dfn[x])
            {
                ++flg;
                tot += sz[to];
                ct[x] += sz[to] * (n - sz[to]);
                if (flg > 1 || x ^ 1)
                    f[x] = 1;
            }
        }
        else
            low[x] = min(low[x], dfn[to]);
    }
    if (f[x])
        ct[x] += (n - tot - 1) * (tot + 1) + (n - 1);
    else
        ct[x] = (n - 1) << 1;
}
signed main()
{
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%lld%lld", &u, &v);
        add(u, v);
        add(v, u);
    }
    tarjan(1);
    for (int i = 1; i <= n; ++i)
        printf("%lld\n", ct[i]);
    return 0;
}
