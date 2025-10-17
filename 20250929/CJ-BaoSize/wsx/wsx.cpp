#include <algorithm>
#include <cstdio>
#include <numeric>

namespace Fujiwara
{
using std::accumulate;
using std::next_permutation;

using ll = long long;
const int N = 2e5 + 5;

int n, q, a[N];
ll x, k, fac[N];
int op, y, f[N];
static void solve1()
{
    scanf("%d%lld", &op, &x);
    if (op == 1)
    {
        scanf("%d", &y);
        printf("%lld\n", accumulate(a + x, a + y + 1, 0ll));
    }
    else
        while (x--)
            next_permutation(a + 1, a + n + 1);
}

static void solve2()
{
    scanf("%d%lld", &op, &x);
    if (op == 1)
    {
        ll t = k;
        for (int i = 1; i <= n; ++i)
            f[i] = 0;
        for (int i = n - 1; ~i; --i)
        {
            int p = t / fac[i];
            for (int j = 1; j <= n; ++j)
            {
                p -= !f[j];
                if (p == -1)
                {
                    f[a[n - i] = j] = 1;
                    break;
                }
            }
            t %= fac[i];
        }

        scanf("%d", &y);
        printf("%lld\n", accumulate(a + x, a + y + 1, 0ll));
    }
    else
        k += x;
}
static int Azusa()
{
    fac[0] = 1;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
        a[i] = i;
    if (n <= 15)
        for (int i = 1; i <= n; ++i)
            fac[i] = fac[i - 1] * i;
    while (q--)
    {
        if (n <= 8)
            solve1();
        else if (n <= 15)
            solve2();
    }
    return 0;
}
}  // namespace Fujiwara

int main()
{
    return Fujiwara::Azusa();
}
