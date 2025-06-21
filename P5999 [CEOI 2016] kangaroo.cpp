#include <cstdio>
#include <sec_api/stdio_s.h>
const int M = 1e9 + 7, N = 2e3 + 7;
using ll = long long;
ll dp[N][N];
int main()
{
    int n, s, t;
    scanf("%d%d%d", &n, &s, &t);
    dp[1][1] = 1;
    for (int i = 2; i <= n; ++i)
        for (int j = 1; j <= i; ++j)
            dp[i][j] = i ^ s && i ^ t ? ((j * (dp[i - 1][j + 1] + dp[i - 1][j - 1]) % M - ((i > s) + (i > t)) * dp[i - 1][j - 1]) % M + M) % M : (dp[i - 1][j - 1] + dp[i - 1][j]) % M;
    printf("%lld\n", dp[n][1]);
    return 0;
}
