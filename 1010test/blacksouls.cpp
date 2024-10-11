#include <cmath>
#include <cstring>
#include <stdio.h>
using ll = long long;
const ll M = 7528443412579576937ll;
inline ll qm(ll a, ll b)
{
    ll res = 0;
    printf("b is %lld.\n", b);
    while (b)
    {
        if (b & 1)
        {
            res = (1ull * res + 1ull * a) % M;
            // printf("Dorry...\n");
        }
        a = 2ull * a % M;
        // printf("Dorra...\n");
        b >>= 1;
    }
    printf("Dolla...\n");
    return res;
}
struct Matrix
{
    ll a[4][4];
    Matrix()
    {
        memset(a, 0, sizeof a);
    }
    ll *operator[](const int &index)
    {
        return a[index];
    }
    Matrix operator*(Matrix b) const
    {
        Matrix res;
        for (int i = 1; i <= 2; ++i)
            for (int j = 1; j <= 2; ++j)
                for (int k = 1; k <= 2; ++k)
                {
                    res[i][j] = (1ull * res[i][j] + 1ull * qm(a[i][k], b[k][j]) % M) % M;
                    printf("Doooi...\n");
                }
        printf("Dobby...\n");
        return res;
    }
    Matrix operator*=(Matrix b)
    {
        return *this = *this * b;
    }
};
inline Matrix qp(Matrix a, ll b)
{
    Matrix res;
    res[1][1] = 1;
    res[2][2] = 1;
    while (b)
    {
        if (b & 1)
            res *= a;
        printf("Doppi...\n");
        a *= a;
        printf("Doggi...\n");
        b >>= 1;
    }
    printf("Doing...\n");
    return res;
}
int main()
{
    int x, k, n;
    scanf("%d%d", &x, &n);
    k = ceil(sqrt(x));
    Matrix f1, f2;
    f1[2][2] = 2 * k;
    f1[1][2] = static_cast<ll>((x - __int128(k * k)) % M);
    f1[2][1] = 1;
    f2[1][1] = 2 * k;
    f2[1][2] = 2;
    f1 = qp(f1, n - 1) * f2;
    printf("%lld", (f1.a[1][2] - (x != k * k) + 1ull * M) % M);
    return 0;
}
