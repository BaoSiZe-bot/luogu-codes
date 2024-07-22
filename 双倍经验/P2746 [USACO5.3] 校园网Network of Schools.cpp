#include <cstdio>
struct Edge
{
    int v, p;
} e[50005];
int ed[10005], dfn[10005], low[10005], stk[10005], pos[10005], ptc[10005], rd[10005], cd[10005], cnt, top, gtm, pts;  //global-time
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
            ptc[pos[t = stk[top--]] = pts]++;
        while (t != x);
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1, x; i <= n; ++i)
        while (scanf("%d", &x), x)
        {
            e[++cnt] = {x, ed[i]};
            ed[i] = cnt;
        }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; ++i)
        for (int j = ed[i]; j; j = e[j].p)
            if (pos[i] ^ pos[e[j].v])
            {
                cd[pos[i]]++;
                rd[pos[e[j].v]]++;
            }
    int res = 0, tot = 0;
    for (int i = 1; i <= pts; ++i)
    {
        res += !rd[i];
        tot += !cd[i];
    }
    tot = max(tot, res);
    if (pts == 1)
        res = 1, tot = 0;
    printf("%d\n%d", res, tot);
    return 0;
}
