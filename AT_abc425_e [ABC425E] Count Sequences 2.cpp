#include <cstdio>
namespace Fujiwara
{
using ll = long long;

const int N = 3e5 + 5, L = 5005;
int T, M, c[N], n;
ll C[L][L];
static void precl()
{
    for (int i = 0; i < L; ++i)
    {
        C[i][0] = C[i][i] = 1;
        for (int j = 1; j < i; ++j)
            C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % M;
    }
}
inline void solve()
{
    ll s = 0, t = 1;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
        scanf("%d", c + i);
    for (int i = 1; i <= n; ++i)
        s += c[i];
    for (int i = 1; i <= n; i++)
    {
        (t *= C[s][c[i]]) %= M;
        s -= c[i];
    }
    printf("%lld\n", t);
}
static int Azusa()
{
    scanf("%d%d", &T, &M);

    precl();
    while (T--)
        solve();
    return 0;
}
}  // namespace Fujiwara
int main()
{
    return Fujiwara::Azusa();
}
