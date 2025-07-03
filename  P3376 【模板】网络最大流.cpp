#include <algorithm>
#include <cstdio>
#include <cstring>

using std::min;
using ll = long long;

const ll INF = 9e18;
const int N = 505, M = 5005;

int n, m, s, t, cnt;

int ed[N];
struct Edge
{
    ll cc;
    int v, p;
} e[M << 1];
inline void add(int u, int v, ll c)
{
    e[cnt] = {c, v, ed[u]};
    ed[u] = cnt++;
}

ll fl[N];
int q[N], lev[N];
inline bool spfa()
{
    int hd = 1, tl = 0;
    for (int i = 1; i <= n; ++i)
        lev[i] = -1;
    lev[q[++tl] = s] = 0;

    while(hd <= tl)
    {
        int nw = q[hd++];
        for (int i = ed[nw]; ~i; i = e[i].p)
            !~lev[e[i].v] && e[i].cc > 0 && (lev[q[++tl] = e[i].v] = lev[nw] + 1);
    }

    return ~lev[t];
}

int cur[N];
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
    while(spfa())
    {
        memcpy(cur, ed, sizeof(ed));
        for (ll pf = dfs(s, INF); pf > 0; pf = dfs(s, INF))
            fl += pf;
    }
    return fl;
}

int main()
{
    memset(ed, -1, sizeof(ed));

    scanf("%d%d%d%d", &n, &m, &s, &t);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        ll c;
        scanf("%d%d%lld", &u, &v, &c);
        add(u, v, c);
        add(v, u, 0);
    }

    printf("%lld\n", dinic());
    return 0;
}
