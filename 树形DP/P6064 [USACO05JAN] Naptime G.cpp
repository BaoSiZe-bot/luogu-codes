#include <cstring>
#include <stdio.h>

int a[3835], dp[3835][3835][2];

inline int max(int a, int b)
{
    return a < b ? b : a;
}
int main()
{
    memset(dp, 0xc0, sizeof dp);
    int n, b, res = 0;
    scanf("%d%d", &n, &b);
    for (int i = 1; i <= n; ++i)
        scanf("%d", a + i);
    dp[1][1][1] = dp[1][0][0] = 0;
    for (int i = 2; i <= n; ++i)
    {
        dp[i][0][0] = 0;
        for (int j = 1; j <= b; ++j)
        {
            dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1]);
            dp[i][j][1] = max(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1] + a[i]);
        }
    }
    res = max(dp[n][b][0], dp[n][b][1]);
    memset(dp, 0xc0, sizeof dp);
    dp[1][1][1] = a[1];
    dp[1][0][0] = 0;
    for (int i = 2; i <= n; ++i)
    {
        dp[i][0][0] = 0;
        for (int j = 1; j <= b; ++j)
        {
            dp[i][j][0] = max(dp[i - 1][j][0], dp[i - 1][j][1]);
            dp[i][j][1] = max(dp[i - 1][j - 1][0], dp[i - 1][j - 1][1] + a[i]);
        }
    }
    printf("%d", max(res, dp[n][b][1]));
    return 0;
}
