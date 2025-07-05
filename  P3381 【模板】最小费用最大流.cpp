#include <stdio.h>
#include <string.h>

const long long INF = 0x3f3f3f3f3f3f3f3f;
#define N 505
#define M 100005

int n, m, s, t, cnt;

long long min(long long a, long long b)
{
    return a < b ? a : b;
}
int ed[N];
struct Edge
{
    long long w;
    int v, p;
} e[M << 1];
void add(int u, int v, long long w)
{
    e[cnt].w = w;
    e[cnt].v = v;
    e[cnt].p = ed[u];
    ed[u] = cnt++;
}

int lev[N];
int q[N << 8], vis[N], cur[N];
int spfa()
{
    memset(vis + 1, 0, sizeof(int) * n);
    memset(lev + 1, 0xff, sizeof(int) * n);
    memcpy(cur + 1, ed + 1, sizeof(int) * n);

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

long long dfs(int x, long long lim)
{
    if (x == t)
        return lim;
    vis[x] = 1;
    long long sf = 0;
    for (int i = cur[x]; lim > 0 && ~i; cur[x] = i = e[i].p)
    {
        int to = e[i].v;
        long long pf;
        if (!vis[to] && lev[to] == lev[x] + 1 && e[i].w > 0 && (pf = dfs(to, min(lim - sf, e[i].w))))
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

long long dinic()
{
    long long fl = 0, pf;
    while (spfa())
        while ((pf = dfs(s, INF)))
            fl += pf;
    return fl;
}

int main()
{
    scanf("%d%d%d%d", &n, &m, &s, &t);
    memset(ed + 1, -1, sizeof(int) * n);

    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        long long w;
        scanf("%d%d%lld", &u, &v, &w);
        add(u, v, w);
        add(v, u, 0);
    }
    printf("%lld\n", dinic());
    return 0;
}
