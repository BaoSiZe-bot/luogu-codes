#include <algorithm>
#include <cstdio>
#include <cstring>

int a[205], c[205], w[100005], tot;
bool dp[100005];
int main()
{
    int n, m;
    while (scanf("%d%d", &n, &m), n || m)
    {
        memset(dp, 0, sizeof dp);
        dp[0] = 1;
        tot = 0;
        for (int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        for (int i = 1; i <= n; ++i)
            scanf("%d", c + i);
        for (int i = 1; i <= n; ++i)
        {
            int t = c[i], p = 1;
            while (t >= p)
            {
                w[++tot] = a[i] * p;
                t -= p;
                p <<= 1;
            }
            if (t > 0)
                w[++tot] = a[i] * t;
        }
        for (int i = 1; i <= tot; ++i)
            for (int j = m; j >= w[i]; --j)
                dp[j] |= dp[j - w[i]];
        printf("%d\n", static_cast<int>(std::count(dp + 1, dp + m + 1, 1)));
    }
    return 0;
}
