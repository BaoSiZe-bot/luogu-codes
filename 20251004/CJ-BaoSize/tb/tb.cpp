#include <cstdio>
namespace Fujiwara
{
using ll = long long;
const ll P = 1e9 + 7;
const ll Q = 5e8 + 4;
const int N = 5e5 + 5;

struct Edge
{
    int v, w, p;
} e[N << 1];
int ed[N], cnt;
static void add(int u, int v, int w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}

ll d[N];
static void dfs(int x, int p, int &s)
{
    if (d[s] <= d[x])
        s = x;
    for (int i = ed[x]; i; i = e[i].p)
    {
        int v = e[i].v, w = e[i].w;
        if (v == p)
            continue;
        d[v] = d[x] + w;
        dfs(v, x, s);
    }
}
static int Azusa()
{
    int n, s = 0, t = 0;
    scanf("%d", &n);
    for (int i = 1, u, v, w; i < n; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    dfs(1, 0, s), d[s] = 0;
    dfs(s, 0, t);
    printf("%lld\n", (ll)((__int128(d[t]) * Q) % P));
    return 0;
}
}  // namespace Fujiwara
int main()
{
    // freopen("tb.in", "r", stdin);
    // freopen("tb.out", "w", stdout);
    return Fujiwara::Azusa();
}
