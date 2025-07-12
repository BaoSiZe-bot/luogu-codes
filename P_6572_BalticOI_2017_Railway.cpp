#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>

using std::set;
using std::sort;
using ll = long long;

const int M = 5e5 + 5, N = 5e5 + 5;
int n, m, s;

template <const int M, const int N> struct Graph
{
    struct Edge
    {
        int u, v, w, p;
    } e[M];
    int ed[N], cnt;
    inline void add(int u, int v, int w)
    {
        e[++cnt] = {u, v, w, ed[u]};
        ed[u] = cnt;
    }
};
Graph<M, N> og, eg;

ll f[N];
int dfn[N], pt;
int d[N], id[N], fa[22][N];
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
            id[to] = og.e[i].w;

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
    eg.cnt = 0;
    sort(h + 1, h + s + 1, [](int a, int b) { return dfn[a] < dfn[b]; });
    stk[top = 1] = h[1];
}
inline void build()
{
    for (int i = 1; i <= s; ++i)
    {
        int x = h[i];
        if (x == 1)
            continue;
        if (top == 1)
        {
            stk[++top] = x;
            continue;
        }
        int p = lca(stk[top], x);
        if (p != stk[top])
        {
            for (; top > 1 && dfn[stk[top - 1]] >= dfn[p]; --top)
                eg.add(stk[top - 1], stk[top], 0);
            if (stk[top] != p)
            {
                eg.add(p, stk[top], 0);
                stk[top] = p;
            }
        }
        stk[++top] = x;
    }
    for (; top > 1; --top)
        eg.add(stk[top - 1], stk[top], 0);
    for (int i = 1; i <= eg.cnt; ++i)
    {
        int fr = eg.e[i].u, to = eg.e[i].v;
        eg.ed[fr] = eg.ed[to] = 0;  // Lazy-clean edges.
        f[to]++;
        f[fr]--;
    }
}

void sum(int x, int fa)
{
    for (int i = og.ed[x]; i; i = og.e[i].p)
    {
        int to = og.e[i].v;
        if (to != fa)
        {
            sum(to, x);
            f[x] += f[to];
        }
    }
}

int main()
{
    int k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        og.add(u, v, i);
        og.add(v, u, i);
    }
    pre(1, 0);
    while (m--)
    {
        scanf("%d", &s);
        for (int i = 1; i <= s; ++i)
            scanf("%d", &h[i]);
        clr();
        build();
    }
    sum(1, -1);
    set<int> st;
    for (int i = 1; i <= n; ++i)
        if (f[i] >= k)
            st.insert(id[i]);
    printf("%d\n", (int)st.size());
    for (auto u : st)
        printf("%d ", u);
    return 0;
}