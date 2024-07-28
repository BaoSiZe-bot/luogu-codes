#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
const int N = 100005;
struct GR
{
    struct Edge
    {
        int v, p;
    } e[N];
    int ed[N], cnt = 0;
    inline void add(int u, int v)
    {
        e[++cnt] = {v, ed[u]};
        ed[u] = cnt;
    }
} g, ge, gf;
int dfn[N], low[N], stk[N], pos[N], ptc[N], rd[N], cd[N], q[4 * N], cnt, top, gtm, pts, n, m, hd, tl;  // global time
int d1[N], d2[N];
inline void tarjan(int x)
{
    dfn[x] = low[x] = ++gtm;
    stk[++top] = x;
    for (int i = g.ed[x]; i; i = g.e[i].p)
    {
        int to = g.e[i].v;
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
        int t = 0;
        do
            ptc[pos[t = stk[top--]] = pts]++;
        while (t != x);
    }
}
inline void topo(int rr[], int d[], const GR &gg)
{
    d[pos[1]] = ptc[pos[1]];
    hd = 1;
    tl = 0;
    for (int i = 1; i <= pts; i++)
        if (!rr[i])
            q[++tl] = i;
    while (hd <= tl)
    {
        int p = q[hd++];
        // printf("p=%d,gg.ed[p]=%d.\n", p, gg.ed[p]);
        for (int i = gg.ed[p]; i; i = gg.e[i].p)
        {
            int to = gg.e[i].v;
            // printf("%d->%d,d:%d->", p, to, d[to]);
            d[to] = max(d[to], d[p] + ptc[to]);
            // printf("%d\n", d[to]);
            --rr[to];
            if (!rr[to])
                q[++tl] = to;
        }
    }
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y;
        scanf("%d%d", &x, &y);
        g.add(x, y);
    }
    for (int i = 1; i <= n; ++i)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= n; ++i)
        for (int j = g.ed[i]; j; j = g.e[j].p)
        {
            int to = g.e[j].v;
            if (pos[i] ^ pos[to])
            {
                ge.add(pos[i], pos[to]);
                gf.add(pos[to], pos[i]);
                ++rd[pos[i]];
                ++cd[pos[to]];
            }
        }
    memset(d1, 0xef, sizeof d1);
    memset(d2, 0xef, sizeof d2);
    topo(rd, d1, gf);
    topo(cd, d2, ge);
    // for (int i = 1 ; i <= n; ++i)
    //     printf("%d is in %d=%d, d1:%d,d2:%d\n", i, pos[i], ptc[pos[i]], d1[pos[i]], d2[pos[i]]);
    int res = ptc[pos[1]];
    for (int i = 1; i <= n; ++i)
        for (int j = g.ed[i]; j; j = g.e[j].p)
        {
            int to = g.e[j].v;
            if (pos[i] ^ pos[to])
            {
                // if (i == 3 && to == 5)
                    // printf("%d %d %d %d\n", d1[pos[i]], d2[pos[to]], ptc[pos[1]], d1[pos[i]] + d2[pos[to]] - ptc[pos[1]]);
                res = max(res, d2[pos[to]] + d1[pos[i]] - ptc[pos[1]]);
            }
        }
    printf("%d\n", res);
    return 0;
}
/*
1 is in 3=1
2 is in 2=3
3 is in 5=1
4 is in 2=3
5 is in 1=1
6 is in 4=1
7 is in 2=3
1
*/


/*
1 is in 3=1, d1:1, d2:1
2 is in 2=3, d1:-269488145, d2:-269488145
3 is in 5=1, d1:-269488145, d2:-269488145
4 is in 2=3, d1:-269488145, d2:-269488145
5 is in 1=1, d1:-269488145, d2:-269488145
6 is in 4=1, d1:-269488145, d2:-269488145
7 is in 2=3, d1:-269488145, d2:-269488145
1
*/
