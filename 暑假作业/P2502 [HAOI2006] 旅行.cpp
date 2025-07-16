#include <limits>
#include <stdio.h>
#include <string.h>
#include <algorithm>
using dl = double;
template <const int N> struct GR
{
    struct Edge
    {
        int u, v, p, d;
        bool operator<(const Edge &oth) const
        {
            return d > oth.d;
        }
    } e[N];
    int ed[N], cnt = 0;
    inline void add(int u, int v, int d)
    {
        e[++cnt] = {u, v, ed[u], d};
        ed[u] = cnt;
    }
};
GR<505> g;
int p[405], h[505];
inline int fd(int x)  // find parent
{
    return ~p[x] ? p[x] = fd(p[x]) : x;
}
inline void mg(int u, int v)  // merge u, v
{
    u = fd(u);
    v = fd(v);
    if (u ^ v)
    {
        if (h[u] <= h[v])
            p[u] = v;
        else
            p[v] = u;
        if (h[u] == h[v])
            ++h[u];
    }
}
int main()
{
    int n, m, s, t, ra = 0, rb = 0;
    scanf("%d%d", &n, &m);
    memset(p, -1, sizeof(int) * (n + 5));
    for (int i = 1; i <= m; ++i)
    {
        int u, v, d;
        scanf("%d%d%d", &u, &v, &d);
        g.add(u, v, d);
        mg(u, v);
    }
    scanf("%d%d", &s, &t);
    if (fd(s) ^ fd(t))
        return 0 * printf("IMPOSSIBLE\n");
    std::sort(g.e + 1, g.e + 1 + g.cnt);
    dl res = std::numeric_limits<float>::max();
    for (int i = 1; i <= m; ++i)
    {
        int w = g.e[i].d;
        memset(p, -1, sizeof(int) * (n + 5));
        for (int j = i; j <= m; ++j)
        {
            int to = g.e[j].v, fr = g.e[j].u;
            mg(fr, to);
            if (!(fd(s) ^ fd(t)))
            {
                dl t = w * 1.0 / g.e[j].d;
                if (t < res)
                {
                    res = t;
                    ra = w;
                    rb = g.e[j].d;
                }
            }
        }
    }
    if (ra / rb * rb == ra)
        printf("%d", ra / rb);
    else
        printf("%d/%d", ra / std::__gcd(ra, rb), rb / std::__gcd(ra, rb));
    return 0;
}
