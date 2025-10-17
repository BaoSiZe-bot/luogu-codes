#include <algorithm>
#include <cstdio>
#include <vector>

namespace Fujiwara
{
using std::max;
using std::next_permutation;
using std::sort;
using std::vector;

const int inf = 2e9 + 21;
const int N = 515;
int res = inf;
int dp[N][N];

static int cmax(int &x, int y)
{
    return x = x < y ? y : x;
}
static void solve()
{
    int n;
    scanf("%d", &n);
    vector<int> a(n + 5);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &a[i]);
    if (n <= 5)
    {
        sort(a.begin() + 1, a.begin() + n + 1);
        vector<int> b = a, c = a, rb, rc, t(n + 5);
        do
            do
            {
                int mx = 0;
                for (int i = 0; i < n; ++i)
                {
                    for (int j = 1; j <= n; ++j)
                        t[j] = c[(i + j - 1) % n + 1];
                    for (int j = 1; j <= n; ++j)
                        for (int k = 1; k <= n; ++k)
                        {
                            dp[j][k] = 0;
                            cmax(dp[j][k], dp[j][k - 1]);
                            cmax(dp[j][k], dp[j - 1][k]);
                            b[j] == t[k] && cmax(dp[j][k], dp[j - 1][k - 1] + 1);
                        }
                    mx = max(mx, dp[n][n]);
                }
                if (res > mx)
                {
                    res = mx;
                    rb = b;
                    rc = c;
                }
            } while (next_permutation(c.begin() + 1, c.begin() + n + 1));
        while (next_permutation(b.begin() + 1, b.begin() + n + 1));
        printf("%d\n", res);
        for (int i = 1; i <= n; ++i)
            printf("%d ", rb[i]);
        printf("\n");
        for (int i = 1; i <= n; ++i)
            printf("%d ", rc[i]);
        return;
    }
}
static int Azusa()
{
    int T = 1;
    // scanf("%d", &T);
    while (T--)
        solve();
    return 0;
}
}  // namespace Fujiwara
int main()
{
    freopen("art.in", "r", stdin);
    freopen("art.out", "w", stdout);
    return Fujiwara::Azusa();
}
