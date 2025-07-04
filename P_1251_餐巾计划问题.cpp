#include <algorithm>
#include <cstdio>
#include <cstring>

using std::min;
using ll = long long;

const ll INF = 1e18;
const int N = 1e5 + 5, M = 5e5 + 5;

ll cost;
ll dis[N];
struct Edge
{
    ll w, c;
    int v, p;
} e[M << 1];
int n, m, s, t, cnt;
int ed[N], q[N], cur[N];
int x[N], y[N], a[N], b[N], v[N];
inline void add(int u, int v, ll c, ll w)
{
    e[cnt] = {c, w, v, ed[u]};
    ed[u] = cnt++;
    e[cnt] = {0, -w, u, ed[v]};
    ed[v] = cnt++;
}

inline bool spfa()
{
    memset(v, 0, sizeof(v));
    memset(dis, 0x3f, sizeof(dis));
    memcpy(cur, ed, sizeof(ed));

    int hd = 1, tl = 0;
    dis[q[++tl] = s] = 0;

    while (hd <= tl)
    {
        int nw = q[hd++];
        v[nw] = false;
        for (int i = ed[nw]; ~i; i = e[i].p)
        {
            int to = e[i].v;
            if (e[i].w && dis[to] > dis[nw] + e[i].c)
            {
                dis[to] = dis[nw] + e[i].c;
                if (!v[to])
                {
                    v[to] = true;
                    q[++tl] = to;
                }
            }
        }
    }

    return dis[t] < INF;
}

inline ll dfs(int x, ll lim)
{
    if (x == t)
        return lim;
    v[x] = true;
    ll sf = 0;
    for (int &i = cur[x]; ~i; i = e[i].p)
    {
        int to = e[i].v, pf;
        if (!v[to] && dis[to] == dis[x] + e[i].c && e[i].w > 0 && (pf = dfs(to, min(lim - sf, e[i].w))))
        {
            cost += e[i].c * pf;
            e[i].w -= pf;
            e[i ^ 1].w += pf;
            sf += pf;
        }
    }
    v[x] = false;
    return sf;
}

inline ll dinic()
{
    ll fl = 0, pf;
    while (spfa())
        while ((pf = dfs(s, INF)))
            fl += pf;
    return fl;
}
int main()
{
    int n, p, tf, cf, ts, cs;
    scanf("%d", &n);
    s = 1, t = n * 2 + 2;
    for (int i = s; i <= t; ++i)
        ed[i] = -1;
    for (int i = 1; i <= n; ++i)
    {
        int x;
        scanf("%d", &x);
        add(s, i << 1, x, 0);
        add(i << 1 | 1, t, x, 0);
        if (i < n)
            add(i << 1, (i + 1) << 1, INF, 0);
    }
    scanf("%d%d%d%d%d", &p, &tf, &cf, &ts, &cs);
    for (int i = 1; i <= n; ++i)
    {
        if (i <= n - tf)
            add(i << 1, (i + tf) << 1 | 1, INF, cf);
        if (i <= n - ts)
            add(i << 1, (i + ts) << 1 | 1, INF, cs);
        add(s, i << 1 | 1, INF, p);
    }
    dinic();
    printf("%lld\n", cost);
    return 0;
}