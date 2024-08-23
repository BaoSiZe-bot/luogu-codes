#include <bitset>
#include <stdio.h>
template <const int N> class GR
{
    struct Edge
    {
        int v, w, p;
    } e[N];
    int ed[N], cnt = 0;

public:
    inline void add(int u, int v, int w)
    {
        e[++cnt] = {v, w, ed[u]};
        ed[u] = cnt;
    }
    inline int gd(int x)
    {
        return ed[x];
    }
    inline Edge ge(int x)
    {
        return e[x];
    }
};
GR<1000005> g;
std::bitset<1000005> f;
int d[1000005], pr[1000005], mp;
inline void dfs(int rt, int fa)
{
    pr[rt] = fa;
    mp = d[mp] < d[rt] ? rt : mp;
    for (int i = g.gd(rt); i; i = g.ge(i).p)
    {
        int to = g.ge(i).v;
        if (to ^ fa && !f.test(to))
        {
            d[to] = d[rt] + g.ge(i).w;
            dfs(to, rt);
        }
    }
}
int main()
{
    int n, s;
    scanf("%d%d", &n, &s);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.add(u, v, w);
        g.add(v, u, w);
    }
    d[1] = 1;
    dfs(1, 0);
    d[mp] = 0;
    dfs(mp, 0);
    int res = 0x7fffffff, p1 = mp, p2 = mp;
        for (; p1; p1 = pr[p1])
    {
        int l = s + d[p1];
        for (; d[p2] > l; p2 = pr[p2])
            ;
        res = std::min(res, std::max(d[mp] - d[p2], d[p1]));
    }
    for (int i = mp; i; i = pr[i])
        f.set(i);
    for (int i = mp; i; i = pr[i])
    {
        mp = i;
        d[mp] = 0;
        dfs(i, pr[i]);
    }
    for (int i = 1; i <= n; i++)
        res = std::max(res, d[i]);
    printf("%d\n", res);
    return 0;
}
