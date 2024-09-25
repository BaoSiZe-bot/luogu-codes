#include <stdio.h>
#include <algorithm>

struct Node
{
    int l, p, s;
    bool operator<(const Node &other) const
    {
        return s < other.s;
    }
} a[105];
int n, m, hd, tl, q[16005], dp[105][16005];

inline int max(int a, int b)
{
    return a < b ? b : a;
}
inline int f(int i, int j)
{
    return dp[i - 1][j] - a[i].p * j;
}
int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d%d%d", &a[i].l, &a[i].p, &a[i].s);
    std::sort(a + 1, a + m + 1);
    for (int i = 1; i <= m; ++i)
    {
        hd = 1;
        tl = 0;
        for (int j = max(0, a[i].s - a[i].l); j <= a[i].s - 1; ++j)
        {
            while (hd <= tl && f(i, q[tl]) <= f(i, j))
                --tl;
            q[++tl] = j;
        }
        for (int j = 1; j <= n; ++j)
        {
            dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            if (j - a[i].s >= 0)
            {
                while (hd <= tl && q[hd] + a[i].l < j)
                    ++hd;
                if (hd <= tl)
                    dp[i][j] = max(dp[i][j], f(i, q[hd]) + a[i].p * j);
            }
        }
    }
    printf("%d", dp[m][n]);
    return 0;
}
