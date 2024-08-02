#include <cstdio>
int w[500005];
int n, a, b;
inline bool chk(int mid)
{
    int s = 0;
    for (int i = 1; i <= n; ++i)
    {
        int t = w[i] - a * mid;
        if (t > 0)
            s += t / b + bool(t % b);
        if (s > mid)
            return 0;
    }
    return 1;
}
int main()
{
    scanf("%d%d%d", &n, &a, &b);
    for (int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    int l = 0, r = 1e6, res = 1e6;
    while (l <= r)
    {
        int mid = (l + r) / 2;
        if (chk(mid))
        {
            res = mid;
            r = mid - 1;
        }
        else
            l = mid + 1;
    }
    printf("%d\n", res);
    return 0;
}
