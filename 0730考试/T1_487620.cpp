#include <cstdio>
using ll = long long;
inline ll cl(ll x, ll y)
{
    return x / y + bool(x % y);
}
int main()
{
    ll t;
    scanf("%lld", &t);
    while (t--)
    {
        ll x, y, k;
        scanf("%lld%lld%lld", &x, &y, &k);
        if (x > y)
        {
            printf("%lld\n", k);
            continue;
        }
        ll _ = 11 * x * k;
        ll $ = 2 * x + 11 * y;
        printf("%lld\n", _ / $);
    }
    return 0;
}
