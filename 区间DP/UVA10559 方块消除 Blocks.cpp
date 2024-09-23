#include <csetjmp>
#include <stdio.h>
#include <string.h>

int a[205], p[205], h[205], dp[205][205][205];

inline int max(int u, int v)
{
    return u < v ? v : u;
}
inline int dfs(int l, int r, int k)
{
    if (l > r)
        return 0;
    if (!~dp[l][r][k])
    {
        dp[l][r][k] = max(dp[l][r][k], dfs(l, r - 1, 0) + (k + 1) * (k + 1));
        for (int i = p[r]; i >= l; i = p[i])
            dp[l][r][k] = max(dp[l][r][k], dfs(l, i, k + 1) + dfs(i + 1, r - 1, 0));
    }
    return dp[l][r][k];
}
int main()
{
    int t, id = 0;
    scanf("%d", &t);
    while (++id <= t)
    {
        int n;
        scanf("%d", &n);
        memset(p, 0, sizeof p);
        memset(h, 0, sizeof h);
        memset(dp, 0xff, sizeof dp);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", a + i);
            p[i] = h[a[i]];
            h[a[i]] = i;
        }
        printf("Case %d: %d\n", id, dfs(1, n, 0));
    }
    return 0;
}
