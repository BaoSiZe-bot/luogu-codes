#include <cstdio>
int n, m;
struct Edge
{
    int v, p;
} e[1000005];
int ed[1000005], stk[1000005], res[1000005], tp, cnt, tot;
bool vis[1000005];
inline void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    stk[++tp] = 1;
    while (tp)
    {
        int rt = stk[tp], id = ed[rt];
        while (id && vis[id])
            id = e[id].p;
        if (!id)
        {
            --tp;
            res[++tot] = rt;
            continue;
        }
        stk[++tp] = e[id].v;
        vis[id] = 1;
        ed[rt] = e[id].p;
    }
    for (int i = 1; i <= tot; ++i)
        printf("%d\n", res[i]);
    return 0;
}
