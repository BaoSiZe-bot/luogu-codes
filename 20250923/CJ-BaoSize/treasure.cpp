#include <cstdio>

namespace Fujiwara
{
const int N = 100005, M = 105;
using ll = long long;
char s[N][M];
ll bk[N << 1];
int t[N][M];
int n, m, k;
ll f[N][M];
ll g[N][M];

static void input()
{
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%100s", s[i] + 1);
}

static void precl()
{
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            t[i][j] = t[i - 1][j] + t[i][j - 1] - t[i - 1][j - 1] + (s[i][j] == '$');
}

static void work1()
{
    ll res = 0;
    for (int lv = 1; lv <= n; ++lv)
        for (int rv = lv; rv <= n; ++rv)
            for (int lh = 1; lh <= m; ++lh)
                for (int rh = lh; rh <= m; ++rh)
                    res += ((t[rv][m] - t[lv - 1][m]) + (t[n][rh] - t[n][lh - 1])) == k;
    printf("%lld\n", res);
}

static void work2()
{
    for (int i = 1; i <= n; ++i)
        for (int x = t[i][m] - t[i - 1][m], j = x; j <= k; ++j)
            f[i][j] = f[i - 1][j - x] + (j == x);
    for (int i = 1; i <= m; ++i)
        for (int x = t[n][i] - t[n][i - 1], j = x; j <= k; ++j)
            g[i][j] = g[i - 1][j - x] + (j == x);

    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= k; ++j)
            f[i][j] += f[i - 1][j];
    for (int i = 1; i <= m; ++i)
        for (int j = 0; j <= k; ++j)
            g[i][j] += g[i - 1][j];

    ll res = 0;
    for (int i = 0; i <= k; ++i)
        res += f[n][i] * g[m][k - i];
    printf("%lld\n", res);
}

static void work3()
{
    bk[0] = 1;
    ll res = 0;
    for (int v = 1; v <= n; ++v)
    {
        for (int lh = 1; lh <= m; ++lh)
            for (int rh = lh; rh <= m; ++rh)
            {
                int p = t[n][rh] - t[n][lh - 1] + t[v][m] - k;
                if (p >= 0)
                    res += bk[p];
            }
        ++bk[t[v][m]];
    }
    printf("%lld\n", res);
}

static int Azusa()
{
    input();
    precl();
    if (n <= 100)
    {
        work1();
        return 0;
    }
    if (k <= 100)
    {
        work2();
        return 0;
    }
    work3();
    return 0;
}
}  // namespace Fujiwara

int main()
{
    // freopen("treasure.in", "r", stdin);
    // freopen("treasure.out", "w", stdout);
    return Fujiwara::Azusa();
}
