#include <algorithm>
#include <cstdio>
#include <cstring>

using std::sort;
using ll = long long;

const int M = 5e5 + 5, N = 5e5 + 5;
int n, m, k;

template <const int M, const int N> struct Graph
{
    struct Edge
    {
        int v, w, p;
    } e[M];
    int ed[N], cnt;
    inline void add(int u, int v, int w)
    {
        e[++cnt] = {v, w, ed[u]};
        ed[u] = cnt;
    }
};
Graph<M, N> og, eg;

int dfn[N], pt;
ll f[N], mv[N];
int d[N], fa[22][N];
inline void pre(int x, int f)
{
    d[x] = d[f] + 1;
    dfn[x] = ++pt;
    for (int i = 1; i <= 20; ++i)
        fa[i][x] = fa[i - 1][fa[i - 1][x]];
    for (int i = og.ed[x]; i; i = og.e[i].p)
    {
        int to = og.e[i].v;
        if (to != f)
        {
            fa[0][to] = x;
            mv[to] = mv[x] < og.e[i].w ? mv[x] : og.e[i].w;
            pre(to, x);
        }
    }
}

inline int lca(int u, int v)
{
    if (d[u] < d[v])
        u ^= v ^= u ^= v;
    for (int i = 20; ~i; --i)
    {
        if (d[fa[i][u]] >= d[v])
            u = fa[i][u];
        if (u == v)
            return u;
    }
    for (int i = 20; ~i; --i)
        if (fa[i][u] != fa[i][v])
        {
            u = fa[i][u];
            v = fa[i][v];
        }
    return fa[0][u];
}

int h[N], stk[N], top;
inline void clr()
{
    memset(eg.ed, 0, sizeof(eg.ed));
    // for (int i = 1; i <= k; ++i)
        // eg.ed[h[i]] = 0;
    // eg.ed[1] = 0;
    eg.cnt = 0;
    stk[top = 1] = 1;
    sort(h + 1, h + k + 1, [](int a, int b) { return dfn[a] < dfn[b]; });
}
inline void build()
{
    for (int i = 1; i <= k; ++i)
        if (h[i] ^ 1)
        {
            if (top == 1)
            {
                stk[++top] = h[i];
                continue;
            }

            int p = lca(h[i], stk[top]);
            if (p != stk[top])
            {
                for (; top > 1 && dfn[stk[top - 1]] >= dfn[p]; --top)
                    eg.add(stk[top - 1], stk[top], 0);
                if (stk[top] != p)
                {
                    eg.add(p, stk[top], 0);
                    stk[top] = p;
                }
                stk[++top] = h[i];
            }
        }
    for (; top > 1; --top)
        eg.add(stk[top - 1], stk[top], 0);
}

inline ll dp(int x)
{
    if (!eg.ed[x])
        return f[x] = mv[x];
    f[x] = 0;
    for (int i = eg.ed[x]; i; i = eg.e[i].p)
        f[x] += dp(eg.e[i].v);
    eg.ed[x] = 0;
    return f[x] = (f[x] < mv[x] ? f[x] : mv[x]);
}

int main()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        og.add(u, v, w);
        og.add(v, u, w);
    }
    mv[1] = 0x7f7f7f7f7f7f7f7f;
    pre(1, 0);
    scanf("%d", &m);
    while (m--)
    {
        scanf("%d", &k);
        for (int i = 1; i <= k; ++i)
            scanf("%d", &h[i]);
        clr();
        build();
        dp(1);
        printf("%lld\n", f[1]);
    }
    return 0;
}