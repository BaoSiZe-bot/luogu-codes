#include <bits/stdc++.h>
#define int long long

using namespace std;

int dp1[24405], dp2[24405], v[10005], c[10005];
int s, mx;
signed main()
{
    int n, t;
    scanf("%lld%lld", &n, &t);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", v + i);
        mx = max(mx, v[i] * v[i]);
    }
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", c + i);
        s += c[i] * v[i];
    }
    if (s < t)
        return 0 * puts("-1");
    memset(dp1, 0x3f, sizeof(dp1));
    dp1[0] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = v[i]; j <= mx; ++j)
            dp1[j] = min(dp1[j], dp1[j - v[i]] + 1);
    memset(dp2, 0x3f, sizeof(dp2));
    dp2[0] = 0;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= c[i]; j <<= 1)
        {
            for (int k = t + mx; k >= j * v[i]; --k)
                dp2[k] = min(dp2[k], dp2[k - j * v[i]] + j);
            c[i] -= j;
        }
        if (c[i])
            for (int k = t + mx; k >= c[i] * v[i]; --k)
                dp2[k] = min(dp2[k], dp2[k - c[i] * v[i]] + c[i]);
    }
    int res = INT_MAX;
    for (int i = t; i <= t + mx; ++i)
        res = min(res, dp2[i] + dp1[i - t]);
    printf("%lld\n", res == INT_MAX ? -1 : res);
    return 0;
}
