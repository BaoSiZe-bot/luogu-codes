#include <algorithm>
#include <stdio.h>
const int N = 1e6 + 5;
long long a[N];
int p[N], h[N], b[64], c[64], n, i, res;
inline int fd(int x)
{
    while (p[x] ^ x)
        x = p[x] = p[p[x]];
    return x;
}
inline void mg(int x, int y)
{
    int fx = fd(x), fy = fd(y);
    if (fx ^ fy)
    {
        h[fx] < h[fy] ? p[fx] = fy : p[fy] = fx;
        if (h[fx] == h[fy])
            h[fx]++;
    }
}
int main()
{
    scanf("%d", &n);
    for (i = 1; i <= n; ++i)
    {
        scanf("%lld", a + i);
        p[i] = i;
    }
    std::sort(a + 1, a + 1 + n);
    for (i = 1; i <= n; ++i)
    {
        for (int j = 63 - __builtin_clzll(a[i]); ~j; --j)
            !(a[i] >> j & 1) && b[j] && (c[j] ? (mg(i, c[j]), 0) : c[j] = fd(i));
        ++b[63 - __builtin_clzll(a[i])];
    }
    for (i = 1; i <= n; ++i)
        c[63 - __builtin_clzll(a[i])] && (mg(i, c[63 - __builtin_clzll(a[i])]), 0);
    for (i = 1; i <= n; ++i)
        res += fd(i) == i;
    printf("%d", res);
    return 0;
}
