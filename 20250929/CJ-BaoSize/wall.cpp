#include <algorithm>
#include <cstdio>
namespace Fujiwara
{
using std::max;
using std::next_permutation;

const int N = 3e5 + 5;
int T, n, m, a[N];
static void solve()
{
    scanf("%d%d", &n, &m);
    if (m == n - 2)
        printf("ruobi\n");
    for (int i = 1; i <= n; ++i)
        a[i] = i;
    do
    {
        int cnt = 0;
        for (int i = 1; i < n - 1; ++i)
            if (a[i] + a[i + 1] + a[i + 2] > max({a[i], a[i + 1], a[i + 2]}) * 2)
                ++cnt;
        if (cnt == m)
        {
            printf("qiangbi\n");
            for (int i = 1; i <= n; ++i)
                printf("%d ", a[i]);
            printf("\n");
            return;
        }
    } while (next_permutation(a + 1, a + n + 1));
    printf("ruobi\n");
}
static int Azusa()
{
    scanf("%d", &T);
    while (T--)
        solve();
    // 期望得分 50
    // 猜测结论：
    // m = n - 3 此时必然 1,2,..n 为合法解
    // m = n - 2 此时必然无解
    return 0;
}
}  // namespace Fujiwara
int main()
{
    // freopen("wall.in", "r", stdin);
    // freopen("wall.out", "w", stdout);
    return Fujiwara::Azusa();
}
