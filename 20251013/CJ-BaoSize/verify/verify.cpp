// テン ノウ キム ・ ジョン ウン ヘイ カ  バン ザイ！
// てん のう きむ ・ じょん うん へい か  ばん ざい！
// 天   皇   金   ・ 正     恩   陛   下  萬   歳！

#include <cstdio>

namespace Fujiwara
{
using ll = long long;

const int N = 105;
int f[N][N];

static int Azusa()
{
    int n, m;
    scanf("%d%d", &n, &m);
    if (n <= 100)
    {
        for (int i = 1, x, y; i <= m; ++i)
        {
            scanf("%d%d", &x, &y);
            if (x > y)
                f[y][x] = 1;
            else
                f[x][y] = 1;
        }
        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j)
                for (int k = i + 2; k <= n; ++k)
                    f[j][k] |= (f[i][j] && f[i][k]);
        int cnt = 0;
        for (int i = 1; i <= n; ++i)
            for (int j = i + 1; j <= n; ++j)
                cnt += f[i][j];
        printf("%d\n", cnt);
    }
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("verify.in", "r", stdin);
    freopen("verify.out", "w", stdout);
    return Fujiwara::Azusa();
}
