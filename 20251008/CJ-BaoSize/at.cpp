// 私はロボットですか？

#include <algorithm>
#include <cstdio>

namespace Fujiwara
{
using std::sort;
using ll = long long;
const int N = 2e5 + 5;

ll n, a[N];
int s[N], t[N];

static ll up(ll x, ll y)
{
    ll res = 0;
    ll l1 = 0, l2 = 0;
    for (; x; x /= 10)
        s[++l1] = x % 10;
    for (; y; y /= 10)
        t[++l2] = y % 10;
    ll mx = std::max(l1, l2);
    for (int i = 1; i <= mx; ++i)
        (s[i] + t[i] > 9) && (++res, ++s[i + 1]);
    for (int i = 1; i <= mx + 1; ++i)
        s[i] = t[i] = 0;
    return res;
}

static int Azusa()
{
    scanf("%lld", &n);
    for (int i = 1; i <= n; i++)
        scanf("%lld", a + i);
    sort(a + 1, a + n + 1);

    ll sum = 0, res = 0;
    for (int i = 1; i <= n; ++i)
    {
        ll x = up(sum, a[i]);
        sum += a[i];
        res += x;
    }
    printf("%lld\n", res);
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("at.in", "r", stdin);
    return Fujiwara::Azusa();
}
