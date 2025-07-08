#include <limits.h>
#include <queue>
#include <stdio.h>
#include <string.h>
#define x first
#define y second
using ll = long long;
inline ll min(ll a, ll b)
{
    return a < b ? a : b;
}
const int M = 1e6 + 5, N = 5e5 + 5;
ll B, E, P;
int n, m;
struct Edge
{
    int v;                      // the ending of this edge
    ll w;                      // the weight of this edge
    int p;                      // the ID of previos edge
} e[M];                         // the edge set
int ed[N];                      // the ending edge of a node
int cnt;                        // edge count
inline void add(int u, int v, ll w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
ll d[N];                       // the temp answer
ll df[N];                      // the first answer
ll ds[N];                      // the second answer
ll dt[N];                      // the third answer
ll f[N];
inline void dij(int s)
{
    memset(f, 0, sizeof(f));
    memset(d, 0x3f, sizeof(d));
    std::priority_queue<std::pair<ll, int>, std::vector<std::pair<ll, int>>, std::greater<std::pair<ll, int>>> q;
    q.push({0, s});
    d[s] = 0;
    while (!q.empty())
    {
        int nw = q.top().second;
        q.pop();
        if (f[nw])
            continue;
        f[nw] = 1;
        for (int i = ed[nw]; i; i = e[i].p)
        {
            int to = e[i].v;
            if (d[to] > d[nw] + e[i].w)
            {
                d[to] = d[nw] + e[i].w;
                q.push({d[to], to});
            }
        }
    }
}

int main()
{
    scanf("%lld%lld%lld%d%d", &B, &E, &P, &n, &m);
    if (P > B + E)
        P = B + E;
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v, 1ll);
        add(v, u, 1ll);
    }
    dij(1);
    for (int i = 1; i <= n; ++i)
        df[i] = 1ll * d[i] * B;
    dij(2);
    for (int i = 1; i <= n; ++i)
        ds[i] = 1ll * d[i] * E;
    dij(n);
    for (int i = 1; i <= n; ++i)
        dt[i] = 1ll * d[i] * P;
    ll res = LONG_LONG_MAX;
    for (int i = 1; i <= n; i++)
        res = min(res, df[i] + ds[i] + dt[i]);
    printf("%lld\n", res);
    return 0;
}
