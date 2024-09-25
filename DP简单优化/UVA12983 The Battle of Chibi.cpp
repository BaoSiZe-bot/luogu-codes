#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <algorithm>

const int M = 1e9 + 7;
int a[1005], b[1005], l[1005], s[1005], dp[1005][1005], n, m;

inline int lb(int x)
{
    return x & -x;
}
inline void add(int x, int k)
{
    for (int i = x; i <= n; i += lb(i))
        (s[i] += k) %= M;
}
inline int qry(int x)
{
    int res = 0;
    for (int i = x; i; i -= lb(i))
        (res += s[i]) %= M;
    return res;
}
int main()
{
    int t;
    scanf("%d", &t);
    for (int _ = 1; _ <= t; ++_)
    {
        memset(dp, 0, sizeof dp);
        memset(l, 0, sizeof l);
        scanf("%d%d", &n, &m);
        a[0] = INT_MIN;
        b[0] = a[0];
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", a + i);
            b[i] = a[i];
        }
        std::sort(b, b + n + 1);
        int len = std::unique(b, b + n + 1) - b - 1;
        for (int i = 0; i <= n; ++i)
            l[i] = std::lower_bound(b, b + len + 1, a[i]) - b;
        dp[0][0] = 1;
        for (int i = 1; i <= m; ++i)
        {
            memset(s, 0, sizeof s);
            add(1, dp[i - 1][0]);
            for (int j = 1; j <= n; j++)
            {
                dp[i][j] = qry(l[j]);
                add(l[j] + 1, dp[i - 1][j]);
            }
        }
        int res = 0;
        for (int i = 1; i <= n; ++i)
            (res += dp[m][i]) %= M;
        printf("Case #%d: %d\n", _, res);
    }
    return 0;
}

