#include <algorithm>
#include <cstdio>
#include <utility>
#include <vector>

namespace Fujiwara
{
using std::min;
using std::pair;
using std::vector;

using ll = __int128;
const long long MOD = 1e18;
const ll INF = ((__int128)1) << 126;

int T;
ll n, a;
static int Azusa();
static void solve();
static ll qp(ll, ll);

static int Azusa()
{
    scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}
static ll qp(ll a, ll b)
{
    ll res = 1;
    for (; b; b >>= 1)
    {
        (b & 1) && (res *= a);
        a *= a;
    }
    return res;
}

vector<pair<ll, ll>> pr;

static void println(ll x)
{
    long long a = x % MOD, b = x / MOD;
    if (b)
    {
        printf("%lld", b);
        printf("%018lld\n", a);
    }
    else
        printf("%lld\n", a);
}
static void solve()
{
    pr.clear();
    long long tn, ta;
    scanf("%lld%lld", &tn, &ta);
    n = tn, a = ta;
    if (n <= 8)
    {
        ll k = 1, res = 0;
        for (int i = 1; i <= n; ++i)
            k *= qp(i, n - i + 1);
        for (ll i = a; k % i == 0; i *= a)
            ++res;
        println(res);
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
            ll t = n / i, q = t * (t + 1) / 2, c = t * (n + 1) - i * q;
            s += c;
        }
        res = min(res, s / p.second);
    }
    println(res);
}
}  // namespace Fujiwara

int main()
{
    return Fujiwara::Azusa();
}
