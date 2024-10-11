#include <algorithm>
#include <stdio.h>
#include <vector>
#define ONLINE_JUDGE luogu
using ll = long long;  // 十年 OI 一场空，不开 __ 见祖宗
const int N = 1e5 + 5;
int t, n, m;
ll _ [100005];
std::vector<ll> a[100005], b[100005], d[100005];
inline ll abs(ll a)
{
    return a < 0 ? -a : a;
}
int main()
{
#ifndef ONLINE_JUDGE
    freopen("matrix.in", "r", stdin);
    freopen("matrix.out", "w", stdout);
#endif
    scanf("%d", &t);
    while (t--)
    {
        scanf("%d%d", &n, &m);
        for (int i = 1; i <= n; ++i)
        {
            a[i].clear();
            a[i].emplace_back(0);
            for (int j = 1, x; j <= m; ++j)
            {
                scanf("%d", &x);
                a[i].emplace_back(x);
            }
        }
        for (int i = 1; i <= n; ++i)
        {
            b[i].clear();
            d[i].clear();
            b[i].emplace_back(0);
            d[i].emplace_back(0);
            for (int j = 1, x; j <= m; ++j)
            {
                scanf("%d", &x);
                b[i].emplace_back(x);
                d[i].emplace_back(x - a[i][j]);
            }
        }
        bool f = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                f |= (d[i][j] - d[i][1] ^ d[1][j] - d[1][1]);
        if (f)
        {
            printf("-1\n");
            continue;
        }
        for (int i = 1; i <= n; ++i)
            _[i] = d[1][1] - d[i][1];
        for (int i = 1; i <= m; ++i)
            _[n + i] = d[1][i];
        std::sort(_ + 1, _ + n + m + 1);
        ll md = _[(n + m + 1) >> 1], res = 0;
        for (int i = 1; i <= n + m; ++i)
            res += abs(_[i] - md);
        printf("%lld\n", res);
    }
    return 0;
}
