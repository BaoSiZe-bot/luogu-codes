#include <cstdio>
#include <set>
namespace Fujiwara
{
using std::set;
using ll = long long;
const int N = 2e5 + 5;

int cnt, t;
struct Edge
{
    int v, p;
} e[N << 1];
int ed[N], c[N], n;
static void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}

bool f[N], g[N];
static void dfs(int x)
{
    ++t;
    g[x] = 1;
    f[c[x]] = 1;
    for (int i = ed[x]; i; i = e[i].p)
        if (!f[c[e[i].v]])
            dfs(e[i].v);
    f[c[x]] = 0;
}

static int Azusa()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", c + i);
    for (int i = 1, u, v; i < n; ++i)
    {
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }
    if (n <= 5000)
    {
        set<int> res;
        for (int i = 1; i <= n; ++i)
        {
            t = 0;
            dfs(i);
            if (t == n)
                res.insert(i);
        }

        printf("%d\n", int(res.size()));
        for (int i : res)
            printf("%d ", i);
    }
    return 0;
}
}  // namespace Fujiwara
int main()
{
    // freopen("tp.in", "r", stdin);
    // freopen("tp.out", "w", stdout);
    return Fujiwara::Azusa();
}
