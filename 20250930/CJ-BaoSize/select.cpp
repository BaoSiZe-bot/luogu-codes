#include <iostream>

using std::cin;
using std::cout;

namespace Fujiwara
{
int n, res;
// 只是不想写数组了而已
// 2^10 就没必要取模了吧
// 事实上就算这东西开了记忆化也不会对时间复杂度产生任何有效的优化
static void dfs(int x, int s)
{
    if (x > n)
    {
        ++res;
        return;
    }
    dfs(x + 1, s);
    if (!((s >> (x - 1)) & 1))
    {
        int ns = s | (1 << (x - 1));
        if (x * 2 <= n)
            ns |= (1 << (x * 2 - 1));
        if (x * 3 <= n)
            ns |= (1 << (x * 3 - 1));
        dfs(x + 1, ns);
    }
}
static int Azusa()
{
    cin >> n;
    if (n <= 10)
    {
        dfs(1, 0);
        cout << res;
    }
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("select.in", "r", stdin);
    freopen("select.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    return Fujiwara::Azusa();
}
