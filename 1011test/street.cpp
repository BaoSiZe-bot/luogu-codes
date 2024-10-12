#include <stdio.h>
using ll = long long;
const int N = 5005, M = 1e9 + 7, MX = 10005;
int s[N], pl;
ll dp[N][MX], res = 1;
int main()
{
    int n, k, x;
    scanf("%d%d%d%d", &n, &k, &x, s + 1);
    dp[0][1] = 1;
    for (int i = 1; i <= x + x; ++i)
    {
        int j = i + (i & 1);
        ll tot = 0;
        for (int k = 1; k <= MX - 5; ++k)
        {
            (tot += dp[i - 1][k - 1]) %= M;
            if (k >= j + 1)
                (tot -= dp[i - 1][k - j - 1] - M) %= M;
            dp[i][k] = (tot + (i + 1 >= k)) % M;
        }
    }
    for (int i = 1; i < k; i++)
    {
        scanf("%d", s + i);
        (res *= dp[((x - i) << 1) + 1][s[i] - s[i - 1]]) %= M;
    }
    printf("%lld", res);
    return 0;
}
