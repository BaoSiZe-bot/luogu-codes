#include <stdio.h>
const int N = 1e6 + 5;
int a[N], st[22][N], lg[N], M, n, k;
inline int max(int a, int b)
{
    return a < b ? b : a;
}
inline int maxp(int x, int y)
{
    // printf("%d%d\n", x, y);
    return a[x] < a[y] ? y : x;
}
inline int qry(int l, int r)
{
    int k = lg[r - l + 1];
    return maxp(st[k][l], st[k][r - (1 << k) + 1]);
}
inline int divide(int l, int r)
{
    if (l < 1 || r > n || r < l)
        return 0;
    int t = qry(l, r), rls = 0, rrs = 0;
    // printf("%d %d %d\n", l, r, t);
    if (a[t] % M)
    {
        l ^ 1 && (rrs = divide(t + 1, r));
        r ^ n && (rls = divide(l, t - 1));
        return max(rls, rrs);
    }
    return divide(l, t - 1) + 1 + divide(t + 1, r);
    // return 0;
}
int main()
{
    scanf("%d%d", &n, &k);
    for (int i = 2; i <= 100000; ++i)
        lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", a + i);
        st[0][i] = i;
    }
    for (int i = 1; i <= 20; ++i)
        for (int j = 1; j <= n - (1 << i) + 1; ++j)
            st[i][j] = maxp(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
    int mxp = a[qry(1, n)];
    for (M = mxp; M; --M)
        if (mxp % M == 0 && divide(1, n) >= k)
            return 0 * printf("%d", M);
    return 0;
}
