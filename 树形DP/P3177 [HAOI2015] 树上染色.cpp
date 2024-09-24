#include <stdio.h>
using ll = long long;
const int N = 5005;
struct Edge
{
    int v;
    ll w;
    int p;
} e[N];
int ed[N], cnt = 0, n, k;
ll dp[N][N], sz[N];
inline void add(int u, int v, int w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
inline void cmax(ll &a, ll b)
{
    a = (a < b ? b : a);
}
void dfs(int x, int fa)
{
    sz[x] = 1;
    for (int i = ed[x]; i; i = e[i].p)
    {
        int y = e[i].v;
        ll w = e[i].w, t;
        if (y == fa)
            continue;
        dfs(y, x);
        for (int j = sz[x]; ~j; --j)
            for (int p = sz[y]; ~p; --p)
            {
                //a line shouldn't out 100 chars limitation.
                t = dp[x][j] + dp[y][p] + w * p * (k - p) + w * (n + p - k - sz[y]) * (sz[y] - p);
                cmax(dp[x][j + p], t);
            }
        sz[x] += sz[y];
    }
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    dfs(1, 0);
    printf("%lld\n", dp[1][k]);
    return 0;
}
