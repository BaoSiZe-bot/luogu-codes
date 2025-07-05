#include <algorithm>
#include <cstdio>
#include <cstring>

using std::min;
using ll = long long;

const ll INF = 1e18;
const int N = 3e4 + 5, M = 5e6 + 5;

struct Edge
{
    ll cc;
    int v, p;
} e[M << 1];
int cnt;
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

int main()
{
    int n, res = 0;
    scanf("%d", &n);
    int s = 1, t = 2 * n + 1005;
    for (int i = s; i <= t; ++i)
        ed[i] = -1;
    for (int i = 1; i <= n; ++i)
    {
        int a;
        scanf("%d", &a);
        res += a;
        add(s, i, a);
    }
    for (int i = 1; i <= n; ++i)
    {
        int b;
        scanf("%d", &b);
        res += b;
        add(i, t, b);
    }
    int m;
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        int k, c1, c2;
        scanf("%d%d%d", &k, &c1, &c2);
        res += c1 + c2;
        add(s, i + n, c1);
        add(i + n + m, t, c2);
        for (int j = 1; j <= k; ++j)
        {
            int p;
            scanf("%d", &p);
            add(i + n, p, INF);
            add(p, i + n + m, INF);
        }
    }
    printf("%lld\n", res - dinic(s, t));
    return 0;
}
