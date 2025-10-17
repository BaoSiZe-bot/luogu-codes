#include <cstdio>

namespace Fujiwara
{
using ll = long long;

int t, n, m, x, y;

static void solve()
{
    scanf("%d%d%d%d", &n, &m, &x, &y);
    for (int i = 1, $; i <= n; ++i)
        scanf("%d", &$);
    for (int i = 1, $; i <= m; ++i)
        scanf("%d", &$);
    printf("%d\n", n + m);
}

static int Azusa()
{
    scanf("%d", &t);
    while (t--)
        solve();
    return 0;
}
}  // namespace Fujiwara

int main()
{
    return Fujiwara::Azusa();
}
