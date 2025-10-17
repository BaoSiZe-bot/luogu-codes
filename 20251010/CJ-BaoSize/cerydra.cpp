#include <algorithm>
#include <cstdio>
#include <cstring>
namespace Fujiwara
{
using std::min;
using std::max;
const int N = 1e3 + 5;

int n, m;
int f[N][N], g[N][N];
static int Azusa()
{
    scanf("%d%d", &n, &m);
    if (n == 2)
    {
        printf("%d %d\n", m / 4 + m % 4, m);
        return 0;
    }
    if (n < N && m < N)
    {
        memset(f, 0x3f, sizeof(f));
        memset(g, -0x3f, sizeof(g));
        for (int i = 0; i <= n; ++i)
        {
            f[i][0] = 0;
            g[i][0] = 0;
        }
        for (int j = 0; j <= m; ++j)
        {
            f[0][j] = 0;
            g[0][j] = 0;
        }
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
            {
                if (j % 2 == 0 && i >= j / 2)
                {
                    f[i][j] = min(f[i][j], f[i - j / 2][j] + 1);
                    g[i][j] = max(g[i][j], g[i - j / 2][j] + 1);
                }
                if (i >= j * 2)
                {
                    f[i][j] = min(f[i][j], f[i - j * 2][j] + 1);
                    g[i][j] = max(g[i][j], g[i - j * 2][j] + 1);
                }
                if (i % 2 == 0 && j >= i / 2)
                {
                    f[i][j] = min(f[i][j], f[i][j - i / 2] + 1);
                    g[i][j] = max(g[i][j], g[i][j - i / 2] + 1);
                }
                if (j >= i * 2)
                {
                    f[i][j] = min(f[i][j], f[i][j - i * 2] + 1);
                    g[i][j] = max(g[i][j], g[i][j - i * 2] + 1);
                }
            }
        printf("%d %d\n", f[n][m], g[n][m]);
        return 0;
    }
    return 0;
}
}  // namespace Fujiwara

int main()
{
    freopen("cerydra.in", "r", stdin);
    freopen("cerydra.out", "w", stdout);
    return Fujiwara::Azusa();
}
