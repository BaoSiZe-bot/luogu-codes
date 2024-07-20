#include <cstdio>
#include <cstring>
#include <queue>
using ll = long long;
struct Edge
{
    int v, p;
    ll d;
} e[200005];
int ed[200005], cnt;
bool vis[200005];
ll dis[200005];
inline void add(int u, int v, int w)
{
    e[++cnt] = {v, ed[u], w};
    ed[u] = cnt;
}
inline void dijkstra(int s)
{
    memset(dis, 0x7f, sizeof dis);
    std::priority_queue<std::pair<ll, int>, std::vector<std::pair<ll, int>>, std::greater<std::pair<ll, int>>> pq;
    pq.push({0, s});
    dis[s] = 0;
    while (!pq.empty())
    {
        int nw = pq.top().second;
        pq.pop();
        if (vis[nw])
            continue;
        vis[nw] = 1;
        for (int i = ed[nw]; i; i = e[i].p)
        {
            int to = e[i].v;
            if (dis[to] > dis[nw] + e[i].d)
            {
                dis[to] = dis[nw] + e[i].d;
                pq.push({dis[to], to});
            }
        }
    }
}
int main()
{
    ll h;
    int x, y, z;
    scanf("%lld%d%d%d", &h, &x, &y, &z);
    --h;
    for (int i = 0; i < x; ++i)
    {
        add(i, (i + y) % x, y);
        add(i, (i + z) % x, z);
    }
    dijkstra(0);
    ll res = 0;
    for (int i = 0; i < x; ++i)
        if (h >= dis[i])
            res += (h - dis[i]) / x + 1;
    printf("%lld\n", res);
    return 0;
}
