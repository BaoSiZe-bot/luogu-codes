#include <stdio.h>
int bk[100005];
inline int clc(int a, int b, int c, int d, int e)
{
    return a * 10000 + b * 1000 + c * 100 + d * 10 + e;
}
int main()
{
    int n, res = 0;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int a, b, c, d, e;
        scanf("%d%d%d%d%d", &a, &b, &c, &d, &e);
        for (int j = 1; j <= 9; ++j)
        {
            bk[clc(a, b, c, d, (e + j) % 10)]++;
            bk[clc(a, b, c, (d + j) % 10, (e + j) % 10)]++;
            bk[clc(a, b, c, (d + j) % 10, e)]++;
            bk[clc(a, b, (c + j) % 10, (d + j) % 10, e)]++;
            bk[clc(a, b, (c + j) % 10, d, e)]++;
            bk[clc(a, (b + j) % 10, (c + j) % 10, d, e)]++;
            bk[clc(a, (b + j) % 10, c, d, e)]++;
            bk[clc((a + j) % 10, (b + j) % 10, c, d, e)]++;
            bk[clc((a + j) % 10, b, c, d, e)]++;
        }
    }
    for (int i = 0; i <= 9; ++i)
        for (int j = 0; j <= 9; ++j)
            for (int k = 0; k <= 9; ++k)
                for (int p = 0; p <= 9; ++p)
                    for (int l = 0; l <= 9; ++l)
                        res += (bk[clc(i, j, k, p, l)] == n);
    printf("%d\n", res);
    return 0;
}
