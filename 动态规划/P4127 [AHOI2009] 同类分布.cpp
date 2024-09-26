#include <cstring>
#include <stdio.h>
#define int long long

int n, a, b, M, ss[25], dp[25][205][205];
int dfs(int p, int s, int y, bool l)
{
    if (p > n)
        return !y && s == M;
    if (!l && ~dp[p][s][y])
        return dp[p][s][y];
    int t = (l ? ss[n - p + 1] : 9), res = 0;
    for (int i = 0; i <= t; ++i)
        res += dfs(p + 1, s + i, (y * 10 + i) % M, i == t && l);
    !l && (dp[p][s][y] = res);
    return res;
}
inline int work(int x)
{
    n = M = 0;
    while (x)
    {
        ss[++n] = x % 10;
        x /= 10;
    }
    int res = 0;
    while (++M <= 9 * n)
    {
        memset(dp, 0xff, sizeof dp);
        res += dfs(1, 0, 0, 1);
    }
    return res;
}
signed main()
{
    int a, b;
    scanf("%lld%lld", &a, &b);
    printf("%lld", work(b) - work(a - 1));
    return 0;
}
