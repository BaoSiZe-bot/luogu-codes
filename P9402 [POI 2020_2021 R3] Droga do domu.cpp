#include <algorithm>
#include <cstring>
#include <stdio.h>
#include <climits>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#define int long long
using ll = long long;
const int M = 1e6 + 5, N = 1e5 + 5, S = 5e4 + 5;
struct Edgy
{
    int v, p;
} e2[M];
int ed[M], cnt;
inline void add(int u, int v)
{
    e2[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
struct Edge
{
    int v;
    ll w, co;
} e[M];
__gnu_pbds::gp_hash_table<int, int> gp[N];
int num;
ll delay[S], tmp[N], p[N], f[S][205];
ll calc(int id, ll u, ll v)
{
    if (v <= e[id].co)
        return e[id].co + e[id].w;
    return ((v - e[id].co + delay[u] - 1) / delay[u]) * delay[u] + e[id].co + e[id].w;
}
signed main()
{
    memset(f, 0x3f, sizeof f);
    int n, m, s, k, t;
    scanf("%lld%lld%lld%lld%lld", &n, &m, &s, &k, &t);
    for (int i = 1; i <= k; ++i)
        f[0][k] = 0;
    for (int i = 1; i <= m; ++i)
    {
        int a, b, c;
        scanf("%lld%lld%lld", &a, &b, &c);
        gp[a][b] = gp[b][a] = c;
    }
    for (int i = 1; i <= s; ++i)
    {
        int l, x;
        scanf("%lld%lld%lld", &l, &x, delay + i);
        for (int j = 1; j <= l; ++j)
            scanf("%lld", tmp + j);
        for (int j = 1; j <= l; ++j)
        {
            p[++num] = i;
            add(tmp[j], num);
            if (j == l)
            {
                e[num].co = x;
                continue;
            }
            e[num] = {num + 1, gp[tmp[j]][tmp[j + 1]], x};
            x += gp[tmp[j]][tmp[j + 1]];
        }
    }
    for (int i = ed[1]; i; i = e2[i].p)
        f[e2[i].v][0] = t;
    for (int i = 1; i <= num; ++i)
    {
        int to = e[i].v;
        if (to)
            f[to][0] = std::min(f[to][0], calc(i, p[i], f[i][0]));
    }
    for (int i = 1; i <= k; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            ll mn = 0x3fffffffffffffff;
            for (int l = ed[j]; l; l = e2[l].p)
                mn = std::min(mn, f[e2[l].v][i - 1]);
            for (int l = ed[j]; l; l = e2[l].p)
                f[e2[l].v][i] = mn;
        }
        for (int j = 1; j <= num; ++j)
        {
            int to = e[j].v;
            if (to)
                f[to][i] = std::min(f[to][i], calc(j, p[j], f[j][i]));
        }
    }
    ll res = 0x3fffffffffffffff;
    for (int i = ed[n]; i; i = e2[i].p)  
        for (int j = 0; j <= k; ++j)
            res = std::min(res, f[e2[i].v][j]);
    if (res >= 0x2fffffffffffffff)
        printf("NIE");
    else
        printf("%lld\n", res);
    return 0;
}
            int to = e[j].v;
            if (to)
                f[to][i] = std::min(f[to][i], calc(j, p[j], f[j][i]));
        }
    }
    ll res = 0x3fffffffffffffff;
    for (int i = ed[n]; i; i = e2[i].p)  
        for (int j = 0; j <= k; ++j)
            res = std::min(res, f[e2[i].v][j]);
    if (res >= 0x2fffffffffffffff)
        printf("NIE");
    else
        printf("%lld\n", res);
    return 0;
}
