#include <algorithm>
#include <cstdio>
#include <cstring>

using std::min;
using ll = long long;

const ll INF = 1e18;
const int N = 6e6 + 5, M = 2e7 + 5;

struct Edge
{
    ll cc;
    int v, p;
} e[M << 1];
int cnt;
int n, m, res = 0;
int q[N], lev[N], cur[N], ed[N];
inline void add(int u, int v, ll c)
{
    e[cnt] = {c, v, ed[u]};
    ed[u] = cnt++;
    e[cnt] = {0, u, ed[v]};
    ed[v] = cnt++;
}

inline bool spfa(int s, int t)
{
    int hd = 1, tl = 0;
    for (int i = s; i <= t; ++i)
    {
        lev[i] = -1;
        cur[i] = ed[i];
    }
    lev[q[++tl] = s] = 0;

    while (hd <= tl)
    {
        int nw = q[hd++];
        for (int i = ed[nw]; ~i; i = e[i].p)
            !~lev[e[i].v] && e[i].cc > 0 && (lev[q[++tl] = e[i].v] = lev[nw] + 1);
    }

    return ~lev[t];
}

inline ll dfs(int x, int t, ll lim)
{
    if (x == t)
        return lim;

    ll sf = 0;
    for (int &i = cur[x]; ~i; i = e[i].p)
    {
        int to = e[i].v, pf;
        if (lev[to] == lev[x] + 1 && e[i].cc > 0)
        {
            if ((pf = dfs(to, t, min(lim - sf, e[i].cc))))
            {
                e[i].cc -= pf;
                e[i ^ 1].cc += pf;
                sf += pf;
            }
        }
    }
    return sf;
}

inline ll dinic(int s, int t)
{
    ll fl = 0;
    while (spfa(s, t))
    {
        ll pf;
        while ((pf = dfs(s, t, INF)))
            fl += pf;
    }
    return fl;
}
int get(int i, int j)
{
    return (i - 1) * m + j;
}
int main()
{
    scanf("%d%d", &n, &m);
    int s = 0, t = 6 * n * m, bid = n * m;
    for (int i = s; i <= t; ++i)
        ed[i] = -1;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int a;
            scanf("%d", &a);
            res += a;
            add(s, get(i, j), a);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int b;
            scanf("%d", &b);
            res += b;
            add(get(i, j), t, b);
        }
    for (int i = 1; i < n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int x;
            scanf("%d", &x);
            res += x;
            add(s, ++bid, x);
            add(bid, get(i, j), INF);
            add(bid, get(i + 1, j), INF);
        }
    for (int i = 1; i < n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int x;
            scanf("%d", &x);
            res += x;
            add(++bid, t, x);
            add(get(i, j), bid, INF);
            add(get(i + 1, j), bid, INF);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < m; ++j)
        {
            int x;
            scanf("%d", &x);
            res += x;
            add(s, ++bid, x);
            add(bid, get(i, j), INF);
            add(bid, get(i, j + 1), INF);
        }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < m; ++j)
        {
            int x;
            scanf("%d", &x);
            res += x;
            add(++bid, t, x);
            add(get(i, j), bid, INF);
            add(get(i, j + 1), bid, INF);
        }
    printf("%lld\n", res - dinic(s, t));
    return 0;
}
