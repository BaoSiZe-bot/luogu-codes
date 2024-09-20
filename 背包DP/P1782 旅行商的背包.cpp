#include <bits/stdc++.h>
#define int long long
#define ri register int

using namespace std;

const int maxn = 100005;
int dp[100005], nv[100005], nw[100005];
template <class T>
inline void read(register T &x)
{
    scanf("%lld", &x);
}
template <class T, typename... Argv>
inline void read(register T &x, register Argv &...args)
{
    read(x);
    read(args...);
}
signed main()
{
    int n, m, c, cnt = 0;
    read(n, m, c);
    for (ri i = 1; i <= n; ++i)
    {
        int v, w, d, t = 1;
        read(v, w, d);
        while (d)
        {
            if (d - t < 0)
            {
                t = d;
                d = 0;
            }
            else
                d -= t;
            nw[++cnt] = t * w, nv[cnt] = t * v;
            t <<= 1;
        }
    }
    for (ri i = 1; i <= cnt; ++i)
        for (ri k = c; k >= nv[i]; --k)
            dp[k] = max(dp[k], dp[k - nv[i]] + nw[i]);
    for (ri i = 1; i <= m; ++i)
    {
        int x, y, z;
        read(x, y, z);
        for (ri k = c; k >= 0; --k)
            for (ri j = 0; j <= c; ++j)
            {
                int u = j, v = (x * j + y) * j + z;
                if (k >= u)
                    dp[k] = max(dp[k], dp[k - u] + v);
            }
    }
    printf("%lld\n", dp[c]);
    return 0;
}
