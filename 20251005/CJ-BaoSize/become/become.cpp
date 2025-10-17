#include <algorithm>
#include <cstdio>
#include <cstring>
namespace Fujiwara
{
using std::max;
using std::min;
const int N = 3e5 + 5;
const int INF = 0x7f7f7f7f;

struct Edge
{
    int v, w, p;
} e[N << 1];
int ed[N], cnt;
static void add(int u, int v, int w)
{
    e[cnt] = {v, w, ed[u]};
    ed[u] = cnt++;
}

int dis[N];
static void dfs(int x, int f, int mn, int mx)
{
    dis[x] = min(dis[x], mx + mn);
    for (int i = ed[x]; ~i; i = e[i].p)
        if (e[i].v != f)
            dfs(e[i].v, x, min(mn, e[i].w), max(mx, e[i].w));
}
bool vis[N << 1];
static void bdfs(int x, int mn, int mx)
{
    dis[x] = min(dis[x], mx + mn);
    for (int i = ed[x]; ~i; i = e[i].p)
        if (!vis[i] && !vis[i ^ 1])
        {
            vis[i] = vis[i ^ 1] = 1;
            bdfs(e[i].v, min(mn, e[i].w), max(mx, e[i].w));
            vis[i] = vis[i ^ 1] = 0;
        }
}
static int Azusa()
{
    int n, m;
    scanf("%d%d", &n, &m);
    memset(ed, -1, sizeof ed);
    for (int i = 1, u, v, w; i <= m; ++i)
    {
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }
    memset(dis, 0x7f, sizeof(dis));
    if (m == n - 1)
        dfs(1, 0, INF, -INF);
    else
        bdfs(1, INF, -INF);
    for (int i = 2; i <= n; ++i)
        printf("%d\n", dis[i]);
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("become.in", "r", stdin);
    freopen("become.out", "w", stdout);
    return Fujiwara::Azusa();
}

// 大概只能得个25pts吧
// D链的性质正适合bdfs
