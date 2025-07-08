#include <bits/stdc++.h>
#include <cstdio>
using namespace std;
using ll = long long;
const int M = 100005;
struct Edge
{
    int v, w, p;
} e[2005];
int ed[1005], cnt;
inline void add(int u, int v, int w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
int d[1005];
bool f[1005];
inline void dij()
{
    memset(d, 0x3f, sizeof(d));
    memset(f, 0, sizeof f);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    q.push({0, 1});
    d[1] = 0;
    while (!q.empty())
    {
        int nw = q.top().second;
        q.pop();
        if (f[nw])
            continue;
        f[nw] = 1;
        for (int i = ed[nw]; i; i = e[i].p)
        {
            int to = e[i].v;
            if (!f[to] && d[to] > d[nw] + e[i].w)
            {
                d[to] = d[nw] + e[i].w;
                q.push({d[to], to});
            }
        }
    }
}
int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int x, y, l;
        scanf("%d%d%d", &x, &y, &l);
        add(x, y, l);
        add(y, x, l);
    }
    dij();
    ll res = 1;
    for (int i = 2; i <= n; ++i)
    {
        ll tot = 0;
        for (int j = ed[i]; j; j = e[j].p)
            tot += (d[e[j].v] + e[j].w == d[i]);
        tot && ((res *= tot) %= M);
    }
    printf("%lld", res);
    return 0;
}
