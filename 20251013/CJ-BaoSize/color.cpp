#include <cstdio>
#include <vector>

namespace Fujiwara
{
using std::vector;

using ll = long long;
const int N = 2e5 + 5;

bool f[N];
vector<vector<int>> e;
static int Azusa()
{
    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    if (m != n - 1 || k != 1)
        return 0 * printf("-1");

    e.resize(n + 1);
    for (int i = 1, u, v; i <= m; ++i)
    {
        scanf("%d%d", &u, &v);
        e[u].emplace_back(v);
        e[v].emplace_back(u);
    }
    if (e[1].size() != 1)
        return 0 * printf("-1");
    int p = 1;
    printf("%d\n", n);
    do
    {
        f[p] = 1;
        printf("%d ", p);
        if(p != 1 && e[p].size() == 1)
            break;
        if (f[e[p].front()])
            p = e[p].back();
        else
            p = e[p].front();
    } while (true);
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("color.in", "r", stdin);
    freopen("color.out", "w", stdout);
    return Fujiwara::Azusa();
}
