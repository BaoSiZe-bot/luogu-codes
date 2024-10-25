#include <stdio.h>
const int N = 505, M = 998244353;
long long f[N][N];
int n, b[N], t[N];
char s[N];
__always_inline int g(int x, int y)
{
    return x + y > 7 ? 3 : x > 0 && !(x + y) || x > 3 && y < 0 || x > 0 && y > 3;
}
int main()
{
    scanf("%d%s", &n, s + 1);
    if (n & 1)
        return 0 * printf("0");
    b['('] = 1;
    b['['] = 2;
    b['{'] = 3;
    b[')'] = -1;
    b[']'] = -2;
    b['}'] = -3;
    b['?'] = 4;
    for (int i = 1; i <= n; ++i)
    {
        t[i] = b[s[i]];  // fill column is 80 not 100!
        f[i][i - 1] = 1;
    }
    for (int i = 2; i <= n; i += 2)
        for (int l = 1; l + i - 1 <= n; ++l)
        {
            int r = l + i - 1;
            (f[l][r] += g(t[l], t[r]) * f[l + 1][r - 1]) %= M;
            for (int k = l + 1; k < r; k += 2)
                (f[l][r] += f[l + 1][k - 1] * f[k + 1][r] * g(t[l], t[k])) %= M;
        }
    return 0 * printf("%lld\n", f[1][n]);
}
