#include <limits.h>
#include <stdio.h>
using dl = double;
int x, y, a;
dl min(dl a, dl b)
{
    return a < b ? a : b;
}
dl max(dl a, dl b)
{
    return a < b ? b : a;
}
dl dfs(dl x, dl y, int k)
{
    if (k == 1)
        return max(x, y) / min(x, y);
    dl res = INT_MAX, u = 0, v = 0;
    for (int i = 1; i * 2 <= k; ++i)
    {
        u = max(dfs(x / k * i, y, i), dfs(x - x / k * i, y, k - i));
        v = max(dfs(x, y / k * i, i), dfs(x, y - y / k * i, k - i));
        res = min(res, min(u, v));
    }
    return res;
}
int main()
{
    scanf("%d%d%d", &x, &y, &a);
    printf("%.6lf", dfs(x, y, a));
    return 0;
}
