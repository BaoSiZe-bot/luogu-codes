#include <bits/stl_algobase.h>
#include <bits/stl_algo.h>
#include <bits/stl_pair.h>
#include <cmath>
#include <cstdio>
int n;
using pii = std::pair<ll, ll>;
const int N = 4e5 + 5;
pii a[N];
inline ll dis(pii x, pii y)
{
    return (x.first - y.first) * (x.first - y.first) + (x.second - y.second) * (x.second - y.second);
}
pii tmp[N];
int cnt;
ll merge(int l, int r)
{
    if (r <= l)
        return 1e18;
    int mid = (l + r) >> 1;
    ll lres = merge(l, mid), rres = merge(mid + 1, r);
    ll res = std::min(lres, rres);
    //std::inplace_merge(a + l, a + mid, a + r + 1, [](const pii &x, const pii &y) { return x.second < y.second; });
    ll tt = sqrt(res);
    cnt = 0;
    for (int i = l; i <= r; ++i)
        if (std::abs(a[mid].first - a[i].first) <= tt)
            tmp[++cnt] = a[i];
    std::sort(tmp + 1, tmp + cnt + 1, [](const pii &x, const pii &y){return x.second < y.second;});
    for (int i = 1; i <= cnt; ++i)
        for (int j = i - 1; j && tmp[i].second - tmp[j].second <= tt; --j)
        {
            res = std::min(res, dis(tmp[i], tmp[j]));
            tt = sqrt(res);
        }
    return res;
}
int main()
{
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%lld%lld", &a[i].first, &a[i].second);
    std::sort(a + 1, a + n + 1);
    printf("%lld\n", merge(1, n));
    return 0;
}
