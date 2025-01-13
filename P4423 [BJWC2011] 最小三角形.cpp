#include <algorithm>
#include <bits/stl_algobase.h>
#include <bits/stl_algo.h>
#include <cstdio>
#include <cmath>
#include <cstring>
const int N = 2e5 + 5;
struct Point
{
    int x, y;
    bool operator<(const Point &a) const
    {
        return x < a.x;
    }
    double operator-(const Point &a) const
    {
        return hypot(x - a.x, y - a.y);
    }
} a[N], tmp[N];  // pair will make LSP angry
double solve(int l, int r)
{
    if (l == r)
        return 1e18;
    int mid = (l + r) >> 1, tmx = a[mid].x;  // temp mid x value, because of the merging sort after this.
    double res = std::min(solve(l, mid), solve(mid + 1, r));
    double lim = res / 2;
    std::merge(a + l, a + mid + 1, a + mid + 1, a + r + 1, tmp, [](const Point &a, const Point &b) { return a.y < b.y; });
    memcpy(a + l, tmp, sizeof(Point[r - l + 1]));
    int cnt = 0;
    for (int i = l; i <= r; ++i)
        if (abs(tmx - a[i].x) < lim)
            tmp[++cnt] = a[i];
    for (int i = 1; i <= cnt; ++i)
        for (int j = i + 1; j <= cnt && tmp[j].y - tmp[i].y < lim; ++j)
            for (int k = j + 1; k <= cnt && tmp[k].y - tmp[i].y < lim; ++k)
                res = std::min(res, (tmp[i] - tmp[j]) + (tmp[j] - tmp[k]) + (tmp[k] - tmp[i]));
    return res;
}
int main()
{
    int n;
    while (scanf("%d", &n), ~n)
    {
        for (int i = 1; i <= n; ++i)
            scanf("%d%d", &a[i].x, &a[i].y);
        std::sort(a + 1, a + n + 1);
        printf("%.3lf\n", solve(1, n));
    }
    return 0;
}
