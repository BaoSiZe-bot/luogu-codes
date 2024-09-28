#include <stdio.h>
#include <string.h>
struct Edge
{
    int v, w, p;
} e[20005];
int ed[1005], q[500005], d[1005], cnt, hd, tl, n, p, k;
inline bool bfs(int mid)
{
    memset(d, 0x3f, sizeof d);
    q[hd = tl = 250000] = 1;
    d[1] = 0;
    while (hd <= tl)
    {
        int nw = q[hd++];
        if (nw == n)
            return d[n] <= k;
        for (int i = ed[nw]; i; i = e[i].p)
        {
            int to = e[i].v, w = e[i].w;
            if (w <= mid)
            {
                if (d[nw] >= d[to])
                    continue;
                d[to] = d[nw];
                q[--hd] = to;
            }
            else
            {
                if (d[nw] + 1 >= d[to])
                    continue;
                d[to] = d[nw] + 1;
                q[++tl] = to;
            }
        }
    }
    return false;
}
inline void add(int u, int v, int w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
int main()
{
    scanf("%d%d%d", &n, &p, &k);
    for (int i = 1; i <= p; ++i)
    {
        int a, b, l;
        scanf("%d%d%d", &a, &b, &l);
        add(a, b, l);
        add(b, a, l);
    }
    int l = 0, r = 0x3f3f3f3f, res = 0x3f3f3f3f;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (bfs(mid))
        {
            res = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    if (res >= 0x3f3f3f3f)
        printf("-1");
    else
        printf("%d", res);
    return 0;
}
