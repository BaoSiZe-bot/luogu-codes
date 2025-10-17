// 众所周知，在日语中，中国和虫国是同一个读音
// 都念作 chugoku
#include <cstdio>
#include <vector>

namespace Fujiwara
{
using std::vector;
using ll = long long;

vector<int> a;
int n, res = 0;
static void dfs(int p, int xr, int ad)
{
    if (p > n)
    {
        res += (xr == ad);
        return;
    }
    dfs(p + 1, xr, ad);
    dfs(p + 1, xr ^ a[p], ad & a[p]);
}
static int Azusa()
{
    scanf("%d", &n);

    a.resize(n + 1);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    dfs(1, 0, -1);  // -1 == 0b1111...11
    printf("%d\n", res);
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
    return Fujiwara::Azusa();
}
