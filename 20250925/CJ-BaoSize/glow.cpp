#include <cstdio>
#include <bits/extc++.h>

namespace Fujiwara
{
using ll = long long;
const int N = 1e5 + 5;

ll t[N];
ll n, k, l;
ll s[N], res[N];
struct Bubble
{
    ll c, d;
    char t;
} a[N];
static int Azusa();

static int Azusa()
{
    scanf("%lld %lld %lld", &n, &k, &l);
    for (int i = 1; i <= n; ++i)
        scanf("%lld %lld %c", &a[i].d, &a[i].c, &a[i].t);
    for (int i = 1, c = 0; i <= n; ++i)
    {
        s[0] += a[i].d - a[i - 1].d;
        s[c] += a[i].d - a[i - 1].d;
        if (a[i].t == 'L')
            for (int j = 0; j < k; ++j)
                res[(j + a[i].c) % k] += s[j];
        else
        {
            for (int j = 0; j < k; ++j)
                t[(j + a[i].c) % k] = s[j];
            for (int j = 0; j < k; ++j)
                s[j] = t[j];

            (c += a[i].c) %= k;
            res[a[i].c] += (l - a[i].d) << 1;
        }
    }
    for (int i = 0; i < k; ++i)
        printf("%.1lf\n", res[i] / 2.0);
    return 0;
}
}  // namespace Fujiwara

int main()
{
    // freopen("glow.in", "r", stdin);
    // freopen("glow.out", "w", stdout);
    return Fujiwara::Azusa();
}
