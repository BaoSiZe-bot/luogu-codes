#include <algorithm>
#include <stdio.h>
const int N = 2e6 + 5;
struct Ln
{
    int xl, xr, y, s;
    bool operator<(const Ln &a) const
    {
        return y < a.y;
    }
} ln[N];
struct SegTree
{
    int l, r, s;
    long long z;
} s[N << 1];
int a[N];
long long res;
void bld(int x, int l, int r)
{
    s[x] = {l, r, 0, 0};
    if (l ^ r)
    {
        int mid = (l + r) >> 1;
        bld(x << 1, l, mid);
        bld(x << 1 | 1, mid + 1, r);
    }
}
void add(int x, int l, int r, int v)
{
    if (a[s[x].r + 1] <= l || r <= a[s[x].l])
        return;
    if (l <= a[s[x].l] && a[s[x].r + 1] <= r)
    {
        s[x].s += v;
        s[x].z = s[x].s ? a[s[x].r + 1] - a[s[x].l] : s[x << 1].z + s[x << 1 | 1].z;
        return;
    }
    add(x << 1, l, r, v);
    add(x << 1 | 1, l, r, v);
    s[x].z = s[x].s ? a[s[x].r + 1] - a[s[x].l] : s[x << 1].z + s[x << 1 | 1].z;
}
int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        int xl, xr, yl, yr;
        scanf("%d%d%d%d", &xl, &yl, &xr, &yr);
        a[(i - 1) << 1 | 1] = xl;
        ln[(i - 1) << 1 | 1] = {xl, xr, yl, 1};
        a[i << 1] = xr;
        ln[i << 1] = {xl, xr, yr, -1};
    }
    n <<= 1;
    std::sort(a + 1, a + n + 1);
    int al = std::unique(a + 1, a + n + 1) - a - 1;
    std::sort(ln + 1, ln + n + 1);
    bld(1, 1, al - 1);
    for (int i = 1; i < n; ++i)
    {
        add(1, ln[i].xl, ln[i].xr, ln[i].s);
        res += s[1].z * (ln[i + 1].y - ln[i].y);
    }
    printf("%lld", res);
    return 0;
}
