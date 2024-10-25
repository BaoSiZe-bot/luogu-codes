#include <math.h>
#include <stdio.h>
#include <string.h>
const int N = 1e5 + 5, M = 515, K = 1e6 + 5;
int v[K], w[K], tw[K], tv[K], dp[N][M], b[M];
__always_inline int max(int x, int y)
{
    return x < y ? y : x;
}
int main()
{
    int n, q, sr;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", v + i, w + i);
    sr = sqrt(n);
    for (int i = 1; i <= sr; ++i)
    {
        memcpy(dp[i], dp[i >> 1], sizeof dp[i]);
        for (int j = N - 5; j >= w[i]; --j)
            dp[i][j] = max(dp[i][j], dp[i][j - w[i]] + v[i]);
    }
    scanf("%d", &q);
    while (q--)
    {
        int t, l, r, tp = 0, res;
        scanf("%d%d", &t, &l);
        r = t;
        for (; r > sr; r >>= 1)
            b[tp++] = r;
        res = dp[sr][l];
        for (int i = 1; i <= (1 << tp); ++i)
        {
            int lb = __builtin_ctz(i);
            tv[i] = tv[i & (i - 1)] + v[b[lb]];  // 运算优先级
            if ((tw[i] = tw[i & (i - 1)] + w[b[lb]]) <= l)
                res = max(res, dp[r][l - tw[i]] + tv[i]);
        }
        printf("%d\n", res);
    }
    return 0;
}
