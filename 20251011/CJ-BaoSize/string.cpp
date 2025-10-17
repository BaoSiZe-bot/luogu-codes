#include <cstdio>
#include <vector>
#include <set>

namespace Fujiwara
{
using std::multiset;
using std::set;
using ll = long long;

set<multiset<int>> s;
static void solve()
{
    int n;
    scanf("%d", &n);
    std::vector<int> a(n + 5);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    for (int l = 1; l <= n; ++l)
    {
        multiset<int> tmp;
        for (int r = l; r <= n; ++r)
        {
            tmp.insert(a[r]);
            s.insert(tmp);
        }
    }
    printf("%d\n", (int)s.size());
}
static int Azusa()
{
    int t = 1;
    // scanf("%d", &t);
    while (t--)
        solve();
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("string.in", "r", stdin);
    freopen("string.out", "w", stdout);
    return Fujiwara::Azusa();
}
