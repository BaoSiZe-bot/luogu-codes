#include <cstdio>
namespace Fujiwara
{
using ll = long long;
const int N = 5e5 + 5;

ll m;
ll a[N];
int b[N];
int n, d;
static void solve()
{
    scanf("%d%d%lld", &n, &d, &m);
    for (int i = 1; i <= n; ++i)
        scanf("%1d", b + i);
    if (d == 2)
    {
        ll p = 0, s = 0;
        for (int i = 1; i <= n; ++i)
        {
            (p += (p - !b[i] + 2) % 2);
            s += (a[i] = p);
        }

        if (s > m)
        {
            printf("No\n");
            return;
        }

        a[n] += m - s;

        if ((a[n] - !b[n] + 2) % 2 != 0)
        {
            printf("No\n");
            return;
        }

        for (int i = 1; i <= n; ++i)
            printf("%lld ", a[i]);
        printf("\n");
        return;
    }
    printf("No\n");
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
