#include <string.h>
#include <stdio.h>
char s[55];
int dp[55][55][2];
inline bool chk(int l, int r)
{
    if ((r - l + 1) & 1)
        return false;
    int mid = (l + r) >> 1;
    for (int i = l; i <= mid; ++i)
        if (s[i] ^ s[i + mid - l + 1])
            return false;
    return true;
}
inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline int gr(int l, int r)
{
    return min(dp[l][r][0], dp[l][r][1]);
}
int main()
{
    memset(dp, 0x3f, sizeof(dp));
    scanf("%50s", s + 1);
    int n = (int)strlen(s + 1);
    for (int i = 1; i <= n; ++i)
        for (int j = i; j <= n; ++j)
            dp[i][j][0] = dp[i][j][1] = j - i + 1;
    for (int l = 2; l <= n; ++l)
        for (int i = 1, j = l; j <= n; ++i, ++j)
        {
            if (chk(i, j))
                dp[i][j][0] = min(dp[i][j][0], dp[i][(i + j) / 2][0] + 1);
            for (int k = i; k < j; ++k)
                dp[i][j][0] = min(dp[i][j][0], dp[i][k][0] + j - k);
            for (int k = i; k < j; ++k)
                dp[i][j][1] = min(dp[i][j][1], gr(i, k) + gr(k + 1, j) + 1);
        }
    printf("%d\n", gr(1, n));
    return 0;
}
