#include <iostream>
#include <bits/stl_pair.h>
#define fi first
#define se second
std::pair<int, int> p[105];
int s[105], dp[105][105][105], tot = 1;

inline int max(int a, int b)
{
    return a < b ? b : a;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    int n, m;
    std::cin >> n >> m;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= m; ++j)
        {
            char c;
            std::cin >> c;
            s[i] = (s[i] << 1) + !(c ^ 'H');
        }
    for (int i = 1; i < (1 << m); i++)
        if (!(i & (i << 1)) && !(i & (i << 2)) && !(i & (i >> 1)) && !(i & (i >> 2)))
            p[++tot] = {i, __builtin_popcount(i)};

    for (int i = 1; i <= tot; ++i)
    {
        if (!(p[i].fi & s[1]))
            dp[1][i][0] = p[i].se;
        if (!(p[i].fi & s[2]))
            for (int j = 1; j <= tot; j++)
                if (!(p[i].fi & p[j].fi) && !(p[j].fi & s[1]))
                    dp[2][i][j] = p[i].se + p[j].se;
    }

    for (int i = 3; i <= n; i++)
        for (int j = 1; j <= tot; j++)
            if (!(p[j].fi & s[i]))
                for (int k = 1; k <= tot; k++)
                    if (!(p[j].fi & p[k].fi) && !(p[k].fi & s[i - 1]))
                        for (int l = 1; l <= tot; l++)
                            if (!(p[j].fi & p[l].fi) && !(p[k].fi & p[l].fi) && !(p[l].fi & s[i - 2]))
                                dp[i][j][k] = max(dp[i][j][k], dp[i - 1][k][l] + p[j].se);
    int res = 0;
    for (int i = 1; i <= tot; i++)
        for (int j = 1; j <= tot; j++)
            res = std::max(res, dp[n][i][j]);
    if (n == 1)
    {
        for (int i = 1; i <= m; i += 3)
            res++;
        std::cout << res;
        return 0;
    }
    std::cout << res;
    return 0;
}
