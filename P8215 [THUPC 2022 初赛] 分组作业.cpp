#include <stdio.h>
#include <string.h>

using ll = long long;
const ll INF = 0x3f3f3f3f3f3f3f3f;
#define N 500005
#define M 1000005

int cnt;

ll min(ll a, ll b)
{
    return a < b ? a : b;
}
int ed[N];
struct Edge
{
    ll w;
    int v, p;
} e[M << 1];
void add(int u, int v, ll w)
{
    e[cnt].w = w;
    e[cnt].v = v;
    e[cnt].p = ed[u];
    ed[u] = cnt++;


    e[cnt].w = 0;
    e[cnt].v = u;
    e[cnt].p = ed[v];
    ed[v] = cnt++;
}

ll lev[N];
int q[N << 8], vis[N], cur[N];
int bfs(int s, int t)
{
    memset(vis, 0, sizeof(int) * (t + 5));
    memset(lev, 0xff, sizeof(ll) * (t + 5));
    memcpy(cur, ed, sizeof(int) * (t + 5));

    int hd = 1, tl = 0;

    lev[s] = 0;
    q[++tl] = s;

    while (hd <= tl)
    {
        int u = q[hd++];

        for (int i = ed[u]; ~i; i = e[i].p)
        {
            int to = e[i].v;
            if (e[i].w > 0 && lev[to] == -1)
            {
                lev[to] = lev[u] + 1;
                q[++tl] = to;
            }
        }
    }

    return lev[t] != -1;
}

ll dfs(int x, int t, ll lim)
{
    if (x == t)
        return lim;
    vis[x] = 1;
    ll sf = 0;
    for (int i = cur[x]; lim > 0 && ~i; cur[x] = i = e[i].p)
    {
        int to = e[i].v;
        ll pf;
        if (!vis[to] && lev[to] == lev[x] + 1 && e[i].w > 0 && (pf = dfs(to, t, min(lim, e[i].w))))
        {
            e[i].w -= pf;
            e[i ^ 1].w += pf;
            sf += pf;
            lim -= pf;
            if (lim <= 0)
                break;
        }
    }
    vis[x] = 0;
    return sf;
}

ll dinic(int s, int t)
{
    ll fl = 0, pf;
    while (bfs(s, t))
        while ((pf = dfs(s, t, INF)))
            fl += pf;
    return fl;
}

int main()
{
    int n, m, s, t;
    scanf("%d%d", &n, &m);
    s = 0;
    t = n * 3 + 1;
    memset(ed, -1, sizeof(int) * (t + 5));
    for (int i = 1; i <= n * 2; i++)
    {
        int c, d;
        ll e;
        scanf("%d%d%lld", &c, &d, &e);
        add(s, i, d);
        add(i, t, c);
        if (i & 1)
            add(i, i + 1, e);
        else
            add(i, i - 1, e);
        add(n * 2 + ((i + 1) >> 1), i, INF);
    }
    for (int i = 1; i <= m; i++)
    {
        int A, B, a, b;
        scanf("%d%d%d%d", &A, &B, &a, &b);
        add(B, n * 2 + ((A + 1) >> 1), a);
        add(n * 2 + ((B + 1) >> 1), A, b);
    }
    printf("%lld\n", dinic(0, n * 3 + 1));
    return 0;
}
