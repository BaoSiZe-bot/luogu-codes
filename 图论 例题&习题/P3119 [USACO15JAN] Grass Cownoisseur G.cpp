#include <cstdio>
#include <bits/stl_pair.h>
struct Edge
{
    int v, p;
} e[500005], pe[500005];
int a[500005], ed[500005], ep[500005], sp[500005], dp[500005], dfn[500005], low[500005], stk[500005], pos[500005], du[500005], cnt, top, gtm, pts, hd = 1, tl, pnt;  //global-time
std::pair<int, int> q[500005];
inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline int max(int a, int b)
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
           sp[pos[t = stk[top--]] = pts] += a[t];
        while (t != x);
    }
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    while(m--)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        e[++cnt] = {v, ed[u]};
        ed[u] = cnt;
    }
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    int st, edc;
    scanf("%d%d", &st, &edc);
    tarjan(st);
    for (int i = 1; i <= n; ++i)
    {
        if (!pos[i])
            continue;
        for (int j = ed[i]; j; j = e[j].p)
            if (pos[i] ^ pos[e[j].v])
            {
                du[pos[e[j].v]]++;
                pe[++pnt] = {pos[e[j].v], ep[pos[i]]};
                ep[pos[i]] = pnt;
            }
    }
    for (int i = 1; i <= pts; ++i)
        dp[i] = sp[i];
    q[++tl] = {pos[st], sp[pos[st]]};
    while (hd <= tl)
    {
        auto nw = q[hd++];
        for (int i = ep[nw.first]; i; i = pe[i].p)
        {
            int to = pe[i].v;
            --du[to];
            dp[to] = max(dp[to], nw.second + sp[to]);
            if (!du[to])
                q[++tl] = {to, dp[to]};
        }
    }
    int res = 0;
    while (edc--)
    {
        int bar;
        scanf("%d", &bar);
        res = max(res, dp[pos[bar]]);
    }
    printf("%d\n", res);
    return 0;
}
