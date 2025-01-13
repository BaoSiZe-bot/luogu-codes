#include <bits/stl_algobase.h>
#include <bits/stl_algo.h>
#include <stdio.h>
const int N = 1e6, M = 2e6;
using ll = long long;
int a[M + 1];
ll d[M + 1];
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        int x;
        scanf("%d", &x);
        a[x + N]++;
    }
    for (int i = 0; i <= M; ++i)
        d[0] += a[i] * i;
    int l = 0, r = n;
    for (int i = 1; i <= M; ++i)
    {
        l += a[i - 1];
        d[i] = d[i - 1] + l - r;
        r -= a[i];
    }
    std::sort(d, d + M + 1);
    ll res = 0;
    for (int i = 0; i < k; ++i)
        res += d[i];
    printf("%lld", res);
    return 0;
}
