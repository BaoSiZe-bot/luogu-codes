#include <stdio.h>

int dp[1005][1005][55][55];
inline int max(int x, int y)
{
    return x > y ? x : y;
}
int main()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    dp[0][0][0][0] = 1;
    for (int i = 0; i <= n; ++i)
        for (int j = 0; j <= m; ++j)
            for (int p = 0; p <= k; ++p)
                for (int l = 0; l <= k; ++l)
                    if (dp[i][j][p][l])
                    {
                        int x = max(l - 1, 0), y = max(p - 1, 0);
                        dp[i + 1][j][p + 1][x] = (dp[i + 1][j][p + 1][x] + dp[i][j][p][l]) % 12345678;
                        dp[i][j + 1][y][l + 1] = (dp[i][j + 1][y][l + 1] + dp[i][j][p][l]) % 12345678;
                    }
    int res = 0;
    for (int i = 0; i <= k; ++i)
        for (int j = 0; j <= k; ++j)
            res = (res + dp[n][m][i][j]) % 12345678;
    printf("%d", res);
    return 0;
}
