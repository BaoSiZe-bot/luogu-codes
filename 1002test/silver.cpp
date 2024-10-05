#include <bits/stl_algobase.h>
#include <bits/stl_algo.h>
#include <unordered_map>
#include <stdio.h>
using ull = unsigned long long;
using ll = long long;
ll fct[1000005], cnt[1000005];
std::unordered_map<ull, ll> mp;
ull hs[1000005], hsum;
const int M = 998244353;
int n, a;
inline ll dfs(int s, int sur, ull hsval)
{
    if (s >= 50 || !sur)
        return fct[sur];
    if (mp.count(hsval))
        return mp[hsval];
    ll &dp = mp[hsval];
    for (int i = 1; i <= s; ++i)
        if (cnt[i])
        {
            --cnt[i];
            (dp += (cnt[i] + 1) * dfs(s + i, sur - 1, hsval - hs[i])) %= M;
            ++cnt[i];
        }
    return dp;
}
int main()
{
    scanf("%d%d", &n, &a);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        scanf("%d", &x);
        cnt[x]++;
    }
    fct[0] = hs[0] = 1;
    for (int i = 1; i <= n; ++i)
        fct[i] = fct[i - 1] * i % M;
    for (int i = 1; i <= 50; ++i)
    {
        hs[i] = hs[i - 1] * 57;
        hsum += hs[i] * cnt[i];
    }
    ll init = dfs(a, n - cnt[0], hsum);
    //calculating A(n, n - cnt[0]);
    for (int i = n - cnt[0] + 1; i <= n; ++i)
        (init *= i) %= M;
    return 0 * printf("%lld", init);
}
