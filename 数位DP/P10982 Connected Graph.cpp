#include <csignal>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define int long long

const int M = 1004535809;
int dp[1005], C[1005][1005];

inline int qp(int a, int b, int p)
{
    int res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= p;
        (a *= a) %= p;
        b >>= 1;
    }
    return res;
}
signed main()
{
    int n;
    scanf("%lld", &n);
    dp[1] = 1;
    for (int i = 1; i <= n; ++i)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % M;
    }
    for (int i = 2; i <= n; ++i)
    {
        dp[i] = qp(2, i * (i - 1) >> 1, M);
        for (int j = 1; j < i; ++j)
        {
            int t = dp[j] * C[i - 1][j - 1] % M * qp(2, (i - j) * (i - j - 1) >> 1, M) % M;
            dp[i] = ((dp[i] - t) % M + M) % M;
        }
    }
    printf("%lld\n", dp[n]);
    return 0;
}
