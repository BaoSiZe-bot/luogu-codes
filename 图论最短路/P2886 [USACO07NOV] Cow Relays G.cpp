#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <string.h>
#include <stdio.h>
using ll = long long;
__gnu_pbds::gp_hash_table<int, int> gp;
int n, t, s, e, m;
inline int min(int a, int b)
{
    return a < b ? a : b;
}
struct Flotrix
{
    ll a[205][205];
    Flotrix()
    {
        memset(a, 0x3f, sizeof a);
    }
    Flotrix operator*(const Flotrix &other) const
    {
        Flotrix t;
        for (int k = 1; k <= m; ++k)
            for (int i = 1; i <= m; ++i)
                for (int j = 1; j <= m; ++j)
                    t.a[i][j] = min(t.a[i][j], a[i][k] + other.a[k][j]);
        return t;
    }
} tmp, res;
int main()
{
    scanf("%d%d%d%d", &n, &t, &s, &e);
    for (int i = 1; i <= t; ++i)
    {
        ll w;
        int u, v;
        scanf("%lld%d%d", &w, &u, &v);
        if (u == v)
            continue;
        if (!gp[u])
            gp[u] = ++m;
        if (!gp[v])
            gp[v] = ++m;
        u = gp[u];
        v = gp[v];
        tmp.a[u][v] = tmp.a[v][u] = min(tmp.a[u][v], w);
    }
    for (int i = 1; i <= m; i++)
        res.a[i][i] = 0;
    while (n)
    {
        if (n & 1)
            res = res * tmp;
        tmp = tmp * tmp;
        n >>= 1;
    }
    printf("%lld", res.a[gp[s]][gp[e]]);
    return 0;
}
