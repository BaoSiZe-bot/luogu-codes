#include <stdio.h>
struct Edge
{
    int v, p;
} e[205];
int ed[205], cnt, ml;
inline __attribute__((always_inline)) int max(int u, int v)
{
    return u < v ? v : u;
}
inline __attribute__((always_inline)) int min(int u, int v)
{
    return u < v ? u : v;
}
inline __attribute__((always_inline)) void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}
void dfs(int rt, int fa, int l)
{
    ml = max(ml, l);
    for (int i = ed[rt]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (to ^ fa)
            dfs(to, rt, l + 1);
    }
}
__attribute__((always_inline)) int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i < n; ++i)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    dfs(0, n, 1);
    printf("%d\n", m < ml ? m + 1 : min(n, ml + (m - ml + 1) / 2));
    return 0;
}
