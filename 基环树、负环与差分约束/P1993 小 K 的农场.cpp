#include <stdio.h>
#include <string.h>

const int N = 4000005, M = 150005;
struct Edge
{
    int v, w, p;
} e[M];
int ed[N], tot[N], d[N], q[N], cnt, n, m;
bool f[N];
inline void add(int u, int v, int w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
inline bool spfa(int s)
{
    memset(d, 0x3f, sizeof d);
    d[s] = 0;
    int hd = 1, tl = 0;
    q[++tl] = s;
    tot[s] = 1;
    while (hd <= tl)
    {
        int nw = q[hd++];
        f[nw] = 0;
        for (int i = ed[nw]; i; i = e[i].p)
        {
            int to = e[i].v;
            if (d[nw] + e[i].w < d[to])
            {
                d[to] = d[nw] + e[i].w;
                if (!f[to])
                {
                    q[++tl] = to;
                    f[to] = 1;
                    tot[to]++;
                    if (tot[to] >= n + 1)
                        return false;
                }
            }
        }
    }
    return true;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int op, u, v, w;
        scanf("%d%d%d", &op, &u, &v);
        if (op == 3)
        {
            add(u, v, 0);
            add(v, u, 0);
            continue;
        }
        scanf("%d", &w);
        if (op & 1)
            add(u, v, -w);//d[v]>=d[u]+w
        else
            add(v, u, w);
    }
    for (int i = 1; i <= n; ++i)
        add(0, i, 0);
    printf(spfa(0) ? "Yes" : "No");
    return 0;
}
