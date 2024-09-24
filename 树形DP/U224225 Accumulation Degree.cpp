#include <cstring>
#include <stdio.h>

struct Edge
{
    int v, w, p;
} e[400005];
int ed[200005], du[200005], dp[200005], t[200005], cnt, T, n;
inline void add(int u, int v, int w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}

inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline int max(int a, int b)
{
    return a < b ? b : a;
}
inline void dfs(int rt, int fa)
{
    t[rt] = 0;
    for (int i = ed[rt]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (to ^ fa)
        {
            dfs(to, rt);
            if (du[to] == 1)
                t[rt] += e[i].w;
            else
                t[rt] += min(t[to], e[i].w);
        }
    }
}
inline void d2f(int rt, int fa)
{
    for (int i = ed[rt]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (to ^ fa)
        {
            if (du[to] == 1)
                dp[to] = t[to] + min(dp[rt] - e[i].w, e[i].w);
            else if (du[rt] == 1)
                dp[to] = t[to] + e[i].w;
            else
                dp[to] = t[to] + min(dp[rt] - min(e[i].w, t[to]), e[i].w);
            d2f(to, rt);
        }
    }
}
int main()
{
    scanf("%d", &T);
    while (T--)
    {
        memset(t, 0, sizeof t);
        memset(ed, 0, sizeof ed);
        memset(dp, 0, sizeof dp);
        memset(du, 0, sizeof du);
        scanf("%d", &n);
        for (int i = 1; i < n; ++i)
        {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            add(x, y, z);
            add(y, x, z);
            du[x]++;
            du[y]++;
        }
        dfs(1, -1);
        dp[1] = t[1];
        d2f(1, 0);
        int mx = 0;
        for (int i = 1; i <= n; ++i)
            mx = max(mx, dp[i]);
        printf("%d\n", mx);
    }
    return 0;
}
