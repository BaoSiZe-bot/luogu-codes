#include <algorithm>
#include <cstdio>
#include <functional>
#include <vector>

namespace Fujiwara
{
using ll = long long;
using std::greater;
using std::sort;
using std::vector;
const int N = 2e5 + 5;
int a[N], t, n;

static void solve()
{
    ll s = 0;
    vector<int> ev;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", a + i);
        if (a[i] & 1)
            ev.emplace_back(a[i]);
        else
            s += a[i];
    }
    if (ev.empty())
    {
        printf("0\n");
        return;
    }
    sort(ev.begin(), ev.end(), greater<int>());
    for (int l = 0, t = (ev.size() - 1) >> 1; l <= t; ++l)
        s += ev[l];
    printf("%lld\n", s);
}

static int Azusa()
{
    scanf("%d", &t);
    while (t--)
        solve();
    return 0;
}
}  // namespace Fujiwara

int main()
{
    return Fujiwara::Azusa();
}
