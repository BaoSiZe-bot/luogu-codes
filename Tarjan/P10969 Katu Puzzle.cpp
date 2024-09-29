#include <iostream>
struct Edge
{
    int v, p;
} e[500005];
int ed[500005], cnt;
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
int ep[500005], dfn[500005], low[500005], stk[500005], pos[500005], top, gtm, pts;
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
        do
            pos[stk[top--]] = pts;
        while (stk[top + 1] != x);
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        char o, p, q;
        std::cin >> u >> v >> w >> o >> p;
        if (o == 'O')
        {
            if (w)
            {
                add(u, v + n);
                add(v, u + n);
            }
            else
            {
                add(u + n, u);
                add(v + n, v);
            }
            continue;
        }
        std::cin >> q;
        if (o == 'A')
        {
            if (w)
            {
                add(u, u + n);
                add(v, v + n);
            }
            else
            {
                add(u + n, v);
                add(v + n, u);
            }
        }
        else
        {
            if (w)
            {
                add(u, v + n);
                add(v, u + n);
                add(u + n, v);
                add(v + n, u);
            }
            else
            {
                add(u, v);
                add(v, u);
                add(u + n, v + n);
                add(v + n, u + n);
            }
        }
    }
    for (int i = 1; i < n * 2 - 1; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 0; i < n; ++i)
        if (pos[i] == pos[n + i])
            return 0 * printf("NO");
    printf("YES");
    return 0;
}
