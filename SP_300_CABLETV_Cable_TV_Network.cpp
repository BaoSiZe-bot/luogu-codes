#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>

using std::min;
using ll = long long;

const ll INF = INT_MAX;
const int N = 505, M = 5005;

ll fl[N], res;
struct Edge
{
    ll cc;
    int v, p;
} e[M << 1];
int n, m, cnt;
int ed[N], q[N], lev[N], cur[N];
inline void add(int u, int v, ll c)
{
    e[cnt] = {c, v, ed[u]};
    ed[u] = cnt++;
    e[cnt] = {0, u, ed[v]};
    ed[v] = cnt++;
}

inline bool bfs(int s, int t)
{
    int hd = 1, tl = 0;
    for (int i = 0; i <= n * 2; ++i)
        lev[i] = -1;
    cur[s] = ed[s];
    lev[q[++tl] = s] = 0;

    while (hd <= tl)
    {
        int nw = q[hd++];
        for (int i = ed[nw]; ~i; i = e[i].p)
            if (!~lev[e[i].v] && e[i].cc)
            {
                cur[e[i].v] = ed[e[i].v];
                lev[e[i].v] = lev[nw] + 1;
                if (e[i].v == t)
                    return true;
                q[++tl] = e[i].v;
            }
    }

    return false;
}

ll dfs(int x, int t, ll lim)
{
    if (x == t)
        return lim;

    ll sf = 0;
    for (int &i = cur[x]; ~i && sf < lim; i = e[i].p)
    {
        int to = e[i].v, pf;
        if (lev[to] == lev[x] + 1 && e[i].cc)
        {
            if (!(pf = dfs(to, t, min(lim - sf, e[i].cc))))
                lev[to] = -1;
            e[i].cc -= pf;
            e[i ^ 1].cc += pf;
            sf += pf;
        }
    }
    return sf;
}

inline ll dinic(int s, int t)
{
    ll ret = 0;
    while (bfs(s, t))
    {
        ll fl = 0;
        while ((fl = dfs(s, t, INF)))
        {
            if (fl >= INF)
                return INF;
            ret += fl;
            if (ret >= res)
                return ret;
        }
    }
    return ret;
}

inline void init()
{
    scanf("%d %d", &n, &m);
    res = n;
    cnt = 0;

    for (int i = 0; i <= n * 2; ++i)
        ed[i] = -1;
}

inline void build()
{
    for (int i = 0; i < n; ++i)
        add(i << 1, i << 1 | 1, 1);

    for (int i = 0; i < m; ++i)
    {
        int u, v;
        scanf(" (%d,%d)", &u, &v);
        add(u << 1 | 1, v << 1, INF);
        add(v << 1 | 1, u << 1, INF);
    }
}

inline void calc()
{
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            res = min(res, dinic(i << 1 | 1, j << 1));
            for (int k = 0; k <= cnt; k += 2)
            {
                e[k].cc += e[k ^ 1].cc;
                e[k ^ 1].cc = 0;
            }
        }
    }
}

inline void solve()
{
    init();
    build();
    calc();
    printf("%lld\n", res);
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}