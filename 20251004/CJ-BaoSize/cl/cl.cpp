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
int ed[N], cnt;
static void add(int u, int v)
{
    e[++cnt] = {v, ed[u]};
    ed[u] = cnt;
}

int tr[N << 1], sz[N], n;
ll f[N][N], g[N][N], res[N];
static void dp1(int x, int p)
{
    f[x][1] = sz[x] = 1;
    for (int i = ed[x]; i; i = e[i].p)
    {
        int v = e[i].v;
        if (v ^ p)
        {
            dp1(v, x);
            for (int j = 0; j <= n; ++j)
                tr[j] = f[x][j];
            for (int j = 1; j <= sz[x]; ++j)
                for (int k = 1; k <= sz[v]; ++k)
                    (tr[j + k] += f[x][j] * f[v][k] % P) %= P;
            for (int j = 0; j <= n; ++j)
                f[x][j] = tr[j];
            sz[x] += sz[v];
        }
    }
}
static void dp2(int x, int p)
{
    for (int i = ed[x]; i; i = e[i].p)
    {
        int v = e[i].v;
        if (v ^ p)
        {
            g[v][1] = 1;
            for (int j = 2; j <= sz[v]; ++j)
                g[v][j] = g[x][j - 1];
            for (int j = ed[x]; j; j = e[j].p)
            {
                int w = e[j].v;
                if (w ^ v && w ^ p)
                {
                    for (int k = 0; k <= sz[v]; ++k)
                        tr[k] = g[v][k];
                    for (int k = 1; k <= sz[v]; ++k)
                        for (int l = 1; l <= sz[w] && k + l <= sz[v]; ++l)
                            (tr[k + l] += g[v][k] * f[w][l] % P) %= P;
                    for (int k = 0; k <= sz[v]; ++k)
                        g[v][k] = tr[k];
                }
            }
            for (int j = 0; j <= sz[v]; ++j)
                (res[j] += f[v][j] * g[v][j]) %= P;
            dp2(v, x);
        }
    }
}

static int Azusa()
{
    scanf("%d", &n);
    for (int i = 1, x, y; i < n; ++i)
    {
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    dp1(1, -1);
    dp2(1, -1);
    for (int i = 1; i + i <= n; ++i)
        printf("%d ", res[i]);
    return 0;
}
}  // namespace Fujiwara
int main()
{
    // freopen("cl.in", "r", stdin);
    // freopen("cl.out", "w", stdout);
    return Fujiwara::Azusa();
}
