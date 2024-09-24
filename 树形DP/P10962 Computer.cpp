#include <cstring>
#include <stdio.h>
struct Edge
{
    int v, w, p;
} e[2005];
int ed[1005], d1[1005], d2[1005], cnt, mx, mp, z;
inline void add(int u, int v, int w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
void dfs(int d[], int rt, int fa)
{
    if (d[rt] > mx)
    {
        mx = d[rt];
        mp = rt;
    }
    for (int i = ed[rt]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (to ^ fa)
        {
            d[to] = d[rt] + e[i].w;
            dfs(d, to, rt);
        }
    }
}
inline int max(int a, int b)
{
    return a < b ? b : a;
}
int main()
{
    int n;
    while (~scanf("%d", &n))
    {
        memset(ed, 0, sizeof ed);
        memset(d1, 0, sizeof d1);
        memset(d2, 0, sizeof d2);
        for (int i = 2; i <= n; ++i)
        {
            int v, w;
            scanf("%d%d", &v, &w);
            add(i, v, w);
            add(v, i, w);
        }
        mx = 0;
        mp = 1;
        dfs(d1, 1, 0);
        mx = 0;
        z = mp;
        mp = 1;
        dfs(d2, z, 0);
        for (int i = 1; i <= n; ++i)
            printf("%d\n", max(d1[i] + d1[mp], d2[i]));
    }
    return 0;
}
