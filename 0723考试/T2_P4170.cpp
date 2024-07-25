#include <cstdio>
#include <cstring>
char s[1005];
int dp[1005][1005];
inline int min(int a, int b)
{
    return a < b ? a : b;
}
int main()
{
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    memset(dp, 0x3f, sizeof dp);
    for (int i = 1; i <= n; ++i)
        dp[i][i] = 1;
    for (int l = 1; l < n; ++l)
        for (int i = 1; i <= n - l; ++i)
        {
            int j = i + l;
            if (s[i] ^ s[j])
                for (int k = i; k < j; ++k)
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k + 1][j]);
            else
                dp[i][j] = min(dp[i][j - 1], dp[i + 1][j]);
        }
    printf("%d\n", dp[1][n]);
    return 0;
}
