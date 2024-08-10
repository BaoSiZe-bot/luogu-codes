#include <stdio.h>
#include <bits/stl_algobase.h>
#include <bits/stl_algo.h>
int m, n, a[5005], b[2005], s[2005], k;
inline bool chk(int mid, int p, int g) 
{
    if (k - g < s[mid])
        return 0;
    if (!mid)
        return 1;
    bool f = 0;
    for (int i = p; i <= n; i++)
        if (a[i] >= b[mid])
        {
            a[i] -= b[mid];
            int gg = g + (a[i] < b[1]) * a[i];
            if ((b[mid] ^ b[mid - 1] && chk(mid - 1, 1, gg)) || (b[mid] == b[mid - 1] && chk(mid - 1, i, gg)))
            {
                a[i] += b[mid];
                return 1;
            }
            a[i] += b[mid];
        }
    return 0;
}
int main()
{
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i)
    {
        scanf("%d", &a[i]);
        k += a[i];
    }
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &b[i]);
    int l = 1, r = n, res = 0;
    std::sort(b + 1, b + n + 1);
    for (int i = 1; i <= n; ++i)
        s[i] = s[i - 1] + b[i];
    while(s[n] > k)
        --n;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (chk(mid, 1, 0))
        {
            l = mid + 1;
            res = mid;
        }
        else
            r = mid - 1;
    }
    printf("%d\n", res);
    return 0;
}
