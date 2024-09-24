#include <stdio.h>
#include <string.h>

const double eps = 1e-6;

int n, a[15][15], s[15][15];
double _s, dp[15][15][15][15][15];

double sq(double x)
{
    return x * x;
}
double min(double u, double v)
{
    return u - v < -eps ? u : v;
}
int gts(int x1, int y1, int x2, int y2)
{
    return s[x2][y2] + s[x1 - 1][y1 - 1] - s[x1 - 1][y2] - s[x2][y1 - 1];
}
double gtx(int x1, int y1, int x2, int y2)
{
    return sq(gts(x1, y1, x2, y2) - _s) / n;
}
double dfs(int x1, int y1, int x2, int y2, int k)
{
    double &t = dp[x1][y1][x2][y2][k];
    if (k == 1)
        return t = gtx(x1, y1, x2, y2);
    if (t >= 0)
        return t;
    t = 2147483647;
    for (int i = x1; i < x2; ++i)
    {
        t = min(t, dfs(x1, y1, i, y2, k - 1) + gtx(i + 1, y1, x2, y2));
        t = min(t, gtx(x1, y1, i, y2) + dfs(i + 1, y1, x2, y2, k - 1));
    }
    for (int i = y1; i < y2; ++i)
    {
        t = min(t, dfs(x1, y1, x2, i, k - 1) + gtx(x1, i + 1, x2, y2));
        t = min(t, gtx(x1, y1, x2, i) + dfs(x1, i + 1, x2, y2, k - 1));
    }
    return t;
}
#include <math.h>
int main()
{
    memset(dp, 0x80, sizeof dp);
    scanf("%d", &n);
    for (int i = 1; i <= 8; ++i)
        for (int j = 1; j <= 8; ++j)
        {
            scanf("%d", a[i] + j);
            s[i][j] = s[i - 1][j] + s[i][j - 1] + a[i][j] - s[i - 1][j - 1];
        }
    _s = s[8][8] * 1.0 / n;
    printf("%.3lf", sqrt(dfs(1, 1, 8, 8, n)));
    return 0;
}
