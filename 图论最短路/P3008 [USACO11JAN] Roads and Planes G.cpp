#include <queue>
#include <stdio.h>
#include <string.h>
struct Edge
{
    int v, w, p;
} e[200005], g[200005];
int ed[100005], hd[200005], rd[200005], cnt, tot;
inline void add(int u, int v, int w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
inline void lnk(int u, int v, int w)
{
    g[++tot] = {v, w, hd[u]};
    rd[v]++;
    hd[u] = tot;
}
int d[100005];
int f[100005], gtm;
inline void dij(int s)
{
    ++gtm;
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    pq.push({0, s});
    d[s] = 0;
    while (!pq.empty())
    {
        int nw = pq.top().second;
        pq.pop();
        if (f[nw])
            continue;
        f[nw] = gtm;
        for (int i = ed[nw]; i; i = e[i].p)
        {
            int to = e[i].v;
            if (!f[to] && d[to] > d[nw] + e[i].w)
            {
                d[to] = d[nw] + e[i].w;
                pq.push({d[to], to});
            }
        }
    }
}
int t, r, p, s;
int q[100005];
inline void topo(int rr[], int d[])
{
    int hed = 1, tal = 0;
    for (int i = 1; i <= gtm; i++)
        if (!rr[i])
            q[++tal] = i;
    while (hed <= tal)
    {
        int p = q[hed++];
        for (int i = hd[p]; i; i = g[i].p)
        {
            int to = e[i].v;
            --rr[to];
            if (!rr[to])
                q[++tal] = to;
        }
    }
}
int main()
{
    scanf("%d%d%d%d", &t, &r, &p, &s);
    for (int i = 1; i <= r; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    memset(d, 0x3f, sizeof(d));
    for (int i = 1; i <= t; ++i)
        if (!f[i])
        {
            ++tot;
            dij(i);
        }
    for (int i = 1; i <= p; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        lnk(f[u], f[v], w);
    }
    return 0;
}
