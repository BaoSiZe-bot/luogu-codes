#include <queue>
#include <string.h>
#include <stdio.h>
using std::greater;
using std::pair;
using std::priority_queue;
using std::vector;
using ll = long long;
using pli = pair<ll, int>;
const int M = 1e6 + 5, N = 5e5 + 5;
struct Edge
{
    int v;
    ll w;
    int p;
} e[M];
int ed[N], cnt;
inline void add(int u, int v, ll w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
ll d1[N], d2[N], res[N];
bool f[N];
int n, m, u[N], v[N];
ll p[N], q[N];
inline void dij(ll d[])
{
    memset(f, 0, sizeof f);
    priority_queue<pli, vector<pli>, greater<pli>> q;
    q.push({0, n});
    d[n] = 0;
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
inline ll sum(int i)
{
    return !(d1[u[i]] + p[i] == d1[v[i]]) + !(d2[u[i]] + q[i] == d2[v[i]]);
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d%d%lld%lld", v + i, u + i, p + i, q + i);
        add(u[i], v[i], p[i]);
    }
    memset(d1, 0x3f, sizeof(d1));
    dij(d1);
    memset(d2, 0x3f, sizeof(d2));
    memset(ed, 0, sizeof ed);
    cnt = 0;
    for (int i = 1; i <= m; ++i)
        add(u[i], v[i], q[i]);
    dij(d2);
    memset(res, 0x3f, sizeof(res));
    memset(ed, 0, sizeof ed);
    cnt = 0;
    for (int i = 1; i <= m; ++i)
        add(u[i], v[i], sum(i));
    dij(res);
    printf("%lld\n", res[1]);
    return 0;
}
