#include <cstdio>
namespace Fujiwara
{
using ll = long long;
const ll P = 1e9 + 7;
const int N = 1e5 + 5;

ll res;
int a[N], f[N], g[N], n;
static void dfs(int x, int cnt)
{
    if (x > n)
    {
        for (int i = 1; i <= n; ++i)
            if (f[g[i]] > a[i])
                return;
        (++res) %= P;
        return;
    }
    for (int i = 1; i <= cnt; ++i)
    {
        f[g[x] = i]++;
        dfs(x + 1, cnt);
        f[g[x]]--;
    }
    f[g[x] = cnt + 1]++;
    dfs(x + 1, cnt + 1);
    f[g[x]]--;
}
static int Azusa()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    if (n <= 10)
    {
        dfs(1, 0);
        printf("%lld\n", res);
    }
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("group.in", "r", stdin);
    freopen("group.out", "w", stdout);
    return Fujiwara::Azusa();
}
