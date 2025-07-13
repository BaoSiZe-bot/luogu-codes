#include <string.h>
#include <stdio.h>
#include <utility>
using ll = long long;
using pii = std::pair<ll, ll>;
const int N = 5005;
struct Edge
{
    ll v, w, p;
} e[10005];
ll ed[N], dis[N], vised[N], cnt, n, m;
bool vis[N];
inline void add(ll u, ll v, ll w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
ll q[N * N], hd, tl;
inline bool spfa(int s)
{
    memset(dis, 0xc0, sizeof(dis));
    tl = dis[s] = 0;
    hd = vis[s] = 1;
    q[++tl] = s;
    while (hd <= tl)
    {
        int nw = q[hd++];
        vis[nw] = 0;
        for (int i = ed[nw]; i; i = e[i].p)
        {
            int to = e[i].v;
            if (dis[to] < dis[nw] + e[i].w)
            {
                dis[to] = dis[nw] + e[i].w;
                if (!vis[to])
                {
                    if (++vised[to] > n)
                        return false;
                    q[++tl] = to;
                    vis[to] = 1;
                }
            }
        }
    }
    return true;
}

int main()
{
    scanf("%lld%lld", &n, &m);
    for (ll i = 1; i <= m; ++i)
    {
        ll u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        add(u, v, -w);
    }
    for (ll i = 1; i <= n; ++i)
        add(0, i, 0);
    if (!spfa(0))
        return 0 * printf("NO");
    for (ll i = 1; i <= n; ++i)
        printf("%lld ", dis[i]);
    return 0;
}
