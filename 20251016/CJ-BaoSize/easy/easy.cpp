#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

namespace Fujiwara
{
using std::vector;

int dp[55][55][105];

static int cmax(int &x, int y)
{
    return x = (x < y ? y : x);
}
static int Azusa()
{
    int n, m;
    scanf("%d%d", &n, &m);
    vector<int> a(n), b(m);
    for (int &i : a)
        scanf("%d", &i);
    for (int &i : b)
        scanf("%d", &i);

    memset(dp, 0xc0, sizeof(dp));

    dp[0][0][0] = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            for (int k = 1; k <= i + j; ++k)
                for (int p = 0; p <= i; ++p)
                    for (int q = 0; q <= j; ++q)
                        cmax(dp[i][j][k], dp[p][q][k - 1] + std::abs(a[p] + b[q] - a[i] - b[j]));

    int res = 0;
    for (int k = 1; k <= (n - 1) + (m - 1); ++k)
        cmax(res, dp[n - 1][m - 1][k]);
    printf("%d\n", res);
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("easy.in", "r", stdin);
    freopen("easy.out", "w", stdout);
    return Fujiwara::Azusa();
}

// O2 really astounded me! From 2.07s -> 147ms
// O2 expanded 2 whole loops so it divided by 16!
