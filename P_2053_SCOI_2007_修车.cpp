#include <algorithm>
#include <cstdio>
#include <cstring>

using std::min;
using ll = long long;

const ll INF = 1e18;
const int N = 1e4 + 5, M = 1e5 + 5;

ll c;
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
    e[cnt] = {0, -c, u, ed[v]};
    ed[v] = cnt++;
}

ll fl[N], d[N];
int q[N << 8], v[N], cur[N];
inline bool spfa()
{
    for (int i = 0; i <= t; ++i)
    {
        d[i] = INF;
        v[i] = false;
        cur[i] = ed[i];
    }

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
            c += e[i].c * pf;
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
    int m, n;
    scanf("%d%d", &m, &n);
    s = 0, t = n * (m + 1) + 1;
    for (int i = 0; i <= t; ++i)
        ed[i] = -1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            int t;
            scanf("%d", &t);
            for (int k = 1; k <= n; ++k)
                add(i, n * j + k, 1, k * t);  // n * j + k 恰好从 n + 1 开始，与 i 不重复。
        }
    }
    for (int i = 1; i <= n; ++i)
        add(s, i, 1, 0);
    for (int i = 1; i <= n * m; ++i)
        add(n + i, t, 1, 0);
    dinic();
    printf("%.2lf\n", (double)c / n);
    return 0;
}
