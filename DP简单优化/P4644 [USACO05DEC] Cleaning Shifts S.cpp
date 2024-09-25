#include <algorithm>
#include <cstring>
#include <stdio.h>

const int M = 1e6 + 5, X = 0x7f7f7f7f;
struct Node
{
    int p, q, s;
    bool operator<(const Node &x) const
    {
        return q < x.q;
    }
} a[M];
int s[M], dp[M], n, m, e;

inline int lb(int x)
{
    return x & -x;
}
inline void cmin(int &a, int b)
{
    a = (a < b ? a : b);
}
inline void add(int x, int k)
{
    for (int i = M - x; i <= M; i += lb(i))
        cmin(s[i], k);
}
inline int qry(int x)
{
    int res = X;
    for (int i = M - x; i; i -= lb(i))
        cmin(res, s[i]);
    return res;
}
int main()
{
    memset(s, 0x7f, sizeof s);
    memset(dp, 0x7f, sizeof dp);
    scanf("%d%d%d", &n, &m, &e);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d%d", &a[i].p, &a[i].q, &a[i].s);
    std::sort(a + 1, a + n + 1);
    int res = X;
    for (int i = 1; i <= n; ++i)
    {
        add(a[i].q, dp[i] = (a[i].p > m) * qry(a[i].p - 1) + a[i].s);
        if (a[i].q >= e)
            cmin(res, dp[i]);
    }
    if (res == X)
        printf("-1");
    else
        printf("%d", res);
    return 0;
}
