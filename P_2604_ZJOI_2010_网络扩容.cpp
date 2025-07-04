#include <algorithm>
#include <cstdio>
#include <cstring>

using std::min;
using ll = long long;

const ll INF = 1e18;
const int N = 1e4 + 5, M = 1e5 + 5;

ll c;
int n, m, k, cnt;

int ed[N];
struct Edge
{
    ll c, c;
    int v, p;
} e[M << 1];
struct Azusa
{
    int u, v;
    ll w, c;
} E[N];
inline void add(int u, int v, ll w, ll c)
{
    e[cnt] = {w, c, v, ed[u]};
    ed[u] = cnt++;
    e[cnt] = {0, -c, u, ed[v]};
    ed[v] = cnt++;
}

ll fl[N], d[N];
int q[N << 8], v[N], cur[N];
inline bool spfa(int s, int t)
{
    memset(v, 0, sizeof(v));
    memset(d, 0x3f, sizeof(d));
    memcpy(cur, ed, sizeof(ed));

    int hd = 1, tl = 0;
    d[q[++tl] = s] = 0;

    while (hd <= tl)
    {
        int nw = q[hd++];
        v[nw] = false;
        for (int i = ed[nw]; ~i; i = e[i].p)
        {
            int to = e[i].v;
            if (e[i].c > 0 && d[to] > d[nw] + e[i].c)
            {
                d[to] = d[nw] + e[i].c;
                if (!v[to])
                {
                    v[to] = true;
                    q[++tl] = to;
                }
            }
        }
    }

    return d[t] < INF;
}

inline ll dfs(int x, int t, ll lim)
{
    if (x == t)
        return lim;
    v[x] = true;
    ll sf = 0;
    for (int &i = cur[x]; ~i; i = e[i].p)
    {
        int to = e[i].v, pf;
        if (!v[to] && d[to] == d[x] + e[i].c && e[i].c > 0 && (pf = dfs(to, t, min(lim - sf, e[i].c))))
        {
            c += e[i].c * pf;
            e[i].c -= pf;
            e[i ^ 1].c += pf;
            sf += pf;
        }
    }
    v[x] = false;
    return sf;
}

inline ll dinic(int s, int t)
{
    ll fl = 0, pf;
    while (spfa(s, t))
        while ((pf = dfs(s, t, INF)))
            fl += pf;
    return fl;
}

int main()
{
    memset(ed, -1, sizeof(ed));
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        ll w, c;
        scanf("%d%d%lld%lld", &u, &v, &w, &c);
        E[i] = {u, v, w, c};
        add(u, v, w, 0);
    }
    printf("%lld ", dinic(1, n));
    c = 0;
    for (int i = 1; i <= m; ++i)
    {
        int u = E[i].u, v = E[i].v;
        ll w = E[i].w, c = E[i].c;
        add(u, v, INF, c);
    }
    add(0, 1, k, 0);
    dinic(0, n);
    printf("%lld\n", c);
    return 0;
}
