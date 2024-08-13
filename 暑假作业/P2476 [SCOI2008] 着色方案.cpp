#include <stdio.h>
const int M = 1e9 + 7;
long long c[15], s[15], C[105][105], dp[1005][1005];
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%lld", &c[i]);
        s[i] = s[i - 1] + c[i];
    }
    C[0][0] = 1;
    for (int i = 1; i <= 100; ++i)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j <= 100; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % M;
    }
    dp[1][c[1] - 1] = 1;
    for (int i = 1; i < n; ++i)
        for (int j = 0; j <= s[i] - 1; ++j)
            for (int k = 1; k <= s[i] + 1 && k <= c[i + 1]; ++k)
                for (int p = 0; p <= k && p <= j; ++p)
                    dp[i + 1][j + c[i + 1] - k - p] = (dp[i + 1][j + c[i + 1] - k - p] + dp[i][j] * C[s[i] + 1 - j][k - p] % M * C[j][p] % M * C[c[i + 1] - 1][k - 1] % M) % M;
    printf("%lld\n", dp[n][0]);
    return 0;
}
