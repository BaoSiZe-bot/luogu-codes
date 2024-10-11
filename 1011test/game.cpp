#include <algorithm>
#include <cstdio>
#include <functional>
using ll = long long;
int a[1000005];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, p;
        scanf("%d%d", &n, &p);
        for (int i = 1; i <= n; ++i)
            scanf("%d", a + i);
        if (n < 3)
        {
            printf("%d\n", 0);
            continue;
        }
        std::sort(a + 1, a + n + 1, std::greater<int>());
        ll res = 0;
        if (p & 1)
        {
            for (int i = 3; i <= n; ++i)
                res += (a[i] + n >= a[3] + 1);
            for (int i = 3; i <= n; ++i)
                res += (a[i] + n >= a[2] + 1) * (i - 3);
            for (int i = 4; i <= n; ++i)
                res += (a[i] + n >= a[1] + 1) * (i - 3ll) * (i - 2) >> 1;
        }
        else
        {
            for (int i = 3; i <= n; ++i)
                res += (a[i] + n >= a[2] + 1);
            for (int i = 4; i <= n; ++i)
                res += (a[i] + n >= a[2] + 1) * (i - 3);
            for (int i = 4; i <= n; ++i)
                res += (a[i] + n >= a[1] + 1) * (i - 3ll) * (i - 2) >> 1;
        }
        printf("%lld\n", res);
    }
    return 0;
}
