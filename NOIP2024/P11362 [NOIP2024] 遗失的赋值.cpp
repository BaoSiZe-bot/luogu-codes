#include <algorithm>
#include <stdio.h>
#include <utility>
const int N = 100005, M = 1e9 + 7;
using ll = long long;
std::pair<int, int> a[N];
#define c first
#define d second
inline ll qp(ll a, int b, int p = M)
{
    ll res = 1;
    while (b)
    {
        if (b & 1)
            res = res * a % p;
        a = a * a % p;
        b >>= 1;
    }
    return res;
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, m;
        ll v;
        scanf("%d%d%lld", &n, &m, &v);
        for (int i = 1; i <= m; ++i)
            scanf("%d%d", &a[i].c, &a[i].d);
        std::sort(a + 1, a + m + 1);
        ll res = qp(v, (a[1].c - 1) << 1);
        for (int i = 1; i < m; i++)
            if (a[i].c ^ a[i + 1].c)
                (res *= (qp(v, (a[i + 1].c - a[i].c) << 1) - (v - 1) * qp(v, a[i + 1].c - a[i].c - 1) % M + M)) %= M;
            else if (a[i].d ^ a[i + 1].d)
                res = 0;
        printf("%lld\n", res * qp(v, (n - a[m].c) << 1) % M);
    }
    return 0;
}
#undef c
#undef d
