#include <cstdio>
struct Edge
{
    int v, p;
} e[50005];
int ed[10005], dfn[10005], low[10005], stk[10005], pos[10005], ptc[10005], du[10005], cnt, top, gtm, pts;  //global-time
inline int min(int a, int b)
{
    return a < b ? a : b;
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
    for (int i = 1, u, v; i <= m; ++i)
    {
        scanf("%d%d", &u, &v);
        e[++cnt] = {v, ed[u]};
        ed[u] = cnt;
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; ++i)
        for (int j = ed[i]; j; j = e[j].p)
            if (pos[e[j].v] != pos[i])
                du[pos[i]]++;
    int res = -1;
    for (int i = 1; i <= pts; ++i)
        if (!du[pos[i]])
        {
            if (~res)
                return 0 * printf("0");
            res = ptc[i];
        }
    return 0 * printf("%d", res);
}
