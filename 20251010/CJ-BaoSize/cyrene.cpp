#include <array>
#include <cassert>
#include <cstdio>
namespace Fujiwara
{
using std::array;

using ll = long long;

const int N = 1e7;
const ll P = 1e9 + 7;
const ll T = 5e8 + 4;
array<ll, N + 5> inv, s;
array<ll, N + 5> fac, ivf;

static ll qp(ll a, ll b, ll p = P)
{
    ll res = 1;
    for (; b; b >>= 1)
    {
        (b & 1) && (res = res * a % p);
        a = a * a % p;
    }
    return res;
}
static void pre(int n = N)
{
    fac[0] = ivf[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % P;
    ivf[n] = qp(fac[n], P - 2);
    for (int i = n - 1; i; --i)
    {
        ivf[i] = ivf[i + 1] * (i + 1) % P;
    }
    for (int i = 1; i <= n; ++i)
    {
        inv[i] = fac[i - 1] * ivf[i] % P;
        s[i] = (s[i - 1] + inv[i]) % P;
    }
    assert(inv[2] == T);
}
static void slv()
{
    int n, x;
    scanf("%d%d", &n, &x);
    ll p = (n - x) * inv[n];
    ll q = s[x] + s[n - x] - s[n];
    ll t = ((p + q) % P + P) % P;
    ll res = t * T % P * fac[n] % P;
    printf("%lld\n", x ? res : 0);
}
static int Azusa()
{
    int t;
    scanf("%d", &t);
    for (pre(); t--; slv()) ;
    return 0;
}
}  // namespace Fujiwara
int main()
{
    return Fujiwara::Azusa();
}
