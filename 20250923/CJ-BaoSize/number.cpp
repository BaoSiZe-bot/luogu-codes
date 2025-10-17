#include <algorithm>
#include <cstdio>

namespace Fujiwara
{
using std::min;
const int N = 5005;
using ll = long long;
const ll M = 998244353;
ll __id, res, n, l, a[N], p[N], f[N];

static void dfs(int x)
{
    if (x == n + 1)
    {
        ll t = 1;
        for (int i = 1; i <= n; ++i)
        {
            ll cnt = 0;
            for (int j = p[i]; j < a[i]; j += l)
                ++cnt;
            (t *= cnt) %= M;
        }
        (res += t) %= M;
    }
    for (int i = 0; i < l; ++i)
        if (!f[i])
        {
            f[i] = 1;
            p[x] = i;
            dfs(x + 1);
            f[i] = 0;
        }
}

static void input()
{
    scanf("%lld%lld%lld", &__id, &n, &l);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", a + i);
}

static void solve()
{
    std::sort(a + 1, a + n + 1, [](ll x, ll y) { return x % l < y % l; });

    f[0] = 1;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = min(a[i] % l, 1ll * i); j; --j)
            f[j] = (f[j] * (a[i] / l) + f[j - 1] * (a[i] % l - j + 1) % M) % M;
        (f[0] *= a[i] / l) %= M;
    }

    ll t = 1;
    for (int i = n; ~i; --i)
    {
        (res += f[i] * t % M) %= M;
        (t *= l - i + 1) %= M;
    }
    printf("%lld\n", res);
}

static int Azusa()
{
    input();
    if (n <= 8 && l <= 9)
    {
        dfs(1);
        printf("%lld\n", res);
        return 0;
    }
    solve();
    return 0;
}
}  // namespace Fujiwara

int main()
{
    // freopen("number.in", "r", stdin);
    // freopen("number.out", "w", stdout);
    return Fujiwara::Azusa();
}
