#include <cstring>
#include <stdio.h>
using ll = long long;
const ll M = 7528443412579576937ll;
inline ll qm(ll a, ll b)
{
    ll res = 0;
    while (b)
    {
        if (b & 1)
            res = (1ull * res + 1ull * a) % M;
        a = 2ull * a % M;
        b >>= 1;
    }
    return res;
}
struct Matrix
{
    ll a[4][4];
    int raw, col;
    Matrix(int _raw = 0, int _col = 0)
    {
        raw = _raw;
        col = _col;
        memset(a, 0, sizeof a);
    }
    ll *operator[](const int &index)
    {
        return a[index];
    }
    Matrix operator*(Matrix b) const
    {
        Matrix res(raw, b.col);
        for (int i = 1; i <= raw; ++i)
            for (int j = 1; j <= b.col; ++j)
                for (int k = 1; k <= col; ++k)
                    res[i][j] = (1ull * res[i][j] + 1ull * qm(a[i][k], b[k][j]) % M) % M;
        return res;
    }
    Matrix operator*=(Matrix b)
    {
        return *this = *this * b;
    }
} f1(2, 2), f2(2, 1);
inline Matrix qp(Matrix a, ll b)
{
    Matrix res(a.raw, a.col);
    for (int i = 1; i <= a.raw; ++i)
        res[i][i] = 1;
    while (b)
    {
        if (b & 1)
            res *= a;
        a *= a;
        b >>= 1;
    }
    return res;
}
int main()
{
    ll b, d, n;
    scanf("%lld%lld%lld", &b, &d, &n);
    if (!n)
        return 0 * printf("1");
    f1[1][1] = b;
    f1[1][2] = static_cast<ll>(((d - __int128(b * b)) >> 2) % M);
    f1[2][1] = 1;
    f2[1][1] = b;
    f2[2][1] = 2;
    f1 = qp(f1, n - 1) * f2;
    printf("%lld", (f1.a[1][1] - (d != b * b && !(n & 1)) + 1ull * M) % M);
    return 0;
}
