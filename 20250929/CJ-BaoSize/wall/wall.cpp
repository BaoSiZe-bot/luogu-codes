#include <cstdio>
namespace Fujiwara
{
const int N = 3e5 + 5;
int T, n, m, p, a[N];
static void solve()
{
    scanf("%d%d", &n, &m);

    if (m == n - 2)
    {
        printf("ruobi\n");
        return;
    }
    printf("qiangbi\n");

    for (int i = (n - m) % 3; i; --i)
        printf("%d ", n--);
    int t = n - m;

    for (int i = 0, x; i < t; ++i)
    {
        switch (i % 3)
        {
            case 0: x = i / 3 + 1; break;
            case 1: x = t - t / 3 - i / 3; break;
            default: x = t - i / 3;
        }
        printf("%d ", x);
    }
    for (int i = t + 1; i <= n; ++i)
        printf("%d ", i);
    printf("\n");
}
static int Azusa()
{
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}
}  // namespace Fujiwara
int main()
{
    // freopen("wall.in", "r", stdin);
    // freopen("wall.out", "w", stdout);
    return Fujiwara::Azusa();
}
