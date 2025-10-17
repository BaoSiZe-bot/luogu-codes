#include <cstdio>
namespace Fujiwara
{
using ll = long long;
const int N = 5e5 + 5;

ll a[N];
static void solve()
{
    int n, s, t;
    scanf("%d%d%d", &n, &s, &t);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", a + i);
    printf("%lld\n", s == t ? 0 : 2 * (a[s] | a[t]));
}
static int Azusa()
{
    int T;
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}
}  // namespace Fujiwara
int main()
{
    return Fujiwara::Azusa();
}
