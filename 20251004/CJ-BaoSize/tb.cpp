#include <cstdio>
namespace Fujiwara
{
using ll = long long;
const ll P = 1e9 + 7;
const int N = 5e5 + 5;

static ll qp(ll a, ll b, ll p = P)
{
    fprintf(stderr, "calculating %lld^%lld%%%lld", a, b, p);
    ll res = 1;
    for (; b; b >>= 1)
    {
        (b & 1) && (res *= a);
        a *= a;
    }
    fprintf(stderr, "\ngot %lld\n", res);
    return res;
}

struct Edge
{
    int v, w, p;
} e[N << 1];
int ed[N], d[N], cnt, n;
static void add(int u, int v, int w)
{
    e[++cnt] = {v, w, ed[u]};
    ed[u] = cnt;
}
static void dfs(int x, int p)
{
    for (int i = ed[x]; i; i = e[i].p)
    {
        int v = e[i].v, w = e[i].w;
        if (v == p)
            continue;
        d[v] = d[x] + w;
        dfs(v, x);
    }
}
static int Azusa()
{
    scanf("%d", &n);
    for (int i = 1, u, v, w; i < n; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    dfs(1, 0);
    if (n == 1)
    {
        printf("0\n");
        return 0;
    }
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("tb.in", "r", stdin);
    freopen("tb.out", "w", stdout);
    return Fujiwara::Azusa();
}
