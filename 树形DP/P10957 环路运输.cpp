#include <stdio.h>

int a[2000005], q[2000005];

inline int max(int u, int v)
{
    return u < v ? v : u;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", a + i);
        a[i + n] = a[i];
    }
    int res = 0, hd = 1, tl = 0;
    for (int i = 1; i <= n * 2; ++i)
    {
        while (hd <= tl && (i - q[hd]) * 2 > n)
            ++hd;
        if (hd <= tl)
            res = max(res, a[i] + a[q[hd]] + i - q[hd]);
        while (hd <= tl && a[q[tl]] - q[tl] <= a[i] - i)
            --tl;
        q[++tl] = i;
    }
    printf("%d", res);
    return 0;
}
