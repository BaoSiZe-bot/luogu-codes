#include <stdio.h>
#include <stdlib.h>
using ll = long long;
ll dp[25][5];
inline int max(int a, int b)
{
    return a < b ? b : a;
}
int main()
{
    dp[0][0] = 1;
    for (int i = 1; i <= 20; ++i)
    {
        for (int j = 1; j <= 3; ++j)
        {
            dp[i][j] += dp[i - 1][j - 1];
            dp[i][0] += dp[i - 1][j - 1] * 9;
        }
        dp[i][3] += dp[i - 1][3] * 10;
    }
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int x, d = 3;
        scanf("%d", &x);
        while (dp[d][3] < x)
            ++d;
        int k = 0;
        for (int i = d; i; --i)
        {
            for (int j = 0; j <= 9; ++j)
            {
                ll tot = dp[i - 1][3];
                if (j == 6 || k == 3)
                    for (int p = max(3 - k - bool(j == 6), 0); p < 3; ++p)
                        tot += dp[i - 1][p];
                if (x - tot > 0)
                    x -= tot;
                else
                {
                    if (k < 3)
                        k = j ^ 6 ? 0 : k + 1;
                    printf("%d", j);
                    break;
                }
            }
        }
        printf("\n");
    }
    return 0;
}
