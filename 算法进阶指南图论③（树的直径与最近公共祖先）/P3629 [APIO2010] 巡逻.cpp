#include <cstring>
#include <stdio.h>
struct Edge
{
    int u, v, w, p;
} e[200005];
int ed[100005], d[100005], p[100005], cnt, res, mx;
inline void add(int u, int v, int w)
{
    e[++cnt] = {u, v, w, ed[u]};
    ed[u] = cnt;
}
inline void cmax(int &a, int b)
{
    a = a < b ? b : a;
}
inline void dfs(int rt, int fa)
{
    if (d[rt] > d[res])
        res = rt;
    for (int i = ed[rt]; i; i = e[i].p)
    {
        int to = e[i].v, w = e[i].w;
        if (to ^ fa)
        {
            p[to] = i;
            d[to] = d[rt] + w;
            dfs(to, rt);
        }
    }
}
inline void dp(int rt, int fa)
{
    d[rt] = 0;
    for (int i = ed[rt]; i; i = e[i].p)
    {
        int to = e[i].v, w = e[i].w;
        if (to ^ fa)
        {
            dp(to, rt);
            cmax(mx, d[rt] + d[to] + w);
            cmax(d[rt], d[to] + w);
        }
    }
}
int main()
{
    int n, t;
    scanf("%d%d", &n, &t);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v, 1);
        add(v, u, 1);
    }
    dfs(1, 0);
    int k = res, l = 0;
    d[res] = 0;
    res = 0;
    dfs(k, 0);
    l = d[res];
    while (res ^ k)
    {
        if (p[res] & 1)
            e[p[res] + 1].w = -1;
        else
            e[p[res] - 1].w = -1;
        e[p[res]].w = -1;
        res = e[p[res]].u;
    }
    if (t == 1)
        dp(1, 0);
    printf("%d", n + n - l - mx);
    return 0;
}
