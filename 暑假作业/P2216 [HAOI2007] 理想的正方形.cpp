#include <stdio.h>
#include <limits.h>
#include <bits/stl_algobase.h>
#include <bits/stl_algo.h>
int g[1005][1005], s1[1005][1005], s2[1005][1005], len, a, b, n, res = INT_MAX;
inline int query(int x, int y)
{
    int j = 1 << len;
    return std::max({s1[x][y], s1[x + n - j][y + n - j], s1[x + n - j][y], s1[x][y + n - j]}) - std::min({s2[x][y], s2[x + n - j][y + n - j], s2[x + n - j][y], s2[x][y + n - j]});
}
int main()
{
    scanf("%d%d%d", &a, &b, &n);
    for (int i = 1; i <= a; ++i)
        for (int j = 1; j <= b; ++j)
        {
            scanf("%d", &g[i][j]);
            s1[i][j] = s2[i][j] = g[i][j];
        }
    len = 31 - __builtin_clz(n);
    for (int i = 0; i <= len - 1; ++i)
    {
        int u = a - (1 << i), v = b - (1 << i);
        for (int j = 1; j <= u; ++j)
            for (int k = 1; k <= v; ++k)
            {
                s1[j][k] = std::max({s1[j][k], s1[j + (1 << i)][k + (1 << i)], s1[j + (1 << i)][k], s1[j][k + (1 << i)]});
                s2[j][k] = std::min({s2[j][k], s2[j + (1 << i)][k + (1 << i)], s2[j + (1 << i)][k], s2[j][k + (1 << i)]});
            }
    }
    for (int i = 1; i <= a - n + 1; i++)
        for (int j = 1; j <= b - n + 1; j++)
            res = std::min(res, query(i, j));
    printf("%d", res);
    return 0;
}
