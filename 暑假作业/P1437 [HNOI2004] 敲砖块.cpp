#include <stdio.h>
#define int long long
int a[105][105], s[105][105], dp[105][105][505];
inline int max(int x, int y)
{
    return x < y ? y : x;
}
signed main()
{
    int n, m;
    scanf("%lld%lld", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n - i + 1; ++j)
            scanf("%lld", a[n - j + 1] + i);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            s[i][j] = s[i][j - 1] + a[i][j];
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            for (int k = 0; k <= m; ++k)
                dp[i][j][k] = (j > i || j * (j + 1) > k || i * (i + 1) / 2 - (i - j) < k) * -1000000000;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= i; ++j)
            for (int k = j * (j + 1) / 2; k <= m && k <= i * (i + 1) / 2; ++k)
                for (int p = j - 1; p <= i - 1; ++p)
                    dp[i][j][k] = max(dp[i][j][k], dp[i - 1][p][k - j] + s[i][j]);
    int res = 0;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= i; j++)
            for (int k = 0; k <= m; k++)
                res = max(res, dp[i][j][k]);
    printf("%lld", res);
    return 0;
}
