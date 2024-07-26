#include <cstdio>
#include <cstring>
using ll = long long;
ll dp[25][25], s[25], tot, len;
inline ll abs(ll x)
{
    return x < 0 ? ~x + 1 : x;
}
inline ll dfs(ll pr, ll nw, ll pz, ll lm)
{
    if (nw > len)
        return 1;
    if (~dp[pr][nw] && !lm)
        return dp[pr][nw];
    ll res = 0, l = lm ? s[len - nw + 1] : 9;
    for (int i = 0; i <= l; ++i)
    {
        if (abs(i - pr) < 2)
            continue;
        if (!i && pz)
            res += dfs(-2, nw + 1, 1, lm && i == l);
        else
            res += dfs(i, nw + 1, 0, lm && i == l);
    }
    (!lm && !pz) && (dp[pr][nw] = res);
    return res;
}
inline ll slv(ll x)
{
    len = 0;
    while (x)
    {
        s[++len] = x % 10;
        x /= 10;
    }
    return dfs(-2, 1, 1, 1);
}
int main()
{
    ll a, b;
    scanf("%lld%lld", &a, &b);
    memset(dp, 0xff, sizeof dp);
    printf("%lld\n", slv(b) - slv(a - 1));
    return 0;
}
