#include <stdio.h>
#include <string.h>

char s[105];
int d[105], dp[105][105];

int min(int a, int b)
{
    return a < b ? a : b;
}
inline bool chk(int l, int r, int len)
{
    for (int i = l + len; i <= r; ++i)
        if (s[i] != s[(i - l) % len + l])
            return false;
    return true;
}
int main()
{
    memset(dp, 0x3f, sizeof dp);
    scanf("%100s", s + 1);
    int n = (int)strlen(s + 1);
    for (int i = 1; i <= 100; ++i)
        d[i] = d[i / 10] + 1;
    for (int i = 1; i <= n; ++i)
        dp[i][i] = 1;
    for (int i = 2; i <= n; ++i)
        for (int l = 1; l <= n - i + 1; ++l)
        {
            int r = l + i - 1;
            for (int k = l; k < r; ++k)
                dp[l][r] = min(dp[l][r], dp[l][k] + dp[k + 1][r]);
            for (int k = l; k < r; ++k)
            {
                int len = k - l + 1;
                if (i % len != 0)
                    continue;
                if (chk(l, r, len))
                    dp[l][r] = min(dp[l][r], dp[l][k] + d[i / len] + 2);
            }
        }
    printf("%d", dp[1][n]);
    return 0;
}
