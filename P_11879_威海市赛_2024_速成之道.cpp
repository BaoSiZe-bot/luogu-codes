#include <algorithm>
#include <cstdio>
#include <cstring>

using std::min;
using ll = long long;

const ll INF = 1e18;
const int N = 1e5 + 5, M = 5e5 + 5;

ll fl[N];
struct Edge
{
    ll cc;
    int v, p;
} e[M << 1];
int n, m, s, t, cnt;
int x[N], y[N], a[N], b[N];
int ed[N], q[N], lev[N], cur[N];
inline void add(int u, int v, ll c)
{
    e[cnt] = {c, v, ed[u]};
    ed[u] = cnt++;
    e[cnt] = {0, u, ed[v]};
    ed[v] = cnt++;
}

inline bool bfs()
{
    int hd = 1, tl = 0;
    for (int i = 1; i <= t; ++i)
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

inline ll dfs(int x, ll lim)
{
    if (x == t)
        return lim;

    ll sf = 0;
    for (int &i = cur[x]; ~i; i = e[i].p)
    {
        int to = e[i].v, pf;
        if (lev[to] == lev[x] + 1 && e[i].cc > 0)
        {
            if ((pf = dfs(to, min(lim - sf, e[i].cc))))
            {
                e[i].cc -= pf;
                e[i ^ 1].cc += pf;
                sf += pf;
            }
        }
    }
    return sf;
}

inline ll dinic()
{
    ll fl = 0;
    while (bfs())
    {
        ll pf;
        while((pf = dfs(s, INF)))
            fl += pf;
    }
    return fl;
}

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    s = 1;
    t = n * 2 + 2;
    for (int i = 1; i <= t; ++i)
        ed[i] = -1;
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d", x + i, y + i);
        add(x[i] << 1 | 1, y[i] << 1, INF);
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", a + i);
        add(s, i << 1, a[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", b + i);
        add(i << 1, i << 1 | 1, b[i]);
    }
    int x;
    scanf("%d", &x);
    add(x << 1 | 1, t, INF);
    printf("%lld\n", dinic());
    return 0;
}
