#include <cstring>
#include <stdio.h>
int t[2005][2], d[305][305];
double k[2005], dp[2005][2005][2];
inline int min(int a, int b)
{
    return a < b ? a : b;
}
inline double min(double a, double b)
{
    return a < b ? a : b;
}
int main()
{
    memset(d, 0x3f, sizeof d);
    memset(dp, 0x7f, sizeof dp);
    dp[1][0][0] = dp[1][1][1] = 0;
    int n, v, m, e;
    scanf("%d%d%d%d", &n, &m, &v, &e);
    for (int i = 1; i <= n; ++i)
        scanf("%d", t[i]);
    for (int i = 1; i <= n; ++i)
        scanf("%d", t[i] + 1);
    for (int i = 1; i <= n; ++i)
        scanf("%lf", k + i);
    for (int i = 1; i <= e; ++i)
    {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        d[u][v] = min(d[u][v], w);
        d[v][u] = min(d[v][u], w);
    }
    for (int k = 1; k <= v; ++k)
        for (int i = 1; i <= v; ++i)
            for (int j = 1; j <= v; ++j)
                if (d[i][j] > d[i][k] + d[k][j])
                    d[i][j] = d[i][k] + d[k][j];
    for (int i = 1; i <= v; ++i)
        d[i][i] = d[0][i] = d[i][0] = 0;
    double res = 1e20;
    for (int i = 2; i <= n; ++i)
    {
        dp[i][0][0] = dp[i - 1][0][0] + d[t[i - 1][0]][t[i][0]];
        for (int j = 1; j <= m && j <= i; ++j)
        {
            dp[i][j][0] = min(dp[i][j][0], min(dp[i - 1][j][0] + d[t[i - 1][0]][t[i][0]], dp[i - 1][j][1] + d[t[i - 1][0]][t[i][0]] * (1 - k[i - 1]) + d[t[i - 1][1]][t[i][0]] * k[i - 1]));
            dp[i][j][1] = min(dp[i][j][1], min(dp[i - 1][j - 1][0] + d[t[i - 1][0]][t[i][0]] * (1 - k[i]) + d[t[i - 1][0]][t[i][1]] * k[i], dp[i - 1][j - 1][1] + d[t[i - 1][1]][t[i][1]] * k[i] * k[i - 1] + d[t[i - 1][1]][t[i][0]] * k[i - 1] * (1 - k[i]) + d[t[i - 1][0]][t[i][1]] * (1 - k[i - 1]) * k[i] + d[t[i - 1][0]][t[i][0]] * (1 - k[i - 1]) * (1 - k[i])));
        }
    }
    for (int i = 0; i <= m; i++)
        res = min(res, min(dp[n][i][0], dp[n][i][1]));
    printf("%.2lf", res);
    return 0;
}
