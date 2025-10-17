#include <cstdio>
namespace Fujiwara
{
using ll = long long;
const ll P = 1e9 + 7;
const int N = 8e3 + 5;

struct Edge
{
    int v, p;
} e[N << 1];
struct Node
{
    int u, v;
} g[N];
int ed[N], dp[N][N], cnt, n;
static void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}

static int Azusa()
{
    scanf("%d", &n);
    for (int i = 1; i < n; ++i)
    {
        scanf("%d%d", &g[i].u, &g[i].v);
        add(g[i].u, g[i].v);
        add(g[i].v, g[i].u);
    }
    for (int i = 1; i < n; ++i)
    {
    
    }
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("cl.in", "r", stdin);
    freopen("cl.out", "w", stdout);
    return Fujiwara::Azusa();
}
