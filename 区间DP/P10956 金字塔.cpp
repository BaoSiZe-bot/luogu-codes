#include <stdio.h>
#include <string.h>
using ll = long long;
const int M = 1e9 + 7;

char s[305];
ll dp[305][305];

ll dfs(int l, int r)
{
    if (l > r || s[l] ^ s[r])
        return 0;
    if (l == r)
        return 1;
    if (!~dp[l][r])
    {
        dp[l][r] = 0;
        for (int i = l + 1; i < r; ++i)
            (dp[l][r] += dfs(l + 1, i) * dfs(i + 1, r) % M) %= M;
    }
    return dp[l][r];
}
int main()
{
    memset(dp, 0xff, sizeof dp);
    scanf("%300s", s + 1);
    printf("%lld", dfs(1, strlen(s + 1)));
    return 0;
}
