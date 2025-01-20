#include <algorithm>
#include <cstring>
#include <stdio.h>
const int N = 1e5 + 5;
int c[N], tmp[N], n;
inline bool chk(int mid)
{
    if (mid == 1)
        return true;
    memcpy(tmp, c, sizeof c);
    std::sort(tmp + 1, tmp + mid);
    for (int i = 1; i < mid; ++i)
        if (tmp[i] > n - mid + i - 1)
            return false;
    return true;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", c + i);
    int l = 0, r = n, res = 0;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (chk(mid))
        {
            res = mid;
            l = mid + 1;
        }
        else
            r = mid - 1;
    }
    printf("%d", n - res);
    return 0;
}
