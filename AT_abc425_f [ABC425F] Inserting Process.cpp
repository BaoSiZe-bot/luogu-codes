#include <cstdio>

namespace Fujiwara
{
using ll = long long;
ll M = 998244353;
ll dp[1 << 25];
int n, fnl;
char t[25];

static int Azusa()
{
    scanf("%d%22s", &n, t);
    dp[fnl = (1 << n) - 1] = 1;
    for (int i = fnl; i; --i)
        for (int j = 0, lst = '$'; j < n; ++j)
            if ((i >> j) & 1)
            {
                if (lst != t[j])
                    (dp[i ^ (1 << j)] += dp[i]) %= M;
                lst = t[j];
            }
    printf("%lld\n", dp[0]);
    return 0;
}
}  // namespace Fujiwara
int main()
{
    return Fujiwara::Azusa();
}
