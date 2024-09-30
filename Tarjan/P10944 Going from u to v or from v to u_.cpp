#include <cstring>
#include <stdio.h>
struct Edge
{
    int v, p;
} e[6005];
int ed[1005], cnt;
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
inline int min(int a, int b)
{
    return a < b ? a : b;
}
int dfn[1005], low[1005], stk[1005], pos[1005], rd[1005], cd[1005], top, gtm, pts;
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
            pos[t = stk[top--]] = pts;
        while (t != x);
    }
}

int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        memset(ed, 0, sizeof ed);
        memset(rd, 0, sizeof rd);
        memset(cd, 0, sizeof cd);
        memset(pos, 0, sizeof pos);
        memset(dfn, 0, sizeof dfn);
        memset(low, 0, sizeof low);
        gtm = pts = top = cnt = 0;
        int n, m;
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            add(u, v);
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
        int c1 = 0, c2 = 0;
        for (int i = 1; i <= pts; ++i)
        {
            c1 += !cd[i];
            c2 += !rd[i];
        }
        if (c1 ^ 1 || c2 ^ 1)
            printf("No\n");
        else
            printf("Yes\n");
    }
    return 0;
}
