#include <stdio.h>
#include <string.h>
using ll = long long;
char s1[105], s2[105];
int n1, n2, l1, l2;
ll dp[105][105];
int main()
{
    while (scanf("%s%d%s%d", s2, &n2, s1, &n1) == 4)
    {
        memset(dp, 0, sizeof dp);
        l1 = strlen(s1);
        l2 = strlen(s2);
        ll res = 0, t = 0;
        for (int i = 0; i < l1; ++i)
        {
            int p = i;
            dp[i][0] = 0;
            for (int j = 0; j < l2; ++j)
            {
                int id = 0;
                while (s1[p] != s2[j])
                {
                    p = (p + 1) % l1;
                    if (++id >= l1)
                        goto out;
                }
                p = (p + 1) % l1;
                dp[i][0] += id + 1;
            }
        }
        for (int i = 1; i <= 30; ++i)
            for (int j = 0; j < l1; ++j)
                dp[j][i] = dp[j][i - 1] + dp[(j + dp[j][i - 1]) % l1][i - 1];
        for (int i = 30; ~i; --i)
            if (t + dp[(t + l1) % l1][i] <= l1 * n1)
            {
                t += dp[(t + l1) % l1][i];
                res += 1 << i;
            }
        res /= n2;
        goto out;
    out:
        printf("%lld\n", res);
    }
    return 0;
}
