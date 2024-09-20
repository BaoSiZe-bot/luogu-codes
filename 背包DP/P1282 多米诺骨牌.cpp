#include <cstdio>
#include <cstring>

int dp[1005][11005], a[1005], b[1005];
const int M = 5e3;
inline int min(int a, int b)
{
    return a < b ? a : b;
}
int main()
{
    memset(dp, 0x7f, sizeof dp);
    dp[0][M] = 0;
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", a + i, b + i);
    for (int i = 1; i <= n; ++i)
        for (int j = -5000; j <= 5000; ++j)
            dp[i][j + M] = min(dp[i - 1][j + a[i] - b[i] + M] + 1, dp[i - 1][j + b[i] - a[i] + M]);
    int mn;
    for (int i = 0; i <= 5000; ++i)
    {
        mn = min(dp[n][M + i], dp[n][M - i]);
        if (mn < 1000)
        {
            printf("%d\n", mn);
            break;
        }
    }
    return 0;
}
