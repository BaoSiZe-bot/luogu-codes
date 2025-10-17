#include <cstdio>

namespace Fujiwara
{
using ll = long long;

int t, x, n;

static void solve()
{
    scanf("%d%d", &x, &n);
    printf("%d\n", (n & 1) ? x : 0);
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
