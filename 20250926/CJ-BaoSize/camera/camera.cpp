#include <algorithm>
#include <climits>
#include <cstdio>
#include <utility>
#include <vector>

namespace Fujiwara
{
using std::min;
using std::pair;
using std::vector;

using ll = long long;
const ll INF = LLONG_MAX;

int T;
ll n, a;
static int Azusa();
static void solve();
static ll qp(ll, int);

static int Azusa()
{
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}
static ll qp(ll a, int b)
{
    ll res = 1;
    for (; b; b >>= 1)
    {
        (b & 1) && (res *= a);
        a *= a;
    }
    return res;
}

vector<pair<ll, int>> pr;

static void solve()
{
    pr.clear();
    scanf("%lld%lld", &n, &a);
    if (n <= 8)
    {
        ll k = 1, res = 0;
        for (int i = 1; i <= n; ++i)
            k *= qp(i, n - i + 1);
        for (ll i = a; k % i == 0; i *= a)
            ++res;
        printf("%lld\n", res);
        return;
    }
    ll res = INF;

    for (ll i = 2; i * i <= a; ++i)
        if (a % i == 0)
            for (pr.emplace_back(i, 0); a % i == 0; a /= i)
                pr.back().second++;
    if (a > 1)
        pr.emplace_back(a, 1);

    for (auto p : pr)
    {
        ll s = 0;
        for (ll i = p.first; i > 0 && i <= n; i *= p.first)
        {
            ll t = n / i, q = t * (t + 1) / 2;
            s += t * (n + 1) - i * q;
        }
        res = min(res, s / p.second);
    }
    printf("%lld\n", res);
}
}  // namespace Fujiwara

int main()
{
    freopen("camera.in", "r", stdin);
    freopen("camera.out", "w", stdout);
    return Fujiwara::Azusa();
}

// k = pow(1, n) * pow(2, n - 1) * pow(3, n - 2) * .... * pow(n, 1)
// v(a, 1) * n + v(a, 2) * (n - 1) + v(a, 3) * (n - 2) + ... + v(a, n) * 1
