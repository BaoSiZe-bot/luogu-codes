#include <string.h>
#include <stdio.h>
int d[105][105];
int max(int a, int b)
{
    return a < b ? b : a;
}
int main()
{
    memset(d, 0x3f, sizeof d);
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
    {
        int a, b;
        scanf("%d%d", &a, &b);
        d[a][b] = d[b][a] = 1;
    }
    for (int i = 1; i <= n; ++i)
        d[i][i] = 0;
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (d[i][k] + d[k][j] < d[i][j])
                    d[i][j] = d[i][k] + d[k][j];
    int res = 0xc0c0c0c0;
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            res = max(res, d[i][j]);
    printf("%d", res);
    return 0;
}
