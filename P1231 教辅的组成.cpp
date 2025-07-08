#include <algorithm>
#include <climits>
#include <cstdio>
#include <cstring>

const int INF = INT_MAX >> 1;
const int M = 3e6, N = 3e5;
struct Edge
{
    int w;
    int v, p;
} e[M];
int ed[N], cnt;
inline void add(int u, int v, int w)
{
    e[cnt] = {w, v, ed[u]};
    ed[u] = cnt++;
    e[cnt] = {0, u, ed[v]};
    ed[v] = cnt++;
}
int vis[N], lev[N], cur[N], q[M];
inline bool bfs(int s, int t)
{
    memset(lev, -1, sizeof lev);
    int hd = 1, tl = 0;
    q[++tl] = s;
    lev[s] = 0;
    vis[s] = 0;
    cur[s] = ed[s];
    while (hd <= tl)
    {
        int nw = q[hd++];
        for (int i = ed[nw]; ~i; i = e[i].p)
        {
            int to = e[i].v;
            if (lev[to] == -1 && e[i].w > 0)
            {
                lev[to] = lev[nw] + 1;
                cur[to] = ed[to];
                q[++tl] = to;
            }
        }
    }
    return lev[t] != -1;
}
int dfs(int x, int t, int lim)
{
    if (x == t)
        return lim;
    vis[x] = true;
    int fl = 0;
    for (int &i = cur[x]; lim > 0 && ~i; i = e[i].p)
    {
        int pf;
        int to = e[i].v;
        if (!vis[to] && e[i].w > 0 && lev[to] == lev[x] + 1 && (pf = dfs(to, t, std::min(lim, e[i].w))))
        {
            fl += pf;
            lim -= pf;
            e[i].w -= pf;
            e[i ^ 1].w += pf;
            if (lim <= 0)
                break;
        }
    }
    vis[x] = false;
    return fl;
}

int dinic(int s, int t)
{
    int fl = 0, pf = 0;
    while (bfs(s, t))
        while ((pf = dfs(s, t, INF)))
            fl += pf;
    return fl;
}
int main()
{
    memset(ed, -1, sizeof ed);
    int n1, n2, n3, m1, m2, s, t;
    scanf("%d%d%d", &n1, &n2, &n3);
    s = 0, t = n1 + n1 + n2 + n3 + 1;
    auto get = [n1, n2, n3](int x, int t) { return t == 1 ? x : t == 2 ? n2 + x : t == 3 ? n1 + n2 + x : n1 + n1 + n2 + x; };
    // 1 means practise-book, 2 means book's entrance-node, 3 means book's exit-node, 4 means answer-book
    // from practise-book to book then answer-book
    for (int i = 1; i <= n1; ++i)
        add(get(i, 2), get(i, 3), 1);
    for (int i = 1; i <= n2; ++i)
        add(s, get(i, 1), 1);
    for (int i = 1; i <= n3; ++i)
        add(get(i, 4), t, 1);
    scanf("%d", &m1);
    for (int i = 1; i <= m1; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        add(get(y, 1), get(x, 2), 1);
    }
    scanf("%d", &m2);
    for (int i = 1; i <= m2; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        add(get(x, 3), get(y, 4), 1);
    }
    printf("%d\n", dinic(s, t));
    return 0;
}
