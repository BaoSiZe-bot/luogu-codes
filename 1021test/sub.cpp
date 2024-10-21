#include <cstring>
#include <stdio.h>
using ll = long long;
const ll N = 1e6 + 5, M = 998244353;
ll a[N], b[N], s[N][4], res, l, r;
__always_inline ll qp(ll a, ll b, ll p = M)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= p;
        (a *= a) %= p;
        b >>= 1;
    }
    return res;
}
__always_inline bool chk()
{
    if (s[r][1] == s[l - 1][1])
        return true;
    if (s[r][2] == s[l - 1][2])
        return true;
    if (s[r][3] == s[l - 1][3])
        return true;
    for (int i = l; i < r - 1; ++i)
        for (int j = i + 1; j < r; ++j)
            for (int k = j + 1; k <= r; ++k)
                if (i + 1 != j || j + 1 != k)
                    if (a[i] * a[j] * a[k] == 6)
                        return false;
    return true;
}
void dfs(ll p)
{
    if (p > r)
    {
        res += chk();
        return;
    }
    if (!a[p])
    {
        a[p] = 1;
        dfs(p + 1);
        a[p] = 2;
        dfs(p + 1);
        a[p] = 3;
        dfs(p + 1);
        a[p] = 0;
        return;
    }
    dfs(p + 1);
}
int main()
{
    ll n, q;
    scanf("%lld%lld", &n, &q);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%lld", a + i);
        for (int j = 0; j < 4; ++j)
            s[i][j] = s[i - 1][j] + (a[i] == j);
    }
    while (q--)
    {
        scanf("%lld%lld", &l, &r);
        if (r - l <= 2)
        {
            printf("%lld\n", qp(3, s[r][0] - s[l - 1][0]));
            continue;
        }
        if (r - l == 3)
        {
            res = 0;
            dfs(l);
            printf("%lld\n", res);
            continue;
        }
        int p = s[r][0] - s[l - 1][0];
        int q = (s[r][1] == s[l - 1][1]);
        q += (s[r][2] == s[l - 1][2]);
        q += (s[r][3] == s[l - 1][3]);
        if (!q)
            printf("0\n");
        else if (q == 1)
            printf("%lld\n", qp(2, p));
        else if (q == 2)
            printf("%lld\n", (qp(2, p + 1) - 1 + M) % M);
        else
            printf("%lld\n", (3 * qp(2, p) % M - 3 + M) % M);
    }
    return 0;
}
