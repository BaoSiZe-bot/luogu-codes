#include <cstdio>
#include <utility>
#include <vector>

namespace Fujiwara
{
using ll = long long;
using std::pair;
using std::vector;

int n, q, s;
int g, w, c;
static void solve()
{
    scanf("%d", &s);
}
static int Azusa()
{
    scanf("%d%d%d%d%d", &n, &q, &g, &w, &c);
    std::vector<pair<int, int>> pt(n + 1);
    for (int i = 1; i <= n; ++i)
        scanf("%d%d", &pt[i].first, &pt[i].second);
    while (q--)
        solve();
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("glory.in", "r", stdin);
    freopen("glory.out", "w", stdout);
    return Fujiwara::Azusa();
}
