#include <stdio.h>
const int N = 5e5 + 5;
using ll = long long;
struct Edge
{
    int v;
    ll w;
    int p;
} e[N];
int ed[N], cnt;
inline ll max(ll a, ll b)
{
    return a < b ? b : a;
}
inline ll min(ll a, ll b)
{
    return a < b ? a : b;
}
inline void add(int u, int v, ll w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
ll d1[N], d2[N];
void dfs(ll d[], int x, int fa)
{
    for (int i = ed[x]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (to ^ fa)
        {
            d[to] = d[x] + e[i].w;
            dfs(d, to, x);
        }
    }
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        ll w;
        scanf("%d%d%lld", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    int a = 1, b = 1;
    ll res = 0;
    dfs(d1, a, -1);
    for (int i = 1; i <= n; ++i)
        a = (d1[i] > d1[a] ? i : a);
    d1[a] = 0;
    dfs(d1, a, -1);
    for (int i = 1; i <= n; ++i)
        b = (d1[i] > d1[b] ? i : b);
    dfs(d2, b, -1);
    for (int c = 1; c <= n; ++c)
        res = max(res, min(d1[c], d2[c]));
    printf("%lld", res + d1[b]);
    return 0;
}
