#include <algorithm>
#include <cstdio>
#include <cstring>

using std::min;
using ll = long long;

const ll INF = 1e18;
const int N = 1e4 + 5, M = 1e5 + 5;

ll cost;
int n, k;
int s, t, cnt;

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
    ll res = 0;
    while (spfa())
    {
        ll pf;
        while ((pf = dfs(s, INF)))
            res += pf;
    }
    return res;
}

inline int gid(int i, int j, int f)
{
    return (i - 1) * n + j + f * n * n;
}

int main()
{
    memset(ed, -1, sizeof(ed));
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            int x, iid, oid;
            scanf("%d", &x);
            iid = gid(i, j, 0);
            oid = gid(i, j, 1);
            add(iid, oid, 1, -x);
            add(oid, iid, 0, x);
            add(iid, oid, INF, 0);
            add(oid, iid, 0, 0);
            if (i < n)
            {
                int iyd = gid(i + 1, j, 0);
                add(oid, iyd, INF, 0);
                add(iyd, oid, 0, 0);
            }
            if (j < n)
            {
                int ixd = gid(i, j + 1, 0);
                add(oid, ixd, INF, 0);
                add(ixd, oid, 0, 0);
            }
        }
    add(0, gid(1, 1, 0), k, 0);
    add(gid(1, 1, 0), 0, 0, 0);
    add(gid(n, n, 1), 2 * n * n + 1, k, 0);
    add(2 * n * n + 1, gid(n, n, 1), 0, 0);
    t = 2 * n * n + 1;
    dinic();
    printf("%lld\n", -cost);
    return 0;
}
