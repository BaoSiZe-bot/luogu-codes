#include <stdio.h>
#include <string.h>

const int INF = 0x3f3f3f3f;
#define N 10005
#define M 100005

int n, m, cnt, tot;

int min(int a, int b)
{
    return a < b ? a : b;
}
int ed[N];
struct Edge
{
    int w;
    int v, p;
} e[M << 1];
void add(int u, int v, int w)
{
    e[cnt].w = w;
    e[cnt].v = v;
    e[cnt].p = ed[u];
    ed[u] = cnt++;

    e[cnt].w = w;
    e[cnt].v = u;
    e[cnt].p = ed[v];
    ed[v] = cnt++;
}
int fl[N], lev[N];
int q[N << 8], vis[N], cur[N];
int spfa(int s, int t)
{
    memset(vis, 0, sizeof(int) * (tot + 5));
    memset(lev, 0xff, sizeof(int) * (tot + 5));
    memcpy(cur, ed, sizeof(int) * (tot + 5));

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

int dfs(int x, int t, int lim)
{
    if (x == t)
        return lim;
    vis[x] = 1;
    int sf = 0;
    for (int i = cur[x]; lim > 0 && ~i; cur[x] = i = e[i].p)
    {
        int to = e[i].v, pf;
        if (!vis[to] && lev[to] == lev[x] + 1 && e[i].w > 0 && (pf = dfs(to, t, min(lim - sf, e[i].w))))
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

int dinic(int s, int t)
{
    int fl = 0, pf;
    while (spfa(s, t))
        while ((pf = dfs(s, t, INF)))
            fl += pf;
    return fl;
}

int get(int i, int j)
{
    return (i - 1) * m + j;
}

int main()
{
    scanf("%d%d", &n, &m);
    tot = n * m;
    memset(ed + 1, -1, sizeof(int) * (tot + 5));
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j < m; ++j)
        {
            int x;
            scanf("%d", &x);
            add(get(i, j), get(i, j + 1), x);
        }
    for (int i = 1; i < n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            int x;
            scanf("%d", &x);
            add(get(i, j), get(i + 1, j), x);
        }
    for (int i = 1; i < n; ++i)
        for (int j = 1; j < m; ++j)
        {
            int x;
            scanf("%d", &x);
            add(get(i, j), get(i + 1, j + 1), x);
        }

    printf("%d\n", dinic(1, tot));
    return 0;
}