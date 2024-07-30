#include <stdio.h>
#include <string.h>
int a[1005][1005], dp[1005][1005], dl[1005][1005], stk[1005], pos = 505, top;
int main()
{
    memset(dp, 0xcf, sizeof dp);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
            scanf("%d", a[i] + j);
    for (int i = 0; i <= m; ++i)
        dp[0][i] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = m - n + i; j >= i; --j)
            for (int k = j - 1; k >= i - 1; --k)
                (dp[i][j] < dp[i - 1][k] + a[i][j]) && (dl[i][j] = k, dp[i][j] = dp[i - 1][k] + a[i][j]);
    for (int i = m; i >= n; --i)
        (dp[n][i] >= dp[n][pos]) && (pos = i);
    printf("%d\n", dp[n][pos]);
    for (int i = n; i; --i)
    {
        stk[++top] = pos;
        pos = dl[i][pos];
    }
    while (top)
        printf("%d ", stk[top--]);
    return 0;
}
