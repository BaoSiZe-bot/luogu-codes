#include <stdio.h>
using ll = long long;
const int N = 5e3 + 4;
ll t[N], f[N], dp[N], st[N], sf[N];
inline ll min(ll a, ll b)
{
    return a < b ? a : b;
}
int main()
{
    int n, s;
    scanf("%d%d", &n, &s);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld%lld", t + i, f + i);
        st[i] = st[i - 1] + t[i];
        sf[i] = sf[i - 1] + f[i];
        dp[i] = 0x3f3f3f3f3f3f3f3f;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            dp[i] = min(dp[i], dp[j - 1] + st[i] * (sf[i] - sf[j - 1]) + s * (sf[n] - sf[j - 1]));
    printf("%lld\n", dp[n]);
    return 0;
}
