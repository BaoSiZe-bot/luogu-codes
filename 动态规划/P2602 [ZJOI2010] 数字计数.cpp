#include <cstring>
#include <stdio.h>
#define int unsigned long long
int dp[15][15][15], a[15], l;
inline int qp(int a, int b)
{
    int res = 1;
    while (b)
        (b & 1) && (res *= a), b >>= 1, a *= a;
    return res;
}
inline int slv(int x, int k)
{
    l = 0;
    memset(a, 0, sizeof a);
    while (x)
    {
        a[++l] = x % 10;
        x /= 10;
    }
    int res = 0;
    for (int i = 1; i < l; ++i)
        for (int j = 0; j <= 9; ++j)
            res += dp[i][j][k];

    for (int i = 1; i < a[l]; ++i)
        res += dp[l][i][k];
    for (int i = l - 1; i >= 1; --i)
    {
        for (int j = 0; j < a[i]; ++j)
            res += dp[i][j][k];
        for (int j = l; j > i; --j)
            a[j] == k && (res += a[i] * qp(10, i - 1));
    }
    return res;
}
signed main()
{
    int a, b;
    scanf("%llu%llu", &a, &b);
    for (int i = 0; i <= 9; ++i)
        dp[1][i][i] = 1;
    for (int i = 2; i <= 13; ++i)
        for (int j = 0; j <= 9; ++j)
        {
            for (int k = 0; k <= 9; ++k)
                for (int l = 0; l <= 9; ++l)
                    dp[i][j][l] += dp[i - 1][k][l];
            dp[i][j][j] += qp(10, i - 1);
        }
    for (int i = 0; i <= 9; ++i)
        printf("%llu ", slv(b + 1, i) - slv(a, i));
    return 0;
}
