#include <cstdio>
#include <stdio_ext.h>
using ll = long long;
const int M = 998244353, N = 5005;
ll dp[N][N], fc[N] = {1}, res;
int n;
inline ll qp(ll a, int b, int p = M)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= p;
        (a *= a) %= p;
        b >>= 1;
    }
    return res;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        fc[i] = fc[i - 1] * i % M;
    dp[3][1] = 1;
    for (int i = 4; i <= n; ++i)
        for (int j = 2; j <= n; ++j)
            dp[i][j] = (dp[i - 1][j - 1] + dp[i - 2][j - 1] + dp[i - 3][j - 1]) % M;
    for (int i = 1; i <= n; i++)
        (res += (((dp[n][i] + dp[n - 2][i - 1] + dp[n - 1][i - 1] * 2) * i % M * fc[i - 1] % M * fc[n - i] % M * qp(fc[n - 1], M - 2) % M)) % M) %= M;
    printf("%lld", res);
    return 0;
}
