#include <algorithm>
#include <cstdio>
#include <cstring>

using std::min;
using ll = long long;

const ll INF = 1e18;
const int N = 1e4 + 5, M = 1e5 + 5;

ll cost;
int n, m, s, t, cnt;

int ed[N];
struct Edge
{
    ll w, c;
    int v, p;
} e[M << 1];
inline void add(int u, int v, ll w, ll c)
{
    e[cnt] = {w, c, v, ed[u]};
    ed[u] = cnt++;
}

ll fl[N], d[N];
int q[N << 8], v[N], cur[N];
inline bool spfa()
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
            if (e[i].w > 0 && d[to] > d[nw] + e[i].c)
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

inline ll dfs(int x, ll lim)
{
    if (x == t)
        return lim;
    v[x] = true;
    ll sf = 0;
    for (int &i = cur[x]; ~i; i = e[i].p)
    {
        int to = e[i].v, pf;
        if (!v[to] && d[to] == d[x] + e[i].c && e[i].w > 0 && (pf = dfs(to, min(lim - sf, e[i].w))))
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
    memset(ed, -1, sizeof(ed));

    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        ll w, c;
        scanf("%d%d%lld%lld", &u, &v, &w, &c);
        add(u, v, w, c);
        add(v, u, 0, -c);
    }
    ll res = dinic();
    printf("%lld %lld\n", res, cost);
    return 0;
}
