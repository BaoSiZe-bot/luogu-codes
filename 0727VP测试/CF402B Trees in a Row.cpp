#include <climits>
#include <cstdio>
int a[1005], b[1005], res = INT_MAX, mn = INT_MAX, mx = INT_MIN, resp = 0;
inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline int max(int a, int b)
{
    return a < b ? b : a;
}
int main()
{
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", a + i);
        mn = min(mn, a[i] - k * (i - 1));
        mx = max(mx, a[i] + k * (i - 1));
    }
    for (int st = 1; st <= 1000; ++st)
    {
        int cnt = 0;
        b[1] = st;
        for (int i = 2; i <= n; ++i)
            b[i] = b[i - 1] + k;
        for (int i = 1; i <= n; ++i)
            if (b[i] ^ a[i])
                ++cnt;
        if (res > cnt)
        {
            res = cnt;
            resp = st;
        }
    }
    printf("%d\n", res);
    b[1] = resp;
    for (int i = 2; i <= n; ++i)
        b[i] = b[i - 1] + k;
    for (int i = 1; i <= n; ++i)
        if (b[i] ^ a[i])
        {
            if (a[i] < b[i])
                printf("+ %d %d\n", i, b[i] - a[i]);
            else
                printf("- %d %d\n", i, a[i] - b[i]);
        }
    return 0;
}
