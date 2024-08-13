#include <cstring>
#include <stdio.h>
#define int long long
using dl = double;
int dc[105][105];
int k[105][105];
signed main()
{
    int n, m;
    scanf("%lld%lld", &n, &m);
    memset(k, 0x3f, sizeof(k));
    for (int i = 1; i <= m; ++i)
    {
        int u, v, w;
        scanf("%lld%lld%lld", &u, &v, &w);
        k[u][v] = k[v][u] = w;
        dc[u][v] = dc[v][u] = 1;
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
            {
                if (k[i][k] == 0x3f3f3f3f3f3f3f3f && k[k][j] == 0x3f3f3f3f3f3f3f3f)
                    continue;
                if (k[i][j] == k[i][k] + k[k][j])
                    dc[i][j] += dc[i][k] * dc[k][j];
                if (k[i][j] > k[i][k] + k[k][j])
                {
                    k[i][j] = k[i][k] + k[k][j];
                    dc[i][j] = dc[i][k] * dc[k][j];
                }
            }
    for (int v = 1; v <= n; ++v)
    {
        dl res = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                if (i ^ v && j ^ v && i ^ j && k[i][j] == k[i][v] + k[v][j])
                    res += (dc[i][v] * dc[v][j]) * 1.0 / dc[i][j];
        printf("%.3lf\n", res);
    }
    return 0;
}
