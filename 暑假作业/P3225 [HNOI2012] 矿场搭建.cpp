#include <stdio.h>
#include <string.h>
#include <vector>
#define int long long
struct Edge
{
    int v, p;  //using GNU/EMACS OS and not done YASnippets.
} g[2005];
int dfn[1005], low[1005], ed[1005], stk[1005], tt[1005], top, gtm, pts, cnt;
std::vector<int> dcc[1005];
inline int max(int u, int v)
{
    return u < v ? v : u;
}
inline int min(int u, int v)
{
    return u < v ? u : v;
}
inline void add(int u, int v)
{
    g[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
inline void tarjan(int x)
{
    dfn[x] = low[x] = ++gtm;
    stk[++top] = x;
    int t = 0;
    for (int i = ed[x]; i; i = g[i].p)
    {
        int to = g[i].v;
        if (!dfn[to])
        {
            tarjan(to);
            low[x] = min(low[x], low[to]);
            if (dfn[x] <= low[to])
            {
                ++pts;
                ++t;
                if (t > 1 || x ^ 1)
                    tt[x] = 1;
                dcc[pts].push_back(x);
                int tp = 0;
                do
                {
                    tp = stk[top--];
                    dcc[pts].push_back(tp);
                } while (tp != to);
            }
        }
        else
            low[x] = min(low[x], dfn[to]);
    }
}
signed main()
{
    int n = 0, m, id = 0;
    while (~scanf("%lld", &m) && m)
    {
        ++id;
        gtm = pts = cnt = top = 0;
        memset(tt, 0, sizeof tt);
        memset(ed, 0, sizeof ed);
        memset(dfn, 0, sizeof dfn);
        memset(low, 0, sizeof low);
        for (int i = 1; i <= n; ++i)
            dcc[i].clear();
        n = 0;
        for (int i = 1; i <= m; ++i)
        {
            int u, v;
            scanf("%d%d", &u, &v);
            add(u, v);
            add(v, u);
            n = max(n, max(u, v));
        }
        tarjan(1);
        int tot = 0, t = 1;
        for (int i = 1; i <= pts; i++)
        {
            int x = dcc[i].size(), y = 0;
            for (int e : dcc[i])
                y += tt[e];
            if (y == 1)
            {
                tot++;
                t *= x - 1;
            }
            if (!y)
            {
                tot += 2;
                t *= x * (x - 1) / 2;
            }
        }
        printf("Case %lld: %lld %lld\n", id, tot, t);
    }
    return 0;
}
