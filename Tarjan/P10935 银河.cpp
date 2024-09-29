#include <stdio.h>
using ll = long long;
struct Edge
{
    int v;
    ll w;
    int p;
} e[500005], f[500005];
int q[1000005], ed[100005], hd[100005], du[100005], cnt, tot, top;
int dfn[100005], low[100005], stk[100005], pos[100005], gtm, pts;
ll dp[100005], ptc[1000005];
inline void add(int u, int v, ll w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
inline void lnk(int u, int v, ll w)
{
    f[++tot] = {v, w, hd[u]};
    du[v]++;
    hd[u] = tot;
}
inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline ll max(ll a, ll b)
{
    return a < b ? b : a;
}
inline void tarjan(int x)
{
    dfn[x] = low[x] = ++gtm;
    stk[++top] = x;
    for (int i = ed[x]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (!dfn[to])
        {
            tarjan(to);
            low[x] = min(low[x], low[to]);
        }
        else if (!pos[to])
            low[x] = min(low[x], dfn[to]);
    }
    if (dfn[x] == low[x])
    {
        ++pts;
        int t = 0;
        do
            ptc[pos[t = stk[top--]] = pts]++;
        while (t != x);
    }
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int t, a, b;
        scanf("%d%d%d", &t, &a, &b);
        switch (t)
        {
            case 5: add(a, b, 0); break;
            case 4: add(b, a, 1); break;
            case 3: add(b, a, 0); break;
            case 2: add(a, b, 1); break;
            default:
                add(a, b, 0);
                add(b, a, 0);
                break;
        }
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; ++i)
        for (int j = ed[i]; j; j = e[j].p)
        {
            int to = e[j].v;
            if (pos[i] == pos[to] && e[j].w)
                return 0 * printf("-1");
            if (pos[i] ^ pos[to])
                lnk(pos[i], pos[to], e[j].w);
        }
    int hed = 1, tal = 0;
    for (int i = 1; i <= pts; ++i)
        if (!du[i])
        {
            q[++tal] = i;
            dp[i] = 1;
        }
    ll res = 0;
    while (hed <= tal)
    {
        int nw = q[hed++];
        res += dp[nw] * ptc[nw];
        for (int i = hd[nw]; i; i = f[i].p)
        {
            int to = f[i].v;
            dp[to] = max(dp[to], dp[nw] + f[i].w);
            if (!--du[to])
                q[++tal] = to;
        }
    }
    return 0 * printf("%lld", res);
}
