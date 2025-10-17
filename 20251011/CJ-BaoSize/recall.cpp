#include <cstdio>

namespace Fujiwara
{
using ll = long long;

ll a[1000005], cnt;

static void solve(ll l, ll r)
{
    ll maxn = -1, id = 0;
    for (ll i = l; i <= r; ++i)
    {
        ++cnt;
        if (a[i] > maxn)
            maxn = a[i], id = i;
    }
    if (l < id)
        solve(l, id - 1);
    if (id < r)
        solve(id + 1, r);
}
static void solve()
{
    cnt = 0;
    int l, r;
    scanf("%d%d", &l, &r);
    solve(l, r);
    printf("%lld\n", cnt);
}
static int Azusa()
{
    int n, q = 1;
    scanf("%d%d", &n, &q);
    for (int i = 1; i <= n; ++i)
        scanf("%lld", a + i);
    while (q--)
        solve();
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("recall.in", "r", stdin);
    freopen("recall.out", "w", stdout);
    return Fujiwara::Azusa();
}
