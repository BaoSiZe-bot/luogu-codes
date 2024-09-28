
#include <stdio.h>
#include <queue>
using ll = long long;
struct Edge
{
    int v;
    ll w;
    int p;
} e[400005];
int ed[200005], p[200005], cnt, res, rr = 2;
ll d[200005], f[200005];
std::priority_queue<std::pair<ll, int>> q;
inline void add(int u, int v, int w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
inline ll max(ll a, ll b)
{
    return a < b ? b : a;
}
inline void dfs(int x, int fa)
{
    p[x] = fa;
    f[x] = 0;
    for (int i = ed[x]; i; i = e[i].p)
    {
        int to = e[i].v;
        if (to ^ fa)
        {
            d[to] = d[x] + e[i].w;
            dfs(to, x);
            f[x] = max(f[x], f[to] + e[i].w);
        }
    }
}
void doit(int x, int fa)
{
    d[x] = 0;
    dfs(x, fa);
    for (;;)
    {
        int y = 0, cnt = 0;
        for (int i = ed[x]; i; i = e[i].p)
            if (e[i].v ^ fa && f[x] == f[e[i].v] + e[i].w)
            {
                y = e[i].v;
                cnt++;
            }
        if (cnt ^ 1)
            break;
        fa = x;
        x = y;
        rr++;
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    dfs(1, 0);
    for (int i = 1; i <= n; i++)
        if (d[i] > d[res])
            res = i;
    d[res] = 0;
    dfs(res, 0);
    res = 0;
    for (int i = 1; i <= n; i++)
        if (d[i] > d[res])
            res = i;
    printf("%lld\n", d[res]);
    ll t = d[res] >> 1;
    while (d[p[res]] >= t)
        res = p[res];
    if (d[res] == t)
    {
        d[res] = 0;
        dfs(res, 0);
        for (int i = ed[res]; i; i = e[i].p)
            q.push({f[e[i].v] + e[i].w, e[i].v});
        auto a = q.top();
        q.pop();
        auto b = q.top();
        q.pop();
        if (q.empty() || q.top().first < b.first)
        {
            doit(a.second, res);
            doit(b.second, res);
        }
        else if (a.first > b.first)
        {
            rr--;
            doit(a.second, res);
        }
    }
    else
    {
        rr--;
        doit(res, p[res]);
        doit(p[res], res);
    }
    printf("%d\n", rr);
    return 0;
}
