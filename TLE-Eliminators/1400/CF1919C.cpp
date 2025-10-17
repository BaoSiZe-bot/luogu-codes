#include <cstdio>
namespace Fujiwara
{
const int N = 2e5 + 5;

int a[N], n;
static void solve()
{
    int res = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);

    for (int i = 1, l = n + 1, r = n + 1; i <= n; ++i)
    {
        if (l > r)
            l ^= r ^= l ^= r;
        if (a[i] <= l)
            l = a[i];
        else if (a[i] <= r)
            r = a[i];
        else
        {
            l = a[i];
            ++res;
        }
    }
    printf("%d\n", res);
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
