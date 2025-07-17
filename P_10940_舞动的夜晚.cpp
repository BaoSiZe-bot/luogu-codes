#include <cstdio>
#include <cstring>
#include <set>
#include <tuple>
#include <vector>

const int INF = 0x3f3f3f3f;
const int N = 5e5 + 5, M = 1e6 + 5;

int min(int a, int b)
{
    return a < b ? a : b;
}

template <const int V, const int E> struct Graph
{
    int ed[V], cnt;
    struct Edge
    {
        int w;
        int v, p;
    } e[E];
    void clr()
    {
        memset(ed, -1, sizeof(ed));
        cnt = 0;
    }
    Graph()
    {
        clr();
    }
    void add_edge(int u, int v, int w)
    {
        e[cnt].w = w;
        e[cnt].v = v;
        e[cnt].p = ed[u];
        ed[u] = cnt++;
    }
    void add(int u, int v, int w)
    {
        add_edge(u, v, w);
        add_edge(v, u, 0);
    }
};
using GP = Graph<N, M << 1>;
GP og, tg;

int lev[N];
int q[N << 8], vis[N], cur[N];
int spfa(const GP &G, const int &s, const int &t)
{
    memset(vis + s, 0, sizeof(int) * (t - s + 5));
    memset(lev + s, 0xff, sizeof(int) * (t - s + 5));
    memcpy(cur + s, G.ed + s, sizeof(int) * (t - s + 5));

    int hd = 1, tl = 0;

    lev[s] = 0;
    q[++tl] = s;

    while (hd <= tl)
    {
        int u = q[hd++];

        for (int i = G.ed[u]; ~i; i = G.e[i].p)
        {
            int to = G.e[i].v;
            if (G.e[i].w > 0 && lev[to] == -1)
            {
                lev[to] = lev[u] + 1;
                q[++tl] = to;
            }
        }
    }

    return lev[t] != -1;
}

int dfs(GP &G, const int &x, const int &t, int lim)
{
    if (x == t)
        return lim;
    int sf = 0;
    for (int i = cur[x]; lim > sf && ~i; cur[x] = i = G.e[i].p)
    {
        int to = G.e[i].v;
        int pf;
        if (lev[to] == lev[x] + 1 && G.e[i].w > 0 && (pf = dfs(G, to, t, min(lim - sf, G.e[i].w))))
        {
            G.e[i].w -= pf;
            G.e[i ^ 1].w += pf;
            sf += pf;
        }
    }
    return sf;
}

int dinic(GP &G, const int &s, const int &t)
{
    int fl = 0, pf;
    while (spfa(G, s, t))
        while ((pf = dfs(G, s, t, INF)))
            fl += pf;
    return fl;
}

int dfn[N], low[N], stk[N], pos[N], top, gtm, pts;
inline void tarjan(const GP &G, int x)
{
    dfn[x] = low[x] = ++gtm;
    stk[++top] = x;
    for (int i = G.ed[x]; ~i; i = G.e[i].p)
    {
        int to = G.e[i].v;
        if (!dfn[to])
        {
            tarjan(G, to);
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

std::vector<std::tuple<int, int, int>> edg;
int main()
{
    int n, m, k, s, t;
    scanf("%d%d%d", &n, &m, &k);
    s = 0, t = n + m + 1;
    for (int i = 1; i <= k; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        edg.emplace_back(u, n + v, i);
        og.add(u, n + v, 1);
    }
    for (int i = 1; i <= n; ++i)
        og.add(s, i, 1);
    for (int i = 1; i <= m; ++i)
        og.add(n + i, t, 1);
    dinic(og, s, t);
    for (int u = 0; u <= t; ++u)
        for (int i = og.ed[u]; ~i; i = og.e[i].p)
            if (og.e[i].w > 0)
                tg.add_edge(u, og.e[i].v, 0); 
    for (int i = 0; i <= t; ++i)
        if (!dfn[i])
            tarjan(tg, i);
    std::set<int> res;
    for (const auto &[u, v, id] : edg)
        if (!og.e[2 * id - 1].w && pos[u] ^ pos[v])
            res.insert(id);
    printf("%d\n", (int)res.size());
    for (const auto &i : res)
        printf("%d ", i);
    return 0;
}
