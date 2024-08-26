#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <queue>
#include <bits/stl_pair.h>
using ll = long long;
template <const int N> struct GR
{
private:
    struct Edge
    {
        int v, w, p;
    } e[N]{};
    int ed[N]{}, cnt = 0;

public:
    inline void add(int u, int v, int w)
    {
        e[++cnt] = {v, w, ed[u]};
        ed[u] = cnt;
    }
    inline Edge ge(int x)
    {
        return e[x];
    }
    inline int gd(int x)
    {
        return ed[x];
    }
};
inline ll min(ll x, ll y)
{
    return x < y ? x : y;
}
GR<100005> g;
bool f[105][105], vised[105], cvis[105];
int n, m, k, e, d;
ll dis[105], pr[105][105], dp[105];
inline void dij()
{
    for (int i = 1; i <= m; i++)
    {
        dis[i] = INT_MAX;
        vised[i] = 0;
    }
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> q;
    q.push({0, 1});
    dis[1] = 0;
    while (!q.empty())
    {
        int nw = q.top().second;
        q.pop();
        if (vised[nw])
            continue;
        vised[nw] = 1;
        for (int i = g.gd(nw); i; i = g.ge(i).p)
        {
            int to = g.ge(i).v;
            if (!cvis[to] && !vised[to] && dis[to] > dis[nw] + g.ge(i).w)
            {
                dis[to] = dis[nw] + g.ge(i).w;
                q.push({dis[to], to});
            }
        }
    }
}
int main()
{
    scanf("%d%d%d%d", &n, &m, &k, &e);
    for (int i = 1; i <= e; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.add(u, v, w);
        g.add(v, u, w);
    }
    scanf("%d", &d);
    for (int i = 1; i <= d; ++i)
    {
        int p, a, b;
        scanf("%d%d%d", &p, &a, &b);
        for (int j = a; j <= b; ++j)
            f[p][j] = 1;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
        {
            memset(cvis, 0, sizeof cvis);
            for (int p = 1; p <= m; ++p)
                for (int l = i; l <= j; ++l)
                    if (f[p][l])
                        cvis[p] = 1;
            dij();
            pr[i][j] = dis[m];
        }
    memset(dp, 0x7f, sizeof(dp));
    for (int i = 1; i <= n; ++i)
    {
        dp[i] = pr[1][i] * i;
        for (int j = i - 1; ~j; --j)
            dp[i] = min(dp[i], dp[j] + pr[j + 1][i] * (i - j) + k);
    }
    printf("%lld", dp[n]);
    return 0;
}
