#include <bits/stl_algobase.h>
#include <bits/stl_algo.h>
#include <cinttypes>
#include <string.h>
#include <stdio.h>
using ll = long long;
struct Edge
{
    int u, v;
    ll w;
    bool operator<(const Edge &other) const
    {
        return w < other.w;
    }
} e[12005];
int p[100005], h[100005];
ll w[100005], res;
inline int fd(int x)  // find parent
{
    return ~p[x] ? p[x] = fd(p[x]) : x;
}
inline void mg(int id)  // merge u, v
{
    int u = fd(e[id].u), v = fd(e[id].v);
    if (u ^ v)
    {
        res += (e[id].w + 1) * (w[u] * w[v] - 1);
        if (h[u] <= h[v])
        {
            p[u] = v;
            w[v] += w[u];
        }
        else
        {
            p[v] = u;
            w[u] += w[v];
        }
        if (h[u] == h[v])
            ++h[u];
    }
}

int main()
{
    int t, n;
    scanf("%d", &t);
    while (t--)
    {
        memset(p, 0xff, sizeof p);
        res = 0;
        scanf("%d", &n);
        for (int i = 1; i < n; ++i)
            scanf("%d%d%lld", &e[i].u, &e[i].v, &e[i].w);
        std::sort(e + 1, e + n);
        for (int i = 1; i <= n; ++i)
            w[i] = 1;
        for (int i = 1; i < n; ++i)
            mg(i);
        printf("%lld\n", res);
    }
    return 0;
}
