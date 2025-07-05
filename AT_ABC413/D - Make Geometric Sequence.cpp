#include <algorithm>
#include <cstdlib>
#include <stdio.h>
const int N = 2e5 + 5;
const long double eps = 1e-15;
int a[N];
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        int n, c0 = 0, c1 = 1, c2 = 0;
        scanf("%d", &n);
        for (int i = 1; i <= n; ++i)
        {
            scanf("%d", a + i);
            if (!a[i])
                ++c0;
            if (i > 1)
            {
                if (a[i] == a[1])
                    ++c1;
                if (a[i] == -a[1])
                    ++c2;
            }
        }
        if (n == 2)
        {
            printf("Yes\n");
            continue;
        }
        if (c1 + c2 == n)
        {
            if (c1 == n || c2 == n || abs(c1 - c2) <= 1)
                printf("Yes\n");
            else
                printf("No\n");
            continue;
        }
        if (c0 >= n - 1)
        {
            printf("Yes\n");
            continue;
        }
        std::sort(a + 1, a + n + 1, [](int a, int b) { return abs(a) < abs(b); });
        bool f = true;
        for (int i = 3; i <= n; ++i)
            if (1ll * a[i] * a[i - 2] != 1ll * a[i - 1] * a[i - 1])
            {
                f = false;
                break;
            }
        printf(f ? "Yes\n" : "No\n");
    }
    return 0;
}
