// 虽然但是，’涙雨’の平仮名は’なみだあめ’です，题目名称里面少了一个あ
// 如果就是要说 ‘なみだめ’ 的话，那应该是题目背景里面的‘涙目’才对
#include <cstdio>

namespace Fujiwara
{
using ll = long long;
const int N = 5e6 + 5;
const ll B = 233, P = 998244853;

int n;
ll x[N];
ll h[N];
ll g[N];
ll p[N];
int t[N];
char s[N];
static int Azusa();
static void prec1();
static void work1();

static int Azusa()
{
    scanf("%d%5000000s", &n, s + 1);
    if (n <= 7000)
    {
        prec1();
        work1();
        return 0;
    }
    return 0;
}
static ll get(ll h[], int l, int r)
{
    return ((h[r] - h[l - 1] * x[r - l + 1] % P) % P + P) % P;
}
static void prec1()
{
    x[0] = 1;
    for (int i = n; i; --i)
        g[n - i + 1] = (g[n - i] * B % P + s[i]) % P;
    for (int i = 1; i <= n; ++i)
    {
        x[i] = (x[i - 1] * B) % P;
        p[i] = p[i - 1] + (s[i] == '?') * i;
        h[i] = (h[i - 1] * B % P + s[i]) % P;
        t[i] = t[i - 1] + (s[i] == '?' ? 1 : -1);
    }
}
static void work1()
{
    ll res = 0;
    for (int l = 1; l <= n; ++l)
        for (int r = l; r <= n; ++r)
            if (t[r] >= t[l - 1])
                if (get(h, l, r) == get(g, n - r + 1, n - l + 1))
                    res += p[r] - p[l - 1];
    printf("%lld\n", res);
}
}  // namespace Fujiwara

int main()
{
    freopen("namidame.in", "r", stdin);
    freopen("namidame.out", "w", stdout);
    return Fujiwara::Azusa();
}
