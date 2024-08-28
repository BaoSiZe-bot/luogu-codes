#include <stdio.h>
#include <string.h>
#include <queue>
using ll = long long;
template <const int N> struct GR
{
private:
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
    inline Edge ge(int x)
    {
        return e[x];
    }
    inline int gd(int x)
    {
        return ed[x];
    }
};
GR<1000005> g;
ll d[10005][105];
int n, m, k;
bool f[10005][105];
inline void dij()
{
    memset(d, 0x7f, sizeof(d));
    std::priority_queue<std::pair<ll, std::pair<int, int>>, std::vector<std::pair<ll, std::pair<int, int>>>, std::greater<std::pair<ll, std::pair<int, int>>>> q;
    q.push({0, {1, 0}});
    d[1][0] = 0;
    while (!q.empty())
    {
        auto nw = q.top().second;
        q.pop();
        if (f[nw.first][nw.second])
            continue;
        f[nw.first][nw.second] = 1;
        for (int i = g.gd(nw.first); i; i = g.ge(i).p)
        {
            int to = g.ge(i).v, w = g.ge(i).w;
            ll ww = d[nw.first][nw.second];
            if (ww < w)
                ww += (w - ww + k - 1) / k * k;
            ww++;
            if (d[to][ww % k] > ww)
            {
                d[to][ww % k] = ww;
                q.push({ww, {to, ww % k}});
            }
        }
    }
}
int main()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.add(u, v, w);
    }
    dij();
    printf("%lld", d[n][0] == 0x7f7f7f7f7f7f7f7f ? -1 : d[n][0]);
    return 0;
}
